#include <stdlib.h>

int main(int argc, char **argv) {
    int rand_size = (rand() % 16384) * -1;
    float *float_arr = (float *)malloc(rand_size * sizeof(float));
    return 0;
}
