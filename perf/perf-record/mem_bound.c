#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define SIZE (1 << 26)

volatile bool keep_running = true;

void* timer_thread(void* arg) {
    sleep(5);
    keep_running = false;
    return NULL;
}

int main() {
    size_t *data = malloc(SIZE * sizeof(size_t));
    if (!data) return 1;

    for (size_t i = 0; i < SIZE; i++) data[i] = i;
    for (size_t i = 0; i < SIZE; i++) {
        size_t j = i + rand() / (RAND_MAX / (SIZE - i) + 1);
        size_t t = data[j];
        data[j] = data[i];
        data[i] = t;
    }

    pthread_t tid;
    size_t curr = 0;

    pthread_create(&tid, NULL, timer_thread, NULL);
    printf("Starting Memory Bound (5s)...\n");

    while (keep_running) {
        curr = data[curr];
        curr = data[curr];
        curr = data[curr];
        curr = data[curr];
    }

    pthread_join(tid, NULL);
    printf("Done. Final index: %zu\n", curr);
    free(data);
    return 0;
}
