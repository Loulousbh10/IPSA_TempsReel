/* Library includes. */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* Local includes. */
#include "console.h"

/* Priorities at which the tasks are created. */
#define TASK_PRIORITY1    ( tskIDLE_PRIORITY + 1 ) //Highest priority
#define TASK_PRIORITY2    ( tskIDLE_PRIORITY + 2 ) 
#define TASK_PRIORITY3    ( tskIDLE_PRIORITY + 3 )
#define TASK_PRIORITY4    ( tskIDLE_PRIORITY + 4 ) // Lowest priority

/* The rate at which data is sent to the queue.  The times are converted from
 * milliseconds to ticks using the pdMS_TO_TICKS() macro. */
#define FREQUENCY_MS1      pdMS_TO_TICKS( 1000UL ) // 1 second
#define FREQUENCY_MS2      pdMS_TO_TICKS( 2000UL ) // 2 seconds
#define FREQUENCY_MS3      pdMS_TO_TICKS( 3000UL ) // 3 seconds
#define FREQUENCY_MS4      pdMS_TO_TICKS( 4000UL ) // 4 seconds

/* The number of items the queue can hold at once. */
#define mainQUEUE_LENGTH                   ( 4 )

/*-----------------------------------------------------------*/

// Task functions
static void prvQueueSendTask1(void *pvParameters);
static void prvQueueSendTask2(void *pvParameters);
static void prvQueueSendTask3(void *pvParameters);
static void prvQueueSendTask4(void *pvParameters);

/*-----------------------------------------------------------*/

/* The queue used by all four tasks. */
static QueueHandle_t xQueue = NULL;

/*-----------------------------------------------------------*/

// Binary search function
int binarySearch(int arr[], int low, int high, int target) {
    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Check if the target is present at the middle
        if (arr[mid] == target) {
            printf("Element %d found at index %d.\n", target, mid);
            return mid;
        }

        // If the target is greater, ignore the left half
        else if (arr[mid] < target) {
            low = mid + 1;
        }

        // If the target is smaller, ignore the right half
        else {
            high = mid - 1;
        }
    }

    // If the target is not present in the array
    printf("Element %d not found in the array.\n", target);
    return -1;
}

/*-----------------------------------------------------------*/

// Entry point of the application
void ipsa_sched(void) {

    // Create a queue with a specific length for communication between tasks
    xQueue = xQueueCreate(mainQUEUE_LENGTH, sizeof(uint32_t));

    if (xQueue != NULL) {
        // Create tasks with different priorities
        xTaskCreate(prvQueueSendTask1, "TX1", configMINIMAL_STACK_SIZE, NULL, TASK_PRIORITY1, NULL);
        xTaskCreate(prvQueueSendTask2, "TX2", configMINIMAL_STACK_SIZE, NULL, TASK_PRIORITY2, NULL);
        xTaskCreate(prvQueueSendTask3, "TX3", configMINIMAL_STACK_SIZE, NULL, TASK_PRIORITY3, NULL);
        xTaskCreate(prvQueueSendTask4, "TX4", configMINIMAL_STACK_SIZE, NULL, TASK_PRIORITY4, NULL);

        // Start the FreeRTOS scheduler
        vTaskStartScheduler();
    }

    for (;;) {
    }
}

/*-----------------------------------------------------------*/

// Task to send data at regular intervals
static void prvQueueSendTask1(void *pvParameters) {
    const TickType_t xBlockTime = FREQUENCY_MS1;

    (void)pvParameters;

    for (;;) {
 		// Print the message
        console_print("The system is working properly.\n");
        
        //Simulate the task execution
        vTaskDelay( xBlockTime );
    }
}

/*-----------------------------------------------------------*/

// Task to send data at regular intervals
static void prvQueueSendTask2(void *pvParameters) {
    const TickType_t xBlockTime = FREQUENCY_MS2;

    (void)pvParameters;

    for (;;) {
 		// Converts the temperature from Fahrenheit to Celsius
        double celsius;
            double fahrenheit = 98.60;
            celsius = (fahrenheit - 32.0) * 5.0 / 9.0;
            printf("The temperature in Fahrenheit is %.2f, so the temperature in Celsius is: %.2f\n", fahrenheit, celsius);
        
        //Simulate the task execution
        vTaskDelay( xBlockTime );
    }
}

/*-----------------------------------------------------------*/

// Task to send data at regular intervals
static void prvQueueSendTask3(void *pvParameters) {
    const TickType_t xBlockTime = FREQUENCY_MS3;

    (void)pvParameters;

    for (;;) {
    		// Calculates the multiplication of two big numbers
			long bignumber1 = 4859648569;
            long bignumber2 = 4894825966;
            long long multiplication = bignumber1 * bignumber2;
            printf("The result of the sum is: %lld\n", multiplication);

        //Simulate the task execution
        vTaskDelay( xBlockTime );
    }
}

/*-----------------------------------------------------------*/

// Task to send data at regular intervals
static void prvQueueSendTask4(void *pvParameters) {
    const TickType_t xBlockTime = FREQUENCY_MS4;

    (void)pvParameters;

    for (;;) {
        	
        	int arr[50] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49};
			
            printf("The binary search will be done on the following array: ");
            for (int i = 0; i < 50; ++i) {
                printf("%d ", arr[i]);
            }
            printf("\n");

            int result = binarySearch(arr, 0, 49, 12);

        //Simulate the task execution
        vTaskDelay( xBlockTime );
    }
}
