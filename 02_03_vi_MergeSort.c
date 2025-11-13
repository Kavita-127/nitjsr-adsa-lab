/* SET-2
   Q3.Implement the (i) insertion sort, (ii) bubble sort, (iii) selection sort, (iv) shell sort, (v) quick sort, (vi)
      merge sort, (vii) heap sort, (viii) radix sort, (ix) counting sort, (x) bucket sort, (xi) radix exchange sort,
      and (xii) address calculation sort. */
// MERGE SORT

#include <stdio.h>
#include <stdlib.h>

// Merge two sorted subarrays a[l..m] and a[m+1..r]
void merge(long long a[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Allocate temporary arrays dynamically
    long long *L = (long long*) malloc(n1 * sizeof(long long));
    long long *R = (long long*) malloc(n2 * sizeof(long long));

    if (!L || !R) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++) L[i] = a[l + i];
    for (int j = 0; j < n2; j++) R[j] = a[m + 1 + j];

    // Merge the temp arrays back into a[l..r]
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }

    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];

    free(L); // Free temporary arrays
    free(R);
}

// Recursive merge sort
void mergesort(long long a[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergesort(a, l, m);
        mergesort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

int main() {
    FILE *fp;
    char filename[100];
    long long *arr = NULL;
    int capacity = 10, n = 0;

    // Dynamic array allocation
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

    // Read numbers dynamically
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

    // Sort the array
    if (n > 0)
        mergesort(arr, 0, n - 1);

    // Print sorted array
    printf("Sorted: ");
    for (int i = 0; i < n; i++)
        printf("%lld ", arr[i]);
    printf("\n");

    free(arr); // Free main array
    return 0;
}

