#include <math.h>
#include <pthread.h>
#include <stdlib.h>
#include <threads.h>


pthread_mutex_t m1, m2;


void *thread_a(void*) {
    pthread_mutex_lock(&m1);
    pthread_mutex_lock(&m2);

    for (int i = 0; i < 10000; ++i) {
        sin((double)rand() / RAND_MAX);
    }

    pthread_mutex_unlock(&m1);
    pthread_mutex_unlock(&m2);
    return NULL;
}


void *thread_b(void*) {
    pthread_mutex_lock(&m2);
    pthread_mutex_lock(&m1);

    for (int i = 0; i < 10000; ++i) {
        sin((double)rand() / RAND_MAX);
    }

    pthread_mutex_unlock(&m2);
    pthread_mutex_unlock(&m1);
    return NULL;
}

int main() {
    pthread_t a;
    pthread_t b;
    pthread_create(&a, NULL, &thread_a, NULL);
    pthread_create(&b, NULL, &thread_b, NULL);
    pthread_join(a, NULL);
    pthread_join(b, NULL);
    return 0;
}
