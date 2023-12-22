#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex;

void *printHelloWorld(void *arg) {
    sem_wait(&mutex);

    printf("Hello World\n");

    sem_post(&mutex);

    return NULL;
}

int main() {
    sem_init(&mutex, 0, 1);

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, printHelloWorld, NULL);

    pthread_join(thread_id, NULL);

    sem_destroy(&mutex);

    return 0;
}

