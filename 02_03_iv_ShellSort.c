//SET-2
//Q3 Implement the (ii) Shell Sort.

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

    // ---------- Shell Sort ----------
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            long long temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
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

