//SET-2
//Q3 Implement the (ii) Selection Sort

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char filename[100];
    long long *arr = NULL;
    int capacity = 10, n = 0;

    arr = (long long*) malloc(capacity * sizeof(long long));
    if (!arr) {
        printf("Memory allocation failed!\n");
        return 0;
    }

    printf("Enter input filename: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");
    if (!fp) {
        printf("Error: File not found!\n");
        free(arr);
        return 0;
    }

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

    // ---------- Selection Sort ----------
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j; // Find index of minimum element
        }
        if (minIndex != i) { // Swap if needed
            long long temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }

    // ---------- Print Sorted Array ----------
    printf("Sorted: ");
    for (int i = 0; i < n; i++)
        printf("%lld ", arr[i]);
    printf("\n");

    free(arr);
    return 0;
}

