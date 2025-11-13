#include <stdio.h>
#include <stdbool.h>

#define MAX 20   // maximum number of vertices

int graph[MAX][MAX];   // adjacency matrix
int color[MAX];        // assigned colors
int V;                 // number of vertices
int m;                 // number of colors

// Check if it's safe to color vertex v with color c
bool isSafe(int v, int c) {
    for (int i = 0; i < V; i++) {
        if (graph[v][i] && color[i] == c) {
            return false;
        }
    }
    return true;
}

// Recursive utility function for graph coloring
bool graphColoringUtil(int v) {
    if (v == V)
        return true;  // all vertices colored

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, c)) {
            color[v] = c;

            if (graphColoringUtil(v + 1))
                return true;

            // backtrack
            color[v] = 0;
        }
    }
    return false;
}

// Solve the graph coloring problem
void graphColoring() {
    for (int i = 0; i < V; i++)
        color[i] = 0;

    if (!graphColoringUtil(0)) {
        printf("\nNo solution exists with %d colors.\n", m);
        return;
    }

    printf("\nGraph coloring possible with %d colors:\n", m);
    printf("Vertex : Color\n");
    for (int i = 0; i < V; i++) {
        printf("%6d : %5d\n", i, color[i]);
    }
}

int main() {
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &V);

    printf("Enter the adjacency matrix (%d x %d) row by row:\n", V, V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter the maximum number of colors allowed: ");
    scanf("%d", &m);

    graphColoring();

    return 0;
}
