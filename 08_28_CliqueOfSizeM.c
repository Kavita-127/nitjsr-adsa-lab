/* SET-7
   Q28. Write a program for determining whether a graph with n vertices and e edges contains a clique of size m
(m ≤ n). Check for what values of n, e, and m your program gives output in reasonable time. */ 

#include <stdio.h>
#include <stdbool.h>

#define MAX 20 

int graph[MAX][MAX];
int n, e, m;

// Function to check if a given subset of vertices forms a clique
bool isClique(int vertices[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (graph[vertices[i]][vertices[j]] == 0)
                return false;
        }
    }
    return true;
}

bool findClique(int start, int currLen, int vertices[]) {
    if (currLen == m) {
        return isClique(vertices, m);
    }

    for (int i = start; i < n; i++) {
        vertices[currLen] = i;
        if (findClique(i + 1, currLen + 1, vertices))
            return true;
    }
    return false;
}

int main() {
    printf("Enter number of vertices (n): ");
    scanf("%d", &n);
    if (n > MAX) {
        printf("n too large! Please use n <= %d for reasonable runtime.\n", MAX);
        return 0;
    }

    printf("Enter number of edges (e): ");
    scanf("%d", &e);
    if (e > n * (n - 1) / 2) {
        printf("Too many edges! Maximum possible for simple graph: %d\n", n * (n - 1) / 2);
        return 0;
    }

    printf("Enter clique size to check (m): ");
    scanf("%d", &m);
    if (m > n) {
        printf("Clique size m cannot be greater than n.\n");
        return 0;
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter %d edges (u v) with 0-based vertex indices:\n", e);
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u < 0 || u >= n || v < 0 || v >= n || u == v) {
            printf("Invalid edge (%d %d). Try again.\n", u, v);
            i--;
            continue;
        }
        graph[u][v] = graph[v][u] = 1;
    }

    int vertices[MAX];
    if (findClique(0, 0, vertices)) {
        printf("Graph contains a clique of size %d.\n", m);
        printf("One such clique is: ");
        for (int i = 0; i < m; i++)
            printf("%d ", vertices[i]);
        printf("\n");
    } else {
        printf("Graph does NOT contain a clique of size %d.\n", m);
    }

    printf("\nNote: For n > 15, runtime may become very long due to combinatorial growth.\n");

    return 0;
}

