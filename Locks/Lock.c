#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 4

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void *thread_func(void *arg) {
    int thread_id = *(int *)arg;

    // ordem de bloqueio: sempre lock1 seguido de lock2
    pthread_mutex_lock(&lock1);
    printf("Thread %d bloqueou lock1\n", thread_id);
    usleep(100000); // Pequeno atraso para demonstrar o uso dos locks

    pthread_mutex_lock(&lock2);
    printf("Thread %d bloqueou lock2\n", thread_id);

    // seção crítica simulada
    printf("Thread %d esta executando na secao critica\n", thread_id);

    // desbloqueia na ordem inversa
    pthread_mutex_unlock(&lock2);
    printf("Thread %d liberou lock2\n", thread_id);

    pthread_mutex_unlock(&lock1);
    printf("Thread %d liberou lock1\n", thread_id);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1; // Identificadores para cada thread
        pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
