#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int V;                     // Number of vertices
int adj[MAX][MAX];          // Adjacency matrix
bool visited[MAX];
int stack[MAX], top = 0;

// DFS utility for topological sort
void topoDFS(int u) {
    visited[u] = true;
    for (int v = 0; v < V; v++) {
        if (adj[u][v] && !visited[v])
            topoDFS(v);
    }
    stack[top++] = u;  // Push vertex to stack after visiting all neighbors
}

// Topological Sort
void topologicalSort() {
    for (int i = 0; i < V; i++)
        visited[i] = false;
    top = 0;

    for (int i = 0; i < V; i++)
        if (!visited[i])
            topoDFS(i);

    printf("\nTopological Sort of the graph:\n");
    for (int i = top - 1; i >= 0; i--)
        printf("%d ", stack[i]);
    printf("\n");
}

int main() {
    int E;  // Number of edges
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    // Initialize adjacency matrix
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            adj[i][j] = 0;

    printf("Enter each edge (source destination):\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;  // directed edge u -> v
    }

    topologicalSort();

    return 0;
}
