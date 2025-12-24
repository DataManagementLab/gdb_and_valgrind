#include <pthread.h>
#include <stdlib.h>
#include <threads.h>
#include <time.h>


pthread_mutex_t unlocked_mutex;
pthread_mutex_t locked_by_another_thread;


/**
 * Locks mutex but never unlocks it
 */
void *lock_mutex(void* noparam) {
    pthread_mutex_lock(&locked_by_another_thread);
    return NULL;
}

int main() {
    pthread_mutex_lock(&unlocked_mutex); // Lock it once for creation
    pthread_mutex_unlock(&unlocked_mutex);
    pthread_mutex_unlock(&unlocked_mutex); // Unlocking not locked mutex

    pthread_t thread1;
    pthread_create(&thread1, NULL,  &lock_mutex, NULL);
    struct timespec sleep_duration = {0, 100000000};
    nanosleep(&sleep_duration, &sleep_duration);
    pthread_mutex_unlock(&locked_by_another_thread); // Unlock mutex held by another thread

    return 0;
}
