/* Library includes. */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

/* Local includes. */
#include "console.h"
extern int binarySearch(int arr[], int low, int high, int target);

/* Priorities at which the tasks are created. */
#define mainQUEUE_RECEIVE_TASK_PRIORITY    ( tskIDLE_PRIORITY + 4 )
#define mainQUEUE_SEND_TASK_PRIORITY       ( tskIDLE_PRIORITY + 1 )
#define mainQUEUE_SEND_TASK_PRIORITY2      ( tskIDLE_PRIORITY + 2 )
#define mainQUEUE_SEND_TASK_PRIORITY3      ( tskIDLE_PRIORITY + 3 )

/* The rate at which data is sent to the queue.  The times are converted from
 * milliseconds to ticks using the pdMS_TO_TICKS() macro. */
#define mainTASK_SEND_FREQUENCY_MS         pdMS_TO_TICKS( 500UL )
#define mainTIMER_SEND_FREQUENCY_MS        pdMS_TO_TICKS( 1500UL )
#define mainTIMER_SEND_FREQUENCY_MS2       pdMS_TO_TICKS( 3000UL )
#define mainTIMER_SEND_FREQUENCY_MS3       pdMS_TO_TICKS( 4500UL )

/* The number of items the queue can hold at once. */
#define mainQUEUE_LENGTH                   ( 4 )

/* The values sent to the queue receive task from the queue send task and the
 * queue send software timer respectively. */
#define mainVALUE_SENT_FROM_TASK           ( 100UL )
#define mainVALUE_SENT_FROM_TIMER          ( 200UL )
#define mainVALUE_SENT_FROM_TIMER2         ( 300UL )
#define mainVALUE_SENT_FROM_TIMER3         ( 400UL )

/*-----------------------------------------------------------*/

// Task functions
static void prvQueueReceiveTask(void *pvParameters);
static void prvQueueSendTask(void *pvParameters);
static void prvQueueSendTask2(void *pvParameters);
static void prvQueueSendTask3(void *pvParameters);

// Timer callback functions
static void prvQueueSendTimerCallback(TimerHandle_t xTimerHandle);
static void prvQueueSendTimerCallback2(TimerHandle_t xTimerHandle);
static void prvQueueSendTimerCallback3(TimerHandle_t xTimerHandle);

/*-----------------------------------------------------------*/

/* The queue used by both tasks. */
static QueueHandle_t xQueue = NULL;

/* A software timer that is started from the tick hook. */
static TimerHandle_t xTimer = NULL;

/*-----------------------------------------------------------*/

// Entry point of the application
void ipsa_sched(void) {
    const TickType_t xTimerPeriod = mainTIMER_SEND_FREQUENCY_MS;

    // Create a queue with a specific length for communication between tasks
    xQueue = xQueueCreate(mainQUEUE_LENGTH, sizeof(uint32_t));

    if (xQueue != NULL) {
        // Create tasks with different priorities
        xTaskCreate(prvQueueReceiveTask, "Rx", configMINIMAL_STACK_SIZE, NULL, mainQUEUE_RECEIVE_TASK_PRIORITY, NULL);
        xTaskCreate(prvQueueSendTask, "TX", configMINIMAL_STACK_SIZE, NULL, mainQUEUE_SEND_TASK_PRIORITY, NULL);
        xTaskCreate(prvQueueSendTask2, "TX2", configMINIMAL_STACK_SIZE, NULL, mainQUEUE_SEND_TASK_PRIORITY2, NULL);
        xTaskCreate(prvQueueSendTask3, "TX3", configMINIMAL_STACK_SIZE, NULL, mainQUEUE_SEND_TASK_PRIORITY3, NULL);

        // Create a timer and start it
        xTimer = xTimerCreate("Timer", xTimerPeriod, pdTRUE, NULL, prvQueueSendTimerCallback);
        if (xTimer != NULL) {
            xTimerStart(xTimer, 0);
        }

        // Start the FreeRTOS scheduler
        vTaskStartScheduler();
    }

    for (;;) {
    }
}

/*-----------------------------------------------------------*/

// Task to send data at regular intervals
static void prvQueueSendTask(void *pvParameters) {
    TickType_t xNextWakeTime;
    const TickType_t xBlockTime = mainTASK_SEND_FREQUENCY_MS;
    const uint32_t ulValueToSend = mainVALUE_SENT_FROM_TASK;

    (void)pvParameters;
    xNextWakeTime = xTaskGetTickCount();

    for (;;) {
        // Delay until the next wake time
        vTaskDelayUntil(&xNextWakeTime, xBlockTime);

        // Send a value to the queue
        xQueueSend(xQueue, &ulValueToSend, 0U);
    }
}

