#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <random>

// Define the size of the square matrices (N x N)
// Choose a size that is large enough to show cache effects (e.g., 512, 1024, or 2048)
// Be aware that 2048x2048 will take a long time on the inefficient method.
const int N = 512;

// Type alias for convenience
using Matrix = std::vector<std::vector<double>>;

// Function to initialize a matrix with random values
void initialize_matrix(Matrix& M) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(1.0, 10.0);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            M[i][j] = distrib(gen);
        }
    }
}

// ==============================================================================
// 1. INEFFICIENT (Cache Unaware) Matrix Multiplication (ijk loop order)
// Accesses B non-sequentially (column-wise) causing frequent cache misses.
// ==============================================================================
void multiply_inefficient(const Matrix& A, const Matrix& B, Matrix& C) {
    // Standard loop order: i, j, k
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            double sum = 0.0;
            for (int k = 0; k < N; ++k) {
                // Access Pattern in the innermost loop (k):
                // A[i][k] is sequential (good locality: row i is traversed).
                // B[k][j] is non-sequential (BAD locality: column j is traversed, jumping in memory).
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

// ==============================================================================
// 2. EFFICIENT (Cache Aware) Matrix Multiplication (ikj loop order)
// Accesses B sequentially (row-wise) leading to high cache hit rates.
// ==============================================================================
void multiply_efficient(const Matrix& A, const Matrix& B, Matrix& C) {
    // Cache-optimized loop order: i, k, j
    for (int i = 0; i < N; ++i) {
        for (int k = 0; k < N; ++k) {
            // Note: A[i][k] is constant in the innermost loop (j)
            double r = A[i][k];
            for (int j = 0; j < N; ++j) {
                // Access Pattern in the innermost loop (j):
                // B[k][j] is sequential (GOOD locality: row k is traversed).
                // C[i][j] is also sequential.
                C[i][j] += r * B[k][j];
            }
        }
    }
}

// Helper function to measure and run a multiplication
double measure_time(void (*func)(const Matrix&, const Matrix&, Matrix&),
                    const Matrix& A, const Matrix& B, Matrix& C) {

    // Reset C before running the multiplication
    for (int i = 0; i < N; ++i) {
        std::fill(C[i].begin(), C[i].end(), 0.0);
    }

    auto start = std::chrono::high_resolution_clock::now();
    func(A, B, C);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    return duration.count();
}

int main() {
    std::cout << "--- Cache Locality Demonstration (Matrix Multiplication) ---\n";
    std::cout << "Matrix Size: " << N << "x" << N << " (Total " << N * N << " elements)\n\n";

    // 1. Setup Matrices
    Matrix A(N, std::vector<double>(N));
    Matrix B(N, std::vector<double>(N));
    Matrix C(N, std::vector<double>(N));

    initialize_matrix(A);
    initialize_matrix(B);

    // 2. Run and Measure Inefficient Multiplication
    std::cout << "Running Inefficient (ijk) Multiplication...\n";
    double time_inefficient = measure_time(multiply_inefficient, A, B, C);
    std::cout << "  -> Time taken: " << std::fixed << std::setprecision(2)
              << time_inefficient << " ms\n\n";

    // 3. Run and Measure Efficient Multiplication
    std::cout << "Running Efficient (ikj) Multiplication...\n";
    double time_efficient = measure_time(multiply_efficient, A, B, C);
    std::cout << "  -> Time taken: " << std::fixed << std::setprecision(2)
              << time_efficient << " ms\n\n";

    // 4. Report Comparison
    double speedup = time_inefficient / time_efficient;
    std::cout << "========================================================\n";
    std::cout << "RESULTS:\n";
    std::cout << "Efficient method was " << std::fixed << std::setprecision(1)
              << speedup << "x faster than the inefficient method.\n";
    std::cout << "This massive difference is almost entirely due to CPU cache misses vs. hits.\n";
    std::cout << "========================================================\n";

    return 0;
}
