# Using Cachegrind to profile cache usage
Cachegrind models a virtual CPU, which can be used to profile cycle-accurate memory acccesses.
To do this, Cachegrind instruments the binary and keeps track of memory accesses and a state of the cache.
Currently, the CPU model only simulates L1-I, L1-D and LL caches.
The cache sizes can be configured with the `--I1`, `--D1`, `--LL` program options.
If the sizes are not manually specified, Cachegrind tries to determine them automatically, and falls back to an AMD Athlon 3/4 like setup for x86/amd64 architectures.

The usual procedure of using Cachegrind is as follows:
1. Call `valgrind --tool=cachegrind --cache-sim=yes ${FILE}`
2. Call `cg_annotate`

The example program executes matrix multiplication in two different ways.
The first one iterates column-wise, which is cache-unfriendly, as the program jumps between different rows.
The second one iterates row-wise, resulting in superior cache usage.
This can be seen in the output of the cg_annotate:
```
Ir_________________ I1mr____ ILmr____ Dr_________________ D1mr_______________ DLmr__________ Dw_________________ D1mw___________ DLmw__________
.....
.         .        .                  .                   .              .                   .               .              .          // ==============================================================================
.         .        .                  .                   .              .                   .               .              .          // 1. INEFFICIENT (Cache Unaware) Matrix Multiplication (ijk loop order)
.         .        .                  .                   .              .                   .               .              .          // Accesses B non-sequentially (column-wise) causing frequent cache misses.
.         .        .                  .                   .              .                   .               .              .          // ==============================================================================
2  (0.0%) 1 (0.0%) 1 (0.0%)           0                   0              0                   2  (0.0%)       0              0          void multiply_inefficient(const Matrix& A, const Matrix& B, Matrix& C) {
.         .        .                  .                   .              .                   .               .              .              // Standard loop order: i, j, k
1,536  (0.0%) 0        0                  0                   0              0                   0               0              0              for (int i = 0; i < N; ++i) {
786,432  (0.0%) 0        0                  0                   0              0                   0               0              0                  for (int j = 0; j < N; ++j) {
786,432  (0.0%) 0        0                  0                   0              0                   0               0              0                      double sum = 0.0;
537,395,200 (25.8%) 0        0                  0                   0              0                   0               0              0                      for (int k = 0; k < N; ++k) {
.         .        .                  .                   .              .                   .               .              .                          // Access Pattern in the innermost loop (k):
.         .        .                  .                   .              .                   .               .              .                          // A[i][k] is sequential (good locality: row i is traversed).
.         .        .                  .                   .              .                   .               .              .                          // B[k][j] is non-sequential (BAD locality: column j is traversed, jumping in memory).
536,870,912 (25.8%) 1 (0.0%) 1 (0.0%) 402,653,184 (59.3%) 201,293,592 (92.2%) 35,299 (31.3%)           0               0              0                          sum += A[i][k] * B[k][j];
.         .        .                  .                   .              .                   .               .              .                      }
262,144  (0.0%) 0        0                  0                   0              0             262,144  (0.2%) 262,144 (52.9%) 29,626 (11.3%)              C[i][j] = sum;
.         .        .                  .                   .              .                   .               .              .                  }
.         .        .                  .                   .              .                   .               .              .              }
3  (0.0%) 1 (0.0%) 1 (0.0%)           3  (0.0%)           1  (0.0%)      1  (0.0%)           0               0              0          }
.         .        .                  .                   .              .                   .               .              .
.         .        .                  .                   .              .                   .               .              .          // ==============================================================================
.         .        .                  .                   .              .                   .               .              .          // 2. EFFICIENT (Cache Aware) Matrix Multiplication (ikj loop order)
.         .        .                  .                   .              .                   .               .              .          // Accesses B sequentially (row-wise) leading to high cache hit rates.
.         .        .                  .                   .              .                   .               .              .          // ==============================================================================
1  (0.0%) 0        0                  0                   0              0                   1  (0.0%)       0              0          void multiply_efficient(const Matrix& A, const Matrix& B, Matrix& C) {
.         .        .                  .                   .              .                   .               .              .              // Cache-optimized loop order: i, k, j
1,536  (0.0%) 0        0                  0                   0              0                   0               0              0              for (int i = 0; i < N; ++i) {
1,048,576  (0.1%) 0        0                  0                   0              0                   0               0              0                  for (int k = 0; k < N; ++k) {
.         .        .                  .                   .              .                   .               .              .                      // Note: A[i][k] is constant in the innermost loop (j)
262,144  (0.0%) 0        0            262,144  (0.0%)      32,896  (0.0%) 32,896 (29.2%)           0               0              0                      double r = A[i][k];
402,653,184 (19.3%) 0        0                  0                   0              0                   0               0              0                      for (int j = 0; j < N; ++j) {
.         .        .                  .                   .              .                   .               .              .                          // Access Pattern in the innermost loop (j):
.         .        .                  .                   .              .                   .               .              .                          // B[k][j] is sequential (GOOD locality: row k is traversed).
.         .        .                  .                   .              .                   .               .              .                          // C[i][j] is also sequential.
536,870,912 (25.8%) 1 (0.0%) 1 (0.0%) 268,435,456 (39.6%)  16,876,160  (7.7%) 32,518 (28.8%) 134,217,728 (94.3%)       0              0                          C[i][j] += r * B[k][j];
.         .        .                  .                   .              .                   .               .              .                      }
.         .        .                  .                   .              .                   .               .              .                  }
.         .        .                  .                   .              .                   .               .              .              }
2  (0.0%) 0        0                  2  (0.0%)           1  (0.0%)      1  (0.0%)           0               0              0          }
```

The first row denotes the number of I-cache read (Ir).
The next row, I1mr, denotes the number of missed I1-cache reads and the the row ILmr denotes the number of missed LL-cache instruction reads.
The same is done for data-reads (Dr, D1mr, DLmr) and data-writes (Dw, D1mw, DLmw).
In this example, the inner loop of the first column-wise matrix multiplication is responsible for 201,293,592 D1 misses, which account for 92.2% of all D1 cache missses of the program (the percentage next to the actual number).
The row-wise matrix multiplication is far more cache friendly, with only 16,876,160 D1 cache-misses.