/*-----------------------------------------------------------*/

// Task to send data at intervals based on a timer
static void prvQueueSendTask2(void *pvParameters) {
    TickType_t xNextWakeTime;
    const TickType_t xBlockTime = mainTIMER_SEND_FREQUENCY_MS2;
    const uint32_t ulValueToSend = mainVALUE_SENT_FROM_TIMER2;

    (void)pvParameters;
    xNextWakeTime = xTaskGetTickCount();

    for (;;) {
        // Delay until the next wake time
        vTaskDelayUntil(&xNextWakeTime, xBlockTime);

        // Send a value to the queue
        xQueueSend(xQueue, &ulValueToSend, 0U);
    }
}
/*-----------------------------------------------------------*/

// Task to send data at intervals based on another timer
static void prvQueueSendTask3(void *pvParameters) {
    TickType_t xNextWakeTime;
    const TickType_t xBlockTime = mainTIMER_SEND_FREQUENCY_MS3;
    const uint32_t ulValueToSend = mainVALUE_SENT_FROM_TIMER3;

    (void)pvParameters;
    xNextWakeTime = xTaskGetTickCount();

    for (;;) {
        // Delay until the next wake time
        vTaskDelayUntil(&xNextWakeTime, xBlockTime);

        // Send a value to the queue
        xQueueSend(xQueue, &ulValueToSend, 0U);
    }
}
/*-----------------------------------------------------------*/

// Timer callback function to send data to the queue
static void prvQueueSendTimerCallback(TimerHandle_t xTimerHandle) {
    const uint32_t ulValueToSend = mainVALUE_SENT_FROM_TIMER;

    (void)xTimerHandle;

    // Send a value to the queue
    xQueueSend(xQueue, &ulValueToSend, 0U);
}
/*-----------------------------------------------------------*/

// Similar callback functions for other timers
static void prvQueueSendTimerCallback2(TimerHandle_t xTimerHandle) {
    const uint32_t ulValueToSend = mainVALUE_SENT_FROM_TIMER2;

    (void)xTimerHandle;

    // Send a value to the queue
    xQueueSend(xQueue, &ulValueToSend, 0U);
}
/*-----------------------------------------------------------*/

static void prvQueueSendTimerCallback3(TimerHandle_t xTimerHandle) {
    const uint32_t ulValueToSend = mainVALUE_SENT_FROM_TIMER3;

    (void)xTimerHandle;

    // Send a value to the queue
    xQueueSend(xQueue, &ulValueToSend, 0U);
}
/*-----------------------------------------------------------*/

// Task to receive data from the queue and perform different actions based on the received value
static void prvQueueReceiveTask(void *pvParameters) {
    uint32_t ulReceivedValue;

    (void)pvParameters;

    for (;;) {
        // Receive a value from the queue, wait indefinitely if the queue is empty
        xQueueReceive

(xQueue, &ulReceivedValue, portMAX_DELAY);

        // Check the received value and perform corresponding actions
        if (ulReceivedValue == mainVALUE_SENT_FROM_TASK) {
            console_print("The system is working properly.\n");
        }
        else if (ulReceivedValue == mainVALUE_SENT_FROM_TIMER) {
            double celsius;
            double fahrenheit = 98.60;
            celsius = (fahrenheit - 32.0) * 5.0 / 9.0;
            printf("The temperature in Fahrenheit is %.2f, so the temperature in Celsius is: %.2f\n", fahrenheit, celsius);
        }
        else if (ulReceivedValue == mainVALUE_SENT_FROM_TIMER2) {
            long bignumber1 = 4859648569;
            long bignumber2 = 4894825966;
            int sum = bignumber1 + bignumber2;
            printf("The result of the sum is: %.2d\n", sum);
        }
        else if (ulReceivedValue == mainVALUE_SENT_FROM_TIMER3) {
            int arr[50] = {};
            for (int i = 0; i < 50; i++) {
                arr[i] = rand() % 101;
            }

            printf("The binary search will be done on the following array: ");
            for (int i = 0; i < 50; ++i) {
                printf("%d ", arr[i]);
            }
            printf("\n");

            int size = sizeof(arr) / sizeof(arr[0]);
            int target = 15;
            int result = binarySearch(arr, 0, size - 1, target);

            if (result != -1) {
                printf("Element %d found at index %d.\n", target, result);
            }else{
                printf("Element %d not found in the array.\n", target);
            }
        }else{
            console_print("Unexpected message\n");
        }
    }
}
