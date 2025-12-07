#include <stdlib.h>

int main(int argc, char **argv) {
    int *int_ptr = (int *)malloc(4);
    float *float_ptr = (float *)malloc(4);
    double *double_ptr = (double *)malloc(8);
    long long *long_long_ptr = (long long *)malloc(4);
    free(int_ptr);
    free(float_ptr);
    free(double_ptr);
    free(long_long_ptr);
    free(int_ptr);
    return 0;
}
