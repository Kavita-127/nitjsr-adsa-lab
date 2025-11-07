#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char filename[100];
    long long *arr = NULL;
    int capacity = 10, n = 0;

    // Allocate initial memory
    arr = (long long*) malloc(capacity * sizeof(long long));
    if (!arr) {
        printf("Memory allocation failed!\n");
        return 0;
    }

    // Get filename from user
    printf("Enter input filename: ");
    scanf("%s", filename);

    // Open file
    fp = fopen(filename, "r");
    if (!fp) {
        printf("Error: File not found!\n");
        free(arr);
        return 0;
    }

    // Read numbers from file dynamically
    while (1) {
        if (n == capacity) {
            capacity *= 2;
            arr = (long long*) realloc(arr, capacity * sizeof(long long));
            if (!arr) {
                printf("Memory reallocation failed!\n");
                fclose(fp);
                return 0;
            }
        }
        if (fscanf(fp, "%lld", &arr[n]) != 1)
            break;
        n++;
    }
    fclose(fp);

    // ---------- Bubble Sort ----------
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) { // Swap if current element is greater
                long long temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // ---------- Print Sorted Array ----------
    printf("Sorted: ");
    for (int i = 0; i < n; i++)
        printf("%lld ", arr[i]);
    printf("\n");

    free(arr); // Free memory
    return 0;
}
