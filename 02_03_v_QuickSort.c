//SET-2
//Q3 Implement the (ii) Quick Sort.

#include <stdio.h>
#include <stdlib.h>

// ---------- Quick Sort Function ----------
void quicksort(long long a[], int low, int high) {
    int i = low, j = high;
    long long pivot = a[(low + high) / 2]; // Choose middle element as pivot
    long long temp;

    // Partitioning
    while (i <= j) {
        while (a[i] < pivot) i++;  // Find element greater than pivot
        while (a[j] > pivot) j--;  // Find element smaller than pivot
        if (i <= j) {
            // Swap a[i] and a[j]
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++; j--;
        }
    }

    // Recursively sort left and right subarrays
    if (low < j) quicksort(a, low, j);
    if (i < high) quicksort(a, i, high);
}

int main() {
    FILE *fp;
    char filename[100];
    long long *arr = NULL; // Dynamic array
    int capacity = 10, n = 0; // Initial capacity and number of elements

    // Allocate initial memory
    arr = (long long*) malloc(capacity * sizeof(long long));
    if (!arr) {
        printf("Memory allocation failed!\n");
        return 0;
    }

    // Get filename from user
    printf("Enter input filename: ");
    scanf("%s", filename);

    // Open file for reading
    fp = fopen(filename, "r");
    if (!fp) {
        printf("Error: File not found!\n");
        free(arr);
        return 0;
    }

    // Read numbers dynamically, reallocating memory if needed
    while (1) {
        if (n == capacity) {  // Double capacity if array is full
            capacity *= 2;
            arr = (long long*) realloc(arr, capacity * sizeof(long long));
            if (!arr) {
                printf("Memory reallocation failed!\n");
                fclose(fp);
                return 0;
            }
        }

        // Read a number, break loop if input is invalid
        if (fscanf(fp, "%lld", &arr[n]) != 1)
            break;

        n++;
    }
    fclose(fp);

    // ---------- Call Quick Sort ----------
    if (n > 0)
        quicksort(arr, 0, n - 1);

    // ---------- Print Sorted Array ----------
    printf("Sorted: ");
    for (int i = 0; i < n; i++)
        printf("%lld ", arr[i]);
    printf("\n");

    free(arr); // Free allocated memory
    return 0;
}

