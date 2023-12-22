#include <stdio.h>
#include <unistd.h>

void task1() {
    printf("Task1\n");
    sleep(1);
}

void task2() {
    printf("Task2\n");
    sleep(1);
}

void task3() {
    printf("Task3\n");
    sleep(1);
}

int main() {

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 3; ++j) {
            switch (j) {
                case 0:
                    task1();
                    break;
                case 1:
                    task2();
                    break;
                case 2:
                    task3();
                    break;
                default:
                    break;
            }
        }
    }

    return 0;
}

