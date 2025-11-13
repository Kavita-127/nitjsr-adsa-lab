#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 100

int graph[MAX][MAX];
int color[MAX];
int n, e;

// BFS-based function to check if the graph is bipartite
bool isBipartite() {
    for (int i = 0; i < n; i++)
        color[i] = -1;  // -1 means uncolored

    for (int start = 0; start < n; start++) {
        if (color[start] == -1) {
            color[start] = 0;
            int queue[MAX], front = 0, rear = 0;
            queue[rear++] = start;

            while (front < rear) {
                int u = queue[front++];
                for (int v = 0; v < n; v++) {
                    if (graph[u][v]) {
                        if (color[v] == -1) {
                            color[v] = 1 - color[u];
                            queue[rear++] = v;
                        } else if (color[v] == color[u]) {
                            return false; // same color on adjacent vertices
                        }
                    }
                }
            }
        }
    }
    return true;
}

int main() {
    printf("Enter number of vertices (n): ");
    scanf("%d", &n);
    if (n > MAX) {
        printf("n too large! Max allowed: %d\n", MAX);
        return 0;
    }

    printf("Enter number of edges (e): ");
    scanf("%d", &e);

    // Initialize adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter %d edges (u v) with 0-based vertex indices:\n", e);
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u < 0 || u >= n || v < 0 || v >= n) {
            printf("Invalid edge (%d %d). Try again.\n", u, v);
            i--;
            continue;
        }
        graph[u][v] = graph[v][u] = 1; // undirected graph
    }

    if (isBipartite()) {
        printf("Graph is bipartite.\n");
        printf("One possible coloring:\n");
        for (int i = 0; i < n; i++)
            printf("Vertex %d ---> Color %d\n", i, color[i]);
    } else {
        printf("Graph is NOT bipartite.\n");
    }

    return 0;
}
