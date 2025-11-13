#include <stdio.h>
#include <stdlib.h>

#define MAX_ITEMS 100
#define MAX_CAPACITY 1000

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n, W;

    printf("Enter number of items (max %d): ", MAX_ITEMS);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_ITEMS) {
        printf("Invalid number of items.\n");
        return 1;
    }

    int weight[n + 1], value[n + 1];
    printf("Enter weight and value of each item:\n");
    for (int i = 1; i <= n; i++) {
        if (scanf("%d %d", &weight[i], &value[i]) != 2 || weight[i] <= 0 || value[i] < 0) {
            printf("Invalid input.\n");
            return 1;
        }
    }

    printf("Enter knapsack capacity (max %d): ", MAX_CAPACITY);
    if (scanf("%d", &W) != 1 || W <= 0 || W > MAX_CAPACITY) {
        printf("Invalid knapsack capacity.\n");
        return 1;
    }

    // DP table
    int dp[n + 1][W + 1];

    // Initialize DP table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weight[i] <= w)
                dp[i][w] = max(value[i] + dp[i - 1][w - weight[i]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    printf("\nMaximum value in the knapsack: %d\n", dp[n][W]);

    //print items included in the knapsack
    printf("Items included (1-based index): ");
    int w = W;
    for (int i = n; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            printf("%d ", i);
            w -= weight[i];
        }
    }
    printf("\n");

    return 0;
}
