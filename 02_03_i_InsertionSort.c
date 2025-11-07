//SET-2
//Q3 (i) INSERTION SORT

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;                 // File pointer for reading input file
    char filename[100];       // Array to store filename input from user
    long long *arr = NULL;    // Pointer for dynamic array to store numbers
    int capacity = 10, n = 0; // Initial capacity of array and count of numbers

    // Allocate initial memory for array
    arr = (long long*) malloc(capacity * sizeof(long long));
    if (!arr) {               // Check if memory allocation failed
        printf("Memory allocation failed!\n");
        return 0;
    }

    // Ask user to enter the name of the input file
    printf("Enter input filename: ");
    scanf("%s", filename);

    // Open the file in read mode
    fp = fopen(filename, "r");
    if (!fp) {                // If file doesn't exist, show error and exit
        printf("Error: File not found!\n");
        free(arr);            // Free allocated memory before exiting
        return 0;
    }

    // Read numbers from the file until end of file
    // Dynamically increase array size if needed
    while (1) {
        if (n == capacity) { // If array is full, double its capacity
            capacity *= 2;
            arr = (long long*) realloc(arr, capacity * sizeof(long long));
            if (!arr) {      // Check if reallocation failed
                printf("Memory reallocation failed!\n");
                fclose(fp);  // Close the file before exiting
                return 0;
            }
        }

        // Read a number from file, break loop if not a valid number
        if (fscanf(fp, "%lld", &arr[n]) != 1)
            break;

        n++; // Increment count of numbers read
    }
    fclose(fp); // Close the file after reading

    // ---------- Insertion Sort Algorithm ----------
    for (int i = 1; i < n; i++) {
        long long key = arr[i];  // Store current element as key
        int j = i - 1;

        // Move elements of arr[0..i-1] that are greater than key
        // one position ahead to make space for key
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key; // Place key at correct position
    }

    // ---------- Print Sorted Array ----------
    printf("Sorted: ");
    for (int i = 0; i < n; i++)
        printf("%lld ", arr[i]);
    printf("\n");

    free(arr); // Free dynamically allocated memory
    return 0;
}

