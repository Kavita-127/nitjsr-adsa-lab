#include <stdio.h>
#include <stdlib.h>

// Merge two sorted parts: arr[l..m] and arr[m+1..r]
void merge(long long arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;   // size of 1st half
    int n2 = r - m;       // size of 2nd half

    // Create temp arrays
    long long *L = (long long*) malloc(n1 * sizeof(long long));
    long long *R = (long long*) malloc(n2 * sizeof(long long));

    if (!L || !R) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    // Copy values into temporary arrays
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge L[] and R[] back into arr[]
    i = 0;   // index of L
    j = 0;   // index of R
    k = l;   // index of arr

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    // Copy remaining elements
    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

// Bottom-up merge sort
void mergeSortBottomUp(long long arr[], int n) {
    int size, left;

    /* 
       size = current size of subarrays being merged
       Start merging subarrays of size 1, then 2, then 4, 8...
    */
    for (size = 1; size < n; size *= 2) {

        for (left = 0; left < n - size; left += 2 * size) {

            int mid = left + size - 1;
            int right = left + (2 * size - 1);

            if (right >= n)
                right = n - 1;

            merge(arr, left, mid, right);
        }
    }
}

int main() {
    FILE *fp;
    char filename[100];
    long long *arr;
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

    if (n > 0)
        mergeSortBottomUp(arr, n);

    printf("Sorted: ");
    for (int i = 0; i < n; i++)
        printf("%lld ", arr[i]);
    printf("\n");

    free(arr);
    return 0;
}
