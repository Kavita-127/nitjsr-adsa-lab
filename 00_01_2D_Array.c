// Write a C program that creates a 2D array initialized with zeros and allows user to input the row, column and values to insert into the array.

#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows, cols;
    int r, c, value;
    int **arr;

    // Take size from user
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);

    // Allocate dynamic 2D array & initialize to 0
    arr = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        arr[i] = (int *)calloc(cols, sizeof(int));
    }

    printf("\n2D array created with all values initialized to 0.\n");

    // Allow user to insert values
    while (1) {
        printf("\nEnter row index (-1 to stop): ");
        scanf("%d", &r);

        if (r == -1)
            break;

        printf("Enter column index: ");
        scanf("%d", &c);
        printf("Enter value to insert: ");
        scanf("%d", &value);

        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            arr[r][c] = value;
            printf("Value inserted!\n");
        } else {
            printf("Invalid position! Try again.\n");
        }
    }

    // Print array with index labels
    printf("\nFinal 2D Array:\n");

    // Print column indexes
    printf("     ");
    for (int j = 0; j < cols; j++) {
        printf("%3d ", j);
    }
    printf("\n");

    // Print separator line
    printf("    ");
    for (int j = 0; j < cols; j++) {
        printf("----");
    }
    printf("\n");

    // Print row index + row values
    for (int i = 0; i < rows; i++) {
        printf("%3d |", i); // row index
        for (int j = 0; j < cols; j++) {
            printf("%3d ", arr[i][j]);
        }
        printf("\n");
    }

    // Free memory
    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}
