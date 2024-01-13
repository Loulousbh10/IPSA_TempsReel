#include <stdio.h>

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
	int arr[50] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49};
    printf("The binary search will be done on the following array: ");
    for (int i = 0; i < 50; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int result = binarySearch(arr, 0, 49, 12); // Provide correct arguments
    if (result != -1) {
        printf("Element 12 found at index %d.\n");
    } else {
        printf("Element 12 not found in the array.\n");
    }
}


