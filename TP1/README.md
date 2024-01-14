# Abstract
This report presents an embedded system application written in C, utilizing the FreeRTOS library for real-time task scheduling. The application involves the creation of tasks, a queue, and timers to simulate asynchronous communication and periodic tasks. Four tasks were implemented, each with a specific function, and their execution times were approximated. Schedulability analysis was performed to ensure the feasibility of the task schedule. The report also covers the creation of a queue, a binary search function, and the overall scheduler structure. Additionally, execution instructions for the code are provided.

# Introduction
The embedded system application utilizes FreeRTOS for real-time task scheduling. The tasks include periodic activities such as system status reporting, temperature conversion, multiplication of large numbers, and binary search. The code structure, task priorities, and execution times were carefully designed to simulate a real-world scenario. This report outlines the key components of the code and provides an overview of the execution environment.

# Method
## Code Structure
The code includes the definition of tasks, libraries, and constants necessary for the implementation. The four tasks were designed to execute periodically, and their priorities and execution times were detailed. The structure of the code was explained, and a script for approximating task execution times was mentioned.

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

## Queue and Binary Search
A queue (xQueue) was created to facilitate communication between tasks and timers. Constants were defined to identify the source of data in the queue. A binary search function was also implemented, adhering to classic binary search algorithms, to be utilized in one of the periodic tasks.

## Scheduler
The scheduler (ipsa_sched.c) serves as the entry point for the application. It creates a queue, initializes tasks with their fixed priorities, and starts a timer. The FreeRTOS scheduler is then initiated, orchestrating the execution of tasks and timers within an infinite loop.

# Results
The execution of tasks is coordinated by the scheduler, with the prvQueueReceiveTask function handling data received from the queue. Depending on the source of the data, the task performs specific actions, such as system status reporting, temperature conversion, number multiplication, or binary search. The execution of tasks was designed to demonstrate real-time behavior in a simulated environment.

# Conclusion
The embedded system application successfully demonstrates the utilization of FreeRTOS for real-time task scheduling. The tasks execute periodically, communicating through a queue, and the application includes features such as a binary search function. Schedulability analysis confirms the feasibility of the task schedule. This report provides insights into the code structure, execution environment, and key functionalities of the application.

### Additional notes
- [ ] Make sure the ipsa_sched.c file is in the following folder : "FreeRTOSv202107.00/FreeRTOS/Demo/Posix_GCC".
- [ ] In the main.c file, you have to change the function call (line 124) if you are using your files.
- [ ] To compile the folder, make sure you are in the folder given before and type "make".
- [ ] To execute the scheduler, type "./build/posix_demo" and the scheduler will start.
- [ ] Type Ctrl + C to interrupt the execution. 
