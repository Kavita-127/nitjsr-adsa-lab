#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int board[MAX][MAX];

// Function to check if a queen can be placed at board[row][col]
int isSafe(int row, int col, int n) {
    int i, j;

    // Check this row on left side
    for (i = 0; i < col; i++)
        if (board[row][i])
            return 0;

    // Check upper diagonal on left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return 0;

    // Check lower diagonal on left side
    for (i = row, j = col; i < n && j >= 0; i++, j--)
        if (board[i][j])
            return 0;

    return 1;
}

// Backtracking function to solve N-Queens
int solveNQueens(int col, int n) {
    if (col >= n)
        return 1;  // All queens placed successfully

    for (int i = 0; i < n; i++) {
        if (isSafe(i, col, n)) {
            board[i][col] = 1;  // Place queen

            if (solveNQueens(col + 1, n))
                return 1;  // Success

            board[i][col] = 0;  // Backtrack
        }
    }

    return 0;  // No place found in this column
}

// Function to print the board
void printBoard(int n) {
    printf("\nOne solution of %d-Queens problem:\n", n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;

    printf("Enter number of queens (max %d): ", MAX);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX) {
        printf("Invalid number of queens.\n");
        return 1;
    }

    // Initialize board
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = 0;

    if (solveNQueens(0, n))
        printBoard(n);
    else
        printf("No solution exists for %d queens.\n", n);

    return 0;
}
