#include <stdio.h>

// Function to implement Greedy Coin Change
void coinChange(int coins[], int n, int amount) {
    int count[50] = {0};  // To store count of each coin
    int totalCoins = 0;

    printf("Making change for amount: %d\n\n", amount);

    for (int i = 0; i < n; i++) {
        count[i] = amount / coins[i];   // Number of coins of this denomination
        amount = amount - (count[i] * coins[i]);
        totalCoins += count[i];
    }

    printf("Coins used:\n");
    for (int i = 0; i < n; i++) {
        if (count[i] > 0)
            printf("%d x %d\n", coins[i], count[i]);
    }

    printf("\nTotal coins used: %d\n", totalCoins);
}

int main() {
    int n, amount;

    printf("Enter number of coin denominations: ");
    scanf("%d", &n);

    int coins[n];

    printf("Enter the coin denominations (in descending order):\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);

    printf("Enter the amount to make change for: ");
    scanf("%d", &amount);

    coinChange(coins, n, amount);

    return 0;
}
