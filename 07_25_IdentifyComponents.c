#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

int V;  // number of vertices

// Graph representation (for directed and undirected)
int adj[MAX][MAX]; // adjacency matrix for input
int visited[MAX];
int stack[MAX], top;

int transpose[MAX][MAX]; // transpose graph for SCCs

// ---------- STRONGLY CONNECTED COMPONENTS ----------
void dfsSCC(int u) {
    visited[u] = 1;
    for (int v = 0; v < V; v++) {
        if (adj[u][v] && !visited[v])
            dfsSCC(v);
    }
    stack[top++] = u;
}

void dfsTranspose(int u) {
    visited[u] = 1;
    printf("%d ", u);
    for (int v = 0; v < V; v++) {
        if (transpose[u][v] && !visited[v])
            dfsTranspose(v);
    }
}

void stronglyConnectedComponents() {
    for (int i = 0; i < V; i++) visited[i] = 0;
    top = 0;

    // Step 1: fill stack according to finish times
    for (int i = 0; i < V; i++)
        if (!visited[i])
            dfsSCC(i);

    // Step 2: transpose the graph
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            transpose[j][i] = adj[i][j];

    // Step 3: process vertices in order of stack
    for (int i = 0; i < V; i++) visited[i] = 0;

    printf("\nStrongly Connected Components (SCCs):\n");
    for (int i = top - 1; i >= 0; i--) {
        int u = stack[i];
        if (!visited[u]) {
            dfsTranspose(u);
            printf("\n");
        }
    }
}

// ---------- ARTICULATION POINTS, BRIDGES, BICONNECTED COMPONENTS ----------
int disc[MAX], low[MAX], parent[MAX];
bool ap[MAX];

void bccDFS(int u) {
    static int time = 0;
    disc[u] = low[u] = ++time;
    int children = 0;

    for (int v = 0; v < V; v++) {
        if (!adj[u][v]) continue; // no edge

        if (disc[v] == -1) {
            children++;
            parent[v] = u;
            bccDFS(v);

            low[u] = (low[u] < low[v]) ? low[u] : low[v];

            // Articulation point
            if ((parent[u] == -1 && children > 1) ||
                (parent[u] != -1 && low[v] >= disc[u]))
                ap[u] = true;

            // Bridge
            if (low[v] > disc[u])
                printf("Bridge: %d - %d\n", u, v);

        } else if (v != parent[u]) {
            low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
        }
    }
}

void findBCC_AP_Bridges() {
    for (int i = 0; i < V; i++) {
        disc[i] = low[i] = -1;
        parent[i] = -1;
        ap[i] = false;
    }

    for (int i = 0; i < V; i++)
        if (disc[i] == -1)
            bccDFS(i);

    printf("Articulation points: ");
    for (int i = 0; i < V; i++)
        if (ap[i]) printf("%d ", i);
    printf("\n");
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter adjacency matrix (%d x %d):\n", V, V);
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            scanf("%d", &adj[i][j]);

    stronglyConnectedComponents();

    printf("\nArticulation points and bridges (for undirected graph):\n");
    findBCC_AP_Bridges();

    return 0;
}
