/*
 * Valgrind Cachegrind Demonstration Program
 * * PURPOSE:
 * This program performs matrix multiplication using an intentionally
 * inefficient loop order (i-k-j) which results in poor data locality.
 * Cachegrind will highlight this function as having a high number of
 * cache misses, pointing to a performance bottleneck.
 * * INSTRUCTIONS:
 * 1. Compile: g++ -g cachegrind_demo.cpp -o cachegrind_demo
 * 2. Run with Cachegrind: valgrind --tool=cachegrind ./cachegrind_demo
 * 3. Analyze results (requires 'cgview' or 'callgrind_annotate' tools):
 * callgrind_annotate cachegrind.out.<pid>
 */

#include <iostream>
#include <vector>
#include <iomanip>

const int SIZE = 256; // Matrix size. Keep it small to run quickly, but large enough for misses.

// Global matrices
std::vector<std::vector<int>> A(SIZE, std::vector<int>(SIZE));
std::vector<std::vector<int>> B(SIZE, std::vector<int>(SIZE));
std::vector<std::vector<int>> C(SIZE, std::vector<int>(SIZE));

void initialize_matrices() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            A[i][j] = i + j;
            B[i][j] = i - j;
            C[i][j] = 0;
        }
    }
}

// Matrix multiplication with INEFFICIENT loop order (i-k-j)
// This order accesses matrix B column-wise (j loop is fastest varying),
// which is bad for C++'s row-major memory layout, causing cache misses.
void multiply_inefficient() {
    std::cout << "Running inefficient matrix multiplication (i-k-j order)...\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int k = 0; k < SIZE; ++k) { // Middle loop
            int r = A[i][k];
            for (int j = 0; j < SIZE; ++j) { // Inner loop
                C[i][j] += r * B[k][j];
            }
        }
    }
}

// Matrix multiplication with EFFICIENT loop order (i-j-k)
// This order accesses all matrices row-wise, which is optimal for cache usage.
void multiply_efficient() {
    std::cout << "Running efficient matrix multiplication (i-j-k order)...\n";
    // This function is included just for comparison but only the inefficient
    // one is called in main to demonstrate the issue.
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) { // Middle loop
            int sum = 0;
            for (int k = 0; k < SIZE; ++k) { // Inner loop
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

int main() {
    std::cout << "Cachegrind Demo starting with matrix size " << SIZE << "x" << SIZE << ".\n";
    initialize_matrices();

    // We only call the inefficient version for profiling
    multiply_efficient();

    std::cout << "\nOperation finished. Check the 'cachegrind.out.<pid>' file for detailed cache analysis.\n";

    // Read a single value to avoid compiler optimizing away the whole calculation
    std::cout << "Check value (C[0][0]): " << C[0][0] << std::endl;
    return 0;
}
