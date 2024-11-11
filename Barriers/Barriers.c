#include <stdio.h>
#include <pthread.h>

#define THREAD_COUNT 5

pthread_barrier_t barrier;

void *thread_task(void *arg) {
    long id = (long)arg;

    printf("Thread %ld chegou na barreira\n", id);

    //threads aguardam na barreira até a chegada de todas
    pthread_barrier_wait(&barrier);
    printf("Thread %ld passou da barreira\n", id);

    return NULL;
}

int main() {
    pthread_t threads[THREAD_COUNT];

    pthread_barrier_init(&barrier, NULL, THREAD_COUNT);

    for (long i = 0; i < THREAD_COUNT; i++) {
        pthread_create(&threads[i], NULL, thread_task, (void *)i);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_barrier_destroy(&barrier);

    return 0;
}
