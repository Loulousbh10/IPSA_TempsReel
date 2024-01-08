#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Declare a semaphore
sem_t mySemaphore;

// Function to be executed by the thread
void *threadFunction(void *arg) {
    // Wait for the semaphore to be available
    sem_wait(&mySemaphore);

    // Print "Hello World" from the thread
    printf("Hello World\n");

    // Release the semaphore
    sem_post(&mySemaphore);

    return NULL;
}

int main() {
    // Initialize the semaphore with an initial value of 1
    sem_init(&mySemaphore, 0, 1);

    // Create three threads
    pthread_t thread1, thread2, thread3;
    
    if (pthread_create(&thread1, NULL, threadFunction, NULL) != 0 ||
        pthread_create(&thread2, NULL, threadFunction, NULL) != 0 ||
        pthread_create(&thread3, NULL, threadFunction, NULL) != 0) {
        perror("Error creating threads");
        exit(EXIT_FAILURE);
    }

    // Sleep for 10 seconds
    sleep(10);

    // Release the semaphore to allow all three threads to print "Hello World"
    sem_post(&mySemaphore);
    
    // Wait for the threads to finish
    if (pthread_join(thread1, NULL) != 0 ||
        pthread_join(thread2, NULL) != 0 ||
        pthread_join(thread3, NULL) != 0) {
        perror("Error joining threads");
        exit(EXIT_FAILURE);
    }

    // Destroy the semaphore
    sem_destroy(&mySemaphore);

    return 0;
}
