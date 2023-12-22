#include <stdio.h>

int main() {
    // Create an array
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);

    // Value to search for
    int target;
    printf("Enter value to find : \n");
	scanf("%d", &target);

    // Search for the value in the array
    int found = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i] == target) {
            found = 1;
            break;
        }
    }

    // Display the result
    if (found) {
        printf("Value %d found in the array.\n", target);
    } else {
        printf("Value %d not found in the array.\n", target);
    }

    return 0;
}

