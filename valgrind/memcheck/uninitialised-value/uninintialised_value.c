#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char str[5];
    str[4] = '\0';
    FILE* fptr = fopen("demo.out", "w");
    fprintf(fptr, "%s", str);
    fclose(fptr);
    return 0;
}
