#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char *buffer = (char*) malloc(40);

    sprintf(buffer, "This string is 1 too long for the buffer");

    return 0;
}
