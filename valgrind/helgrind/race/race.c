#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


int loser;

void *horse(void *thread_id) {
    for (int i = 0; i < 10000; ++i) {
        sin((double)rand() / RAND_MAX);
    }

    loser = *(int *)thread_id;
    return NULL;
}

int main() {
    loser = 0;
    pthread_t workers[2];
    int thread_ids[2];
    for (int t = 0 ; t < 2; ++t) {
        thread_ids[t] = t + 1;
        pthread_create(&workers[t], NULL, &horse, &thread_ids[t]);
    }

    for (int t = 0 ; t < 2; ++t) {
        pthread_join(workers[t], NULL);
    }

    printf("Losing horse: %d\n", loser);
    return 0;
}