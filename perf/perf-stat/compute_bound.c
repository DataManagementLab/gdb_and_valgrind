#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

volatile bool keep_running = true;

void* timer_thread(void* arg) {
    sleep(5);
    keep_running = false;
    return NULL;
}

long long iter = (1LL << 32);

int main() {
    pthread_t thread_id;
    float a = 1.1, b = 1.2, c = 1.3;

    pthread_create(&thread_id, NULL, timer_thread, NULL);

    long long i = 0;
    while (i++ < iter) {
        a = a * b + c;
    }

    pthread_join(thread_id, NULL);

    printf("result: %f", a);
    return 0;
}
