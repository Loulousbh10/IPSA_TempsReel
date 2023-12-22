#include <stdio.h>

// Binary search function
int binarySearch(int arr[], int low, int high, int target) {
    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Check if the target is present at the middle
        if (arr[mid] == target)
            return mid;

        // If the target is greater, ignore the left half
        else if (arr[mid] < target)
            low = mid + 1;

        // If the target is smaller, ignore the right half
        else
            high = mid - 1;
    }

    // If the target is not present in the array
    return -1;
}

int main() {
    // Create an ordered list (sorted array)
    int arr[] = {2, 4, 7, 12, 16, 21, 27, 34, 42, 50};
    int size = sizeof(arr) / sizeof(arr[0]);

    // Value to search for
    int target;
    printf("Enter value to find : \n");
	scanf("%d", &target);

    // Perform binary search
    int result = binarySearch(arr, 0, size - 1, target);

    // Display the result
    if (result != -1)
        printf("Element %d found at index %d.\n", target, result);
    else
        printf("Element %d not found in the array.\n", target);

    return 0;
}

