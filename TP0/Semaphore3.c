#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;

void *threadFunction1(void *arg) {
    // Wait for the semaphore (similar to sem_wait)
    sem_wait(&mutex);

    // Critical section
    printf("Thread 1 in critical section\n");

    // Simulate spending time in the critical section
    sleep(2);

    // Signal that the critical section is over (similar to sem_post)
    sem_post(&mutex);

    return NULL;
}

void *threadFunction2(void *arg) {
    // Wait for the semaphore (similar to sem_wait)
    sem_wait(&mutex);

    // Critical section
    printf("Thread 2 in critical section\n");

    // Simulate spending time in the critical section
    sleep(2);

    // Signal that the critical section is over (similar to sem_post)
    sem_post(&mutex);

    return NULL;
}

void *threadFunction3(void *arg) {
    // Wait for the semaphore (similar to sem_wait)
    sem_wait(&mutex);

    // Critical section
    printf("Thread 3 in critical section\n");

    // Simulate spending time in the critical section
    sleep(2);

    // Signal that the critical section is over (similar to sem_post)
    sem_post(&mutex);

    return NULL;
}


int main() {
    // Initialize the semaphore (mutex)
    sem_init(&mutex, 0, 1);

    // Create two threads
    pthread_t thread1, thread2, thread3;

    pthread_create(&thread1, NULL, threadFunction1, NULL);
    pthread_create(&thread2, NULL, threadFunction2, NULL);
    pthread_create(&thread3, NULL, threadFunction3, NULL);

    // Wait for the threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    // Destroy the semaphore
    sem_destroy(&mutex);

    return 0;
}

