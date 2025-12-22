// compute_bound.c
#include <stdio.h>
#include <math.h>

#define ITERATIONS 300000000

int main() {
    double x = 1.0;
    double y = 1.0;
    
    // Heavy arithmetic loop
    for (int i = 0; i < ITERATIONS; i++) {
        x += sin(x) + cos(y);
        y += cos(x) + sin(y);
    }

    printf("Result: %f\n", x + y);
    return 0;
}
