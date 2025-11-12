/*SET-5
  Q15. Write a function to identify the largest and smallest cycles in a given 
       directed or undirected graph. */

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int n;  // Number of vertices
int graph[MAX][MAX];
int visited[MAX];
int path[MAX];
int pathLen;
int minCycleLen = MAX * MAX;
int maxCycleLen = 0;

// Function to check cycles using DFS
void DFS_cycle(int start, int u) {
    visited[u] = 1;
    path[pathLen++] = u;

    for (int v = 0; v < n; v++) {
        if (graph[u][v]) {  // Edge exists
            if (v == start && pathLen > 1) {  // Cycle found
                if (pathLen < minCycleLen) minCycleLen = pathLen;
                if (pathLen > maxCycleLen) maxCycleLen = pathLen;
            } else if (!visited[v]) {
                DFS_cycle(start, v);
            }
        }
    }

    pathLen--;
    visited[u] = 0; // Backtrack
}

void findCycles() {
    minCycleLen = MAX * MAX;
    maxCycleLen = 0;

    for (int i = 0; i < n; i++) {
        pathLen = 0;
        for (int j = 0; j < n; j++) visited[j] = 0;
        DFS_cycle(i, i);
    }

    if (minCycleLen == MAX * MAX)
        printf("No cycles found in the graph.\n");
    else {
        printf("Smallest cycle length: %d\n", minCycleLen);
        printf("Largest cycle length: %d\n", maxCycleLen);
    }
}

int main() {
    printf("Enter number of vertices (max %d): ", MAX);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    printf("Enter adjacency matrix (0 = no edge, 1 = edge):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &graph[i][j]) != 1 || graph[i][j] < 0) {
                printf("Invalid input.\n");
                return 1;
            }
        }
    }

    findCycles();
    return 0;
}

