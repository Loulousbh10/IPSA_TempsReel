#include <stdio.h>
#include <time.h>

void printTimeElapsed() {
    clock_t start_time = clock();

    while (1) {
        clock_t current_time = clock();
        double elapsed_seconds = (double)(current_time - start_time) / CLOCKS_PER_SEC;

        printf("Time Elapsed: %.2f seconds\n", elapsed_seconds);

        // Wait for 1 second
        while ((clock() - current_time) / CLOCKS_PER_SEC < 1)
            ;
    }
}

int main() {
    printTimeElapsed();
    return 0;
}

