/* SET-2 
  Q4.  Implement merge sort without using recursion. You may use a stack data structure in order to keep track
       of dividing and conquering the task. This will be a top-down approach of solving the problem. */

#include <stdio.h>
#include <stdlib.h>

// Structure to store left and right indexes of subarrays
typedef struct {
    int left, right;
} Node;

// Merge function
void merge(long long arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    long long *L = (long long*) malloc(n1 * sizeof(long long));
    long long *R = (long long*) malloc(n2 * sizeof(long long));

    if (!L || !R) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    // Merge the two arrays
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

// Non-Recursive Merge Sort using stack (Top-Down)
void mergeSortStack(long long arr[], int n) {
    Node *stack = (Node*) malloc(sizeof(Node) * n * 2);
    int top = -1;

    // Push the whole array onto stack
    stack[++top].left = 0;
    stack[top].right = n - 1;

    // Process stack until empty
    while (top >= 0) {
        Node current = stack[top--];

        int l = current.left;
        int r = current.right;

        // If more than one element, divide
        if (l < r) {
            int m = (l + r) / 2;

            // Push left part
            stack[++top].left = l;
            stack[top].right = m;

            // Push right part
            stack[++top].left = m + 1;
            stack[top].right = r;

            // Merge after pushing
            merge(arr, l, m, r);
        }
    }

    free(stack);
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
        mergeSortStack(arr, n);

    printf("Sorted: ");
    for (int i = 0; i < n; i++)
        printf("%lld ", arr[i]);
    printf("\n");

    free(arr);
    return 0;
}

