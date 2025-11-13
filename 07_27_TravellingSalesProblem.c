/* SET-7
  Q27. Write a function to implement the travelling sales person problem. Prepare the table of running time for
      graphs containing 10, 20, 40, 60 and 100 nodes and draw graph problem-size versus execution time. */

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// Maximum number of nodes for DP solution
#define MAXN 20 

int n; // Number of cities
int dist[MAXN][MAXN]; // Adjacency matrix for distances
int memo[1 << MAXN][MAXN]; // Memoization table for dynamic programming

// Function to solve TSP using dynamic programming 
int tsp(int mask, int pos) {
    if (mask == (1 << n) - 1) {
        return dist[pos][0]; // Return to starting city (0)
    }
    if (memo[mask][pos] != -1) {
        return memo[mask][pos];
    }

    int ans = INT_MAX;
    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0) { // If city not visited
            int newCost = dist[pos][city] + tsp(mask | (1 << city), city);
            if (newCost < ans) {
                ans = newCost;
            }
        }
    }
    return memo[mask][pos] = ans;
}

// Function to generate a random distance matrix
void generateRandomDistances(int numNodes) {
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            if (i == j) {
                dist[i][j] = 0;
            } else {
                dist[i][j] = rand() % 100 + 1; // Random distances between 1 and 100
            }
        }
    }
}

int main() {
    printf("Nodes\tExecution Time (seconds)\n");

    int nodes[] = {10, 20, 40, 60, 100};

    for (int i = 0; i < sizeof(nodes) / sizeof(nodes[0]); i++) {
        n = nodes[i];
        if (n > MAXN) {
            printf("%d\tToo large for DP solution\n", n);
            continue;
        }

        generateRandomDistances(n);
        
        // Initialize memoization table
        for (int j = 0; j < (1 << n); j++) {
            for (int k = 0; k < n; k++) {
                memo[j][k] = -1;
            }
        }

        clock_t start_time = clock();
        int min_cost = tsp(1, 0); // Start from city 0, mask 1 (0001)
        clock_t end_time = clock();

        double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("%d\t%.6f\n", n, execution_time);
    }

    return 0;
}
