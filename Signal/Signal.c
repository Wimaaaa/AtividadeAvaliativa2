#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int ready = 0;

void *worker(void *arg) {
    pthread_mutex_lock(&mutex);
    while (!ready) {
        //aguarda o sinal de que pode começar
        pthread_cond_wait(&cond, &mutex);
    }
    printf("Thread %ld recebeu o sinal para comecar\n", (long)arg);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t thread;

    pthread_create(&thread, NULL, worker, (void *)1);
    sleep(1); // Simula algum processamento

    pthread_mutex_lock(&mutex);
    ready = 1;
    //sinaliza que está pronto
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);

    pthread_join(thread, NULL);
    return 0;
}