#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure for edge
typedef struct {
    int u, v, weight;
} Edge;

// Structure for union-find (disjoint set)
typedef struct {
    int parent;
    int rank;
} Subset;

// Function to find set of an element i
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Function to do union of two sets x and y (by rank)
void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Comparison function for qsort
int compareEdges(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

// Kruskal's algorithm
void kruskalMST(int graph[MAX][MAX], int n) {
    Edge edges[MAX * MAX];
    int edgeCount = 0;

    // Collect all edges from adjacency matrix
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) { // avoid duplicates
            if (graph[i][j] != 0) {
                edges[edgeCount].u = i;
                edges[edgeCount].v = j;
                edges[edgeCount].weight = graph[i][j];
                edgeCount++;
            }
        }
    }

    // Sort edges by weight
    qsort(edges, edgeCount, sizeof(Edge), compareEdges);

    Subset subsets[MAX];
    for (int v = 0; v < n; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    printf("\nEdges in MST:\n");
    printf("Edge \tWeight\n");

    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        int setU = find(subsets, u);
        int setV = find(subsets, v);

        if (setU != setV) {
            printf("%d - %d \t%d\n", u, v, edges[i].weight);
            Union(subsets, setU, setV);
        }
    }
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

    kruskalMST(graph, n);
    return 0;
}
