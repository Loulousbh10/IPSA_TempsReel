The given code is an application written in C for an embedded system, utilizing the FreeRTOS (Real-Time Operating System) library.
The application involves the creation of tasks, a queue, and timers to simulate a system with asynchronous communication and periodic tasks. 
The tasks communicate through a queue, and some tasks are triggered periodically by timers.

## Code Structure
### Libraries and Definitions
In order to implement this code, I had to include standard C libraries such stdio.h, stdlib.h, pthreads.h and time.h, and some FreeRTOS-specific headers.
I defined 4 tasks, following the instructions of the practical work and tested them 1000 times to approximate the execution time for each task by running the bash script time.sh that you can find in this folder.

- The first task is a periodic task that prints that the system is working properly. This task is executed once every second (1000UL) and has the highest priority. The maximum execution time on 1000 iterations is 26.805 milliseconds.
- The second task is a periodic task that converts a fixed Fahrenheit temperature value into a Celsius temperature value and prints it. It is executed every 2 seconds (2000UL) and has the second highest priority. The maximum execution time on 1000 iterations is 24.858 milliseconds.
- The third task is a periodic task that multiply two fixed long int numbers and prints the result. It is executed every 3 seconds (3000UL) and has the third highest priority. The maximum execution time on 1000 iterations is 20.649 milliseconds.
- The fourth task is a periodic task that does a binary search of a fixed element to search in a list of 50 fixed elements. It is executed every 4 seconds (4000UL) and has the fourth highest priority. The maximum execution time on 1000 iterations is 27.297 milliseconds.

The period for the tasks were chosen arbitrarily to see every execution. If the tasks were executed more frequently, we could not see them, such as their priorities defined in mainQUEUE_RECEIVE_TASK_PRIORITY and mainQUEUE_SEND_TASK_PRIORITY.

### Schedulability
We need to verify that the tasks are schedulable by using the following formula :
$$\ \sum_{i=1}^n \frac{C_i}{T_i} \le n(2^{1/n} - 1) $$

By replacing the expression with or four tasks and their period and their maximum execution time, we get :
$$\ \frac{26.805 \times 10^{-3}}{1} + \frac{24.858  \times 10^{-3}}{2} + \frac{20.649 \times 10^{-3}}{3} + \frac{27.297  \times 10^{-3}}{4} \le 4(2^{1/4} - 1) $$
$$\ \iff 0.053 \le 0.757 $$ 

Since the inequality is correct, we can say that the tasks are schedulable.

### Creation of the queue
We create a queue xQueue that can contain our four tasks in it and we define values representing different values that can be sent from various sources (tasks and timers) to the queue. These constants are associated with specific tasks or timers, and they serve as identifiers or markers for the receiver task to distinguish the source of the data in the queue and execute the corresponding actions.

### Binary Search Function
Since one of the tasks is meant to proceed to a binary search, we define a binary search function that we will call later.
The binary search algorithm is a classic search algorithm for finding the position of a target element in a sorted array. The function uses a loop to iteratively narrow down the search range until the target is found or the range becomes empty. It calculates the middle index and the current search range, if the value of the middle index equals the target, it prints the index as an output, if the target is greater than the middle value, it adjusts the search range to the right half, If the target is smaller than the middle value, it adjusts the search range to the left half.
Finally, if the target is not found in the array, we print a message and the function return -1.
In our example, we have a sorted array of 50 numbers from 0 to 49 and want to find the target number, i.e. 12.

### Scheduler
The ipsa_sched function serves as the entry point for an embedded application using the FreeRTOS kernel. At the beginning, it defines a constant xTimerPeriod based on the frequency of a timer mainTIMER_SEND_FREQUENCY_MS.
The function then creates a queue xQueue for communication between tasks, with a specified length and data size. If the queue is successfully created, the function proceeds to create multiple tasks with different priorities.
These tasks include one to receive data from the queue prvQueueReceiveTask and three others to send data at regular intervals using tasks and timers prvQueueSendTask, prvQueueSendTask2, prvQueueSendTask3. 
Additionally, a timer xTimer is created, started, and associated with a callback function prvQueueSendTimerCallback that sends data to the queue. 
Finally, the FreeRTOS scheduler is started with vTaskStartScheduler().
The tasks and timers operate within an infinite loop, and the function is the main orchestrator for task and timer creation, as well as the initiation of the real-time operating system.

### Execution
The prvQueueReceiveTask function is a task designed to continuously receive data from the queue and execute different actions based on the values received. It begins by declaring a variable ulReceivedValue to store the data received from the queue and initializes a result variable. The function operates in an infinite loop (for (;;)), representing an ongoing real-time task.

Within the loop, the task uses the xQueueReceive function to wait indefinitely for data in the queue. When data is received, it checks the value ulReceivedValue against predefined constants like mainVALUE_SENT_FROM_TASK, mainVALUE_SENT_FROM_TIMER, etc., to determine the source of the data. Depending on the received value, the task performs distinct actions.
These actions include printing messages to the console, converting temperature values, multiplying large numbers, conducting a binary search on an array, or handling unexpected messages.

For instance, if the received value corresponds to mainVALUE_SENT_FROM_TASK, the task prints a message indicating that the system is working properly.
If the value corresponds to mainVALUE_SENT_FROM_TIMER, it calculates and prints the temperature conversion from Fahrenheit to Celsius.
Similarly, for other values, it conducts specific operations such as multiplying large numbers or performing a binary search on an ordered array.
This task is a central component in the overall application, responsible for reacting to different messages received through the queue and executing the corresponding functionality.

### Additional notes
The ipsa_sched.c file has to be in the following folder : "FreeRTOSv202107.00/FreeRTOS/Demo/Posix_GCC" in order to compile and execute correctly.
In the main.c file, you have to change the function call (line 124) if using your files.
To compile the folder, make sure you are in the folder given before and type "make".
To execute the scheduler, type "./build/posix_demo" and the scheduler will start.
Type Ctrl + C to interrupt the execution.
