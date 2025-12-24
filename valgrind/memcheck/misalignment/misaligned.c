#include <stdlib.h>

struct MyStruct {
    int a;
    float b;
    long long c;
};


int main(int argc, char **argv) {
    struct MyStruct* mystruct_array;
    posix_memalign((void**)&mystruct_array, 24, 4);
    return 0;
}
