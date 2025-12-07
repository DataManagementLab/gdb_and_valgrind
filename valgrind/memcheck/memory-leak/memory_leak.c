#include <stdlib.h>
#include <string.h>

struct LinkedList {
    struct LinkedList* next;
};

void leaking_function() {
    struct LinkedList *list = (struct LinkedList *)malloc(sizeof(struct LinkedList));
    list->next = (struct LinkedList *)malloc(sizeof(struct LinkedList));
}


void unexpected_crash() {
    abort();
}


int main(int argc, char **argv) {
    leaking_function();
    int* still_reachable = (int *) malloc(8 * sizeof(int));
    int* possibly_lost = (int *) malloc(8 * sizeof(int));
    possibly_lost += 1;
    unexpected_crash();
    possibly_lost -= 1;
    free(still_reachable);
    free(possibly_lost);
    return 0;
}
