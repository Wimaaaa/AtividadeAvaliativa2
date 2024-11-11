#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define THREAD_COUNT 5

pthread_barrier_t barrier;

void *thread_task(void *arg) {
    long id = *(long *)arg;
    free(arg); // Libera a memória alocada para o argumento
    printf("Thread %ld chegou na barreira\n", id);
    pthread_barrier_wait(&barrier);
    printf("Thread %ld passou da barreira\n", id);
    return NULL;
}

int main() {
    pthread_t threads[THREAD_COUNT];

    // Inicializa a barreira
    pthread_barrier_init(&barrier, NULL, THREAD_COUNT);

    // Cria as threads
    for (long i = 0; i < THREAD_COUNT; i++) {
        long *arg = malloc(sizeof(long)); // Aloca memória para o argumento
        *arg = i;
        pthread_create(&threads[i], NULL, thread_task, arg);
    }

    // Espera todas as threads terminarem
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destrói a barreira
    pthread_barrier_destroy(&barrier);

    return 0;
}
