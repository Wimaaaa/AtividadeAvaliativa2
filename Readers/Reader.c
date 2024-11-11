#include <stdio.h>
#include <pthread.h>

pthread_mutex_t resource_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t writer_cond = PTHREAD_COND_INITIALIZER;
int readers = 0;

void *reader(void *arg) {
    long id = (long)arg;

    //
    pthread_mutex_lock(&resource_lock);
    readers++;
    pthread_mutex_unlock(&resource_lock);

    printf("Leitor %ld está lendo\n", id);
    printf("Total de leitores lendo: %d\n", readers);

    pthread_mutex_lock(&resource_lock);
    readers--;
    if (readers == 0) {
        printf("Total de leitores: %d\nLivre para escrita. \n", readers);
        //sinaliza que não há nenhuma thread lendo, portanto está livre para escrita
        pthread_cond_signal(&writer_cond);
    }
    pthread_mutex_unlock(&resource_lock);

    return NULL;
}

void *writer(void *arg) {
    long id = (long)arg;

    pthread_mutex_lock(&resource_lock);
    while (readers > 0){
        //espera não ter nenhuma thread de leitura para escrever
        pthread_cond_wait(&writer_cond, &resource_lock);
    }
    printf("Escritor %ld está escrevendo\n", id);
    pthread_mutex_unlock(&resource_lock);

    return NULL;
}

int main() {
    pthread_t readers[5], writers[3];
    for (long i = 0; i < 5; i++) {
        pthread_create(&readers[i], NULL, reader, (void *)i);
    }
    for (long i = 0; i < 3; i++) {
        pthread_create(&writers[i], NULL, writer, (void *)i);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(writers[i], NULL);
    }

    pthread_exit(NULL);
    return 0;

}
