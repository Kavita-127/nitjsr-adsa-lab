#include <stdio.h>

// Function to return the maximum of two numbers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Backtracking function for 0/1 Knapsack
int knapsack(int W, int wt[], int val[], int n, int index, int currWeight, int currProfit) {
    // If weight exceeds capacity, invalid choice
    if (currWeight > W)
        return 0;

    // If all items are processed
    if (index == n)
        return currProfit;

    // Include current item
    int include = knapsack(W, wt, val, n, index + 1, currWeight + wt[index], currProfit + val[index]);

    // Exclude current item
    int exclude = knapsack(W, wt, val, n, index + 1, currWeight, currProfit);

    // Return the best of both choices
    return max(include, exclude);
}

int main() {
    int n, W;

    printf("Enter the number of items: ");
    scanf("%d", &n);

    int val[n], wt[n];

    printf("\nEnter the values of %d items:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Value of item %d: ", i + 1);
        scanf("%d", &val[i]);
    }

    printf("\nEnter the weights of %d items:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Weight of item %d: ", i + 1);
        scanf("%d", &wt[i]);
    }

    printf("\nEnter the capacity of the knapsack: ");
    scanf("%d", &W);

    int maxProfit = knapsack(W, wt, val, n, 0, 0, 0);

    printf("\n---------------------------------------\n");
    printf("Maximum Profit that can be obtained = %d\n", maxProfit);
    printf("---------------------------------------\n");

    return 0;
}
