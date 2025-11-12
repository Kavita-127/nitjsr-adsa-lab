#include <stdio.h>
#include <limits.h>

#define MAX 100  // Maximum number of vertices

// Function to find the vertex with minimum key value
int minKey(int key[], int mstSet[], int n) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < n; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to print the MST
void printMST(int parent[], int graph[MAX][MAX], int n) {
    printf("\nEdge \tWeight\n");
    for (int i = 1; i < n; i++)
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
}

// Prim’s algorithm
void primMST(int graph[MAX][MAX], int n) {
    int parent[MAX];  // Array to store MST
    int key[MAX];     // Key values to pick minimum weight edge
    int mstSet[MAX];  // Boolean array to track vertices in MST

    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[0] = 0;      // Start from vertex 0
    parent[0] = -1;  // First node is root

    for (int count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet, n);
        mstSet[u] = 1;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph, n);
}

int main() {
    int n;

    printf("Enter number of vertices (max %d): ", MAX);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    int graph[MAX][MAX];
    printf("Enter adjacency matrix (use 0 for no edge):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &graph[i][j]) != 1 || graph[i][j] < 0) {
                printf("Invalid input.\n");
                return 1;
            }
        }
    }

    primMST(graph, n);
    return 0;
}
