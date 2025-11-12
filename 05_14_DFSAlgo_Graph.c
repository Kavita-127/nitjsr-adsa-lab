/* SET-5
   Q14. Implement DFS algorithms for graphs. Your function should be able to identify all the tree edges, back
edges, forward edges and cross edges.*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adjList[MAX];    // adjacency list
int visited[MAX], discovery[MAX], finish[MAX];
int timeCounter = 0;

// create a new adjacency list node
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// add edge to adjacency list (directed)
void addEdge(int u, int v) {
    Node* newNode = createNode(v);
    newNode->next = adjList[u];
    adjList[u] = newNode;
}

// DFS with edge classification
void DFS(int u) {
    visited[u] = 1;
    discovery[u] = ++timeCounter;

    for (Node* temp = adjList[u]; temp != NULL; temp = temp->next) {
        int v = temp->vertex;
        if (visited[v] == 0) {
            printf("Tree Edge: %d -> %d\n", u, v);
            DFS(v);
        } else if (visited[v] == 1) {
            printf("Back Edge: %d -> %d\n", u, v);
        } else if (visited[v] == 2) {
            if (discovery[u] < discovery[v])
                printf("Forward Edge: %d -> %d\n", u, v);
            else
                printf("Cross Edge: %d -> %d\n", u, v);
        }
    }

    visited[u] = 2;
    finish[u] = ++timeCounter;
}

int main() {
    int V, E;
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    // initialize adjacency list and visited arrays
    for (int i = 0; i < V; i++) {
        adjList[i] = NULL;
        visited[i] = 0;
    }

    printf("Enter edges (u v) (0-indexed, directed graph):\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    printf("\nDFS Edge Classification:\n");
    for (int i = 0; i < V; i++) {
        if (visited[i] == 0)
            DFS(i);
    }

    return 0;
}

