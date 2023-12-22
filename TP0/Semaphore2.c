#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Global semaphore (mutex)
sem_t mutex;

// Function to be executed by the first thread
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

// Function to be executed by the second thread
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

int main() {
    // Initialize the semaphore (mutex)
    sem_init(&mutex, 0, 1);

    // Create two threads
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, threadFunction1, NULL);
    pthread_create(&thread2, NULL, threadFunction2, NULL);

    // Wait for the threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the semaphore
    sem_destroy(&mutex);

    return 0;
}

