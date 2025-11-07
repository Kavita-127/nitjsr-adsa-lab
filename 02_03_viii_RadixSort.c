#include <stdio.h>
#include <stdlib.h>

// Get maximum value in array
long long getMax(long long arr[], int n) {
    long long max = arr[0];
    for(int i = 1; i < n; i++)
        if (arr[i] > max) max = arr[i];
    return max;
}

// Counting sort for each digit
void countSort(long long arr[], int n, long long exp) {
    long long *output = (long long*) malloc(n * sizeof(long long));
    int i, count[10] = {0};

    for (i = 0; i < n; i++)
        count[(arr[i]/exp)%10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i-1];

    for (i = n-1; i >=0; i--) {
        output[count[(arr[i]/exp)%10]-1] = arr[i];
        count[(arr[i]/exp)%10]--;
    }

    for (i = 0; i < n; i++) arr[i] = output[i];
    free(output);
}

void radixsort(long long arr[], int n) {
    long long m = getMax(arr, n);
    for (long long exp = 1; m/exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

int main() {
    FILE *fp;
    char filename[100];
    long long *arr = NULL;
    int capacity = 10, n = 0;

    arr = (long long*) malloc(capacity * sizeof(long long));
    if (!arr) { printf("Memory allocation failed!\n"); return 0; }

    printf("Enter input filename: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");
    if (!fp) { printf("File not found!\n"); free(arr); return 0; }

    while (1) {
        if (n == capacity) { capacity *= 2; arr = (long long*) realloc(arr, capacity*sizeof(long long));
            if (!arr) { printf("Memory reallocation failed!\n"); fclose(fp); return 0; } }
        if (fscanf(fp, "%lld",&arr[n]) != 1) break;
        n++;
    }
    fclose(fp);

    if (n > 0) radixsort(arr, n);

    printf("Sorted: ");
    for (int i = 0; i < n; i++) printf("%lld ", arr[i]);
    printf("\n");
    free(arr);
    return 0;
}
