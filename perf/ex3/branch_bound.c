// branch_bound_complex.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000000
#define ITERATIONS 20

int main() {
    int *data = malloc(SIZE * sizeof(int));
    srand(time(NULL));

    // Fill with random integers
    for (int i = 0; i < SIZE; i++) {
        // Use a function that generates high-quality random numbers if available
        data[i] = rand(); 
    }

    long long count = 0;
    
    // The conditional logic is much harder to optimize to branchless code:
    for (int k = 0; k < ITERATIONS; k++) {
        for (int i = 0; i < SIZE; i++) {
            
            // Complex, data-dependent, loop-carried condition
            if ( (data[i] > (SIZE / 2)) && ((data[i] ^ count) & 0x1) ) {
                // Path 1 (Small update)
                count += 1; 
            } else if (data[i] < (SIZE / 4)) {
                // Path 2 (Medium update)
                count += 5;
            } else {
                // Path 3 (Largest update)
                count += 17; 
            }
        }
    }

    printf("Final Count: %lld\n", count);
    free(data);
    return 0;
}
