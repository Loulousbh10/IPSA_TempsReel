#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Declare a semaphore
sem_t mySemaphore;

// Function to be executed by the thread
void *threadFunction(void *arg) {
    // Print "Hello World" from the thread
    printf("Hello World\n");

    return NULL;
}

int main() {
    // Initialize the semaphore with an initial value of 0
    sem_init(&mySemaphore, 0, 0);

    // Create a thread
    pthread_t myThread;
    if (pthread_create(&myThread, NULL, threadFunction, NULL) != 0) {
        perror("Error creating thread");
        exit(EXIT_FAILURE);
    }

    // Print the first line
    printf("Line 1\n");

    // Sleep for 10 seconds
    sleep(10);

    // Release the semaphore to allow the thread to print "Hello World"
    sem_post(&mySemaphore);

    // Wait for the thread to finish
    if (pthread_join(myThread, NULL) != 0) {
        perror("Error joining thread");
        exit(EXIT_FAILURE);
    }

    // Destroy the semaphore
    sem_destroy(&mySemaphore);

    return 0;
}
