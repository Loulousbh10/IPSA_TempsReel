# Abstract
This code is an example of a multi-tasking application using the FreeRTOS (Real-Time Operating System) kernel in C. The application defines four tasks with different priorities, each performing a specific operation at regular intervals. These tasks communicate through a queue, and their execution demonstrates the capabilities of task scheduling in a real-time system. This report provides insights into the code structure, execution environment, and key functionalities of the application.

# Introduction
The code implements a simple real-time system using FreeRTOS, where four tasks with varying priorities are created. Each task performs a specific operation, such as printing messages, converting temperatures, performing arithmetic operations, and conducting a binary search on an array. These tasks communicate through a queue, showcasing the task scheduling capabilities of the FreeRTOS kernel.

# Method
## Code Structure
The application consists of five tasks: ipsa_sched, which initializes the system and starts the FreeRTOS scheduler, and four tasks (prvQueueSendTask1 to prvQueueSendTask4) with different priorities. Each task simulates a specific operation and periodically sends data to a shared queue.

The priorities of the tasks are defined using preprocessor directives, ranging from highest priority (TASK_PRIORITY1) to lowest priority (TASK_PRIORITY4). The tasks are created using the xTaskCreate function, specifying the task function, stack size, and priority.

A queue (xQueue) is created with a specific length for communication between tasks using xQueueCreate. Each task sends data to this queue at regular intervals using vTaskDelay.

The tasks include operations such as printing a system message, converting temperatures, performing arithmetic multiplication, and conducting a binary search on an array. These operations showcase different types of computations and demonstrate the concurrent execution of tasks.

## Definitions of the tasks
The codes includes the definition of the following tasks. We calculate the Worst Case Execution Time (WCET) by executing each task 1000 times by executing the bash file time.sh. This method is not the most precise way to estimate the WCET but since the execution times are in milliseconds and the periods in seconds, it is not a problem.

- The first task is a periodic task that prints that the system is working properly. This task is executed once every second and has the highest priority. The maximum execution time on 1000 iterations is 26.805 milliseconds.
- The second task is a periodic task that converts a fixed Fahrenheit temperature value into a Celsius temperature value and prints it. It is executed every 2 seconds and has the second highest priority. The maximum execution time on 1000 iterations is 24.858 milliseconds.
- The third task is a periodic task that multiply two fixed long int numbers and prints the result. It is executed every 3 seconds and has the third highest priority. The maximum execution time on 1000 iterations is 20.649 milliseconds.
- The fourth task is a periodic task that does a binary search of a fixed element to search in a list of 50 fixed elements. It is executed every 4 seconds and has the fourth highest priority. The maximum execution time on 1000 iterations is 27.297 milliseconds.

The periods for the tasks were chosen to see them being printed in the terminal but we could have chosen a higher frequency of execution.

## Schedulability
Schedulability analysis was conducted to ensure that the tasks could be scheduled within their defined periods. The analysis involved verifying the mathematical formula against the execution times and periods of each task.
$$\ \sum_{i=1}^n \frac{C_i}{T_i} \le 1 $$

By replacing the expression with or four tasks and their period and their maximum execution time, we get :
$$\ \frac{26.805 \times 10^{-3}}{1} + \frac{24.858  \times 10^{-3}}{2} + \frac{20.649 \times 10^{-3}}{3} + \frac{27.297  \times 10^{-3}}{4} \le 1 $$
$$\ \iff 0.053 \le 1 $$ 

Since the inequality is correct, we can say that the tasks are schedulable.

# Results
The tasks run concurrently, with the FreeRTOS scheduler managing their execution based on their defined priorities. The system messages, temperature conversions, arithmetic operations, and binary search results are printed periodically. The binary search function, for example, demonstrates the ability to perform complex computations without blocking the execution of other tasks.

In summary, the code illustrates a basic multi-tasking application using FreeRTOS, where tasks with different priorities perform diverse operations concurrently in a real-time environment. The application demonstrates the advantages of task scheduling in embedded systems, allowing for efficient and timely execution of various tasks.

### Additional notes
- [ ] Make sure the ipsa_sched.c file is in the following folder : "FreeRTOSv202107.00/FreeRTOS/Demo/Posix_GCC".
- [ ] In the main.c file, you have to change the function call (line 124) if you are using your files.
- [ ] To compile the folder, make sure you are in the folder given before and type "make".
- [ ] To execute the scheduler, type "./build/posix_demo" and the scheduler will start.
- [ ] Type Ctrl + C to interrupt the execution. 
