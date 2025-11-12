/* SET-5
   Q11. Implement Dijkstra’s algorithm for the shortest path problem. */

#include <stdio.h>
#include <limits.h>

#define MAX 100  // Maximum number of vertices

// Function to find the vertex with minimum distance value
int minDistance(int dist[], int visited[], int n) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < n; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to print the distances
void printSolution(int dist[], int n) {
    printf("\nVertex\tDistance from Source\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\n", i, dist[i]);
}

// Dijkstra's algorithm
void dijkstra(int graph[MAX][MAX], int src, int n) {
    int dist[MAX];     // Shortest distance from source
    int visited[MAX];  // Visited vertices

    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, visited, n);
        if (u == -1) break; // No reachable vertex left
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] > 0 && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printSolution(dist, n);
}

int main() {
    int n, src;

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

    printf("Enter source vertex (0 to %d): ", n - 1);
    if (scanf("%d", &src) != 1 || src < 0 || src >= n) {
        printf("Invalid source vertex.\n");
        return 1;
    }

    dijkstra(graph, src, n);
    return 0;
}

