#include <stdio.h>
#include <stdlib.h>

// Function to heapify a subtree rooted at index i
void heapify(long long arr[], int n, int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;
    long long temp;

    // Check if left child exists and is larger
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Check if right child exists and is larger
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Swap and continue heapifying if root is not largest
    if (largest != i) {
        temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapsort(long long arr[], int n) {
    // Build max heap
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        long long temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

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
        printf("File not found!\n");
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
        if (fscanf(fp, "%lld", &arr[n]) != 1) break;
        n++;
    }
    fclose(fp);

    // Perform Heap Sort
    if (n > 0) heapsort(arr, n);

    printf("Sorted: ");
    for (int i = 0; i < n; i++) printf("%lld ", arr[i]);
    printf("\n");

    free(arr);
    return 0;
}
