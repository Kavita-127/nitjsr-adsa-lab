/* SET-7
   Q29. Write a program for determining whether there exists a Hamiltonian cycle in a graph with n vertices and
        e edges. */

#include <stdio.h>
#include <stdbool.h>

#define MAX 20  

int graph[MAX][MAX];
int path[MAX];
int n, e;

// Function to check if current vertex can be added to Hamiltonian path
bool isSafe(int v, int pos) {
    // Check if vertex is adjacent to previous vertex
    if (!graph[path[pos - 1]][v])
        return false;

    // Check if vertex has already been included
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

// Recursive utility to find Hamiltonian cycle
bool hamiltonianCycleUtil(int pos) {
    if (pos == n) {
        // Check if last vertex is connected to first
        return graph[path[pos - 1]][path[0]];
    }

    for (int v = 1; v < n; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;
            if (hamiltonianCycleUtil(pos + 1))
                return true;
            // Backtrack
        }
    }
    return false;
}

// Function to find Hamiltonian cycle
bool hamiltonianCycle() {
    path[0] = 0;  // start from vertex 0
    return hamiltonianCycleUtil(1);
}

int main() {
    printf("Enter number of vertices (n): ");
    scanf("%d", &n);
    if (n > MAX) {
        printf("n too large! Use n <= %d for reasonable runtime.\n", MAX);
        return 0;
    }

    printf("Enter number of edges (e): ");
    scanf("%d", &e);
    if (e > n * (n - 1) / 2) {
        printf("Too many edges! Maximum for simple graph: %d\n", n * (n - 1) / 2);
        return 0;
    }

    // Initialize adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter %d edges (u v) with 0-based indices:\n", e);
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u < 0 || u >= n || v < 0 || v >= n || u == v) {
            printf("Invalid edge (%d %d). Try again.\n", u, v);
            i--;  // retry this edge
            continue;
        }
        graph[u][v] = graph[v][u] = 1;
    }

    if (hamiltonianCycle()) {
        printf("Hamiltonian cycle exists.\n");
        printf("One possible cycle: ");
        for (int i = 0; i < n; i++)
            printf("%d -> ", path[i]);
        printf("%d\n", path[0]);
    } else {
        printf("Hamiltonian cycle does NOT exist.\n");
    }

    printf("\nNote: For n > 15, runtime may be very long.\n");
    return 0;
}

