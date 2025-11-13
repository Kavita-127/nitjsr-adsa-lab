/* SET-6
   Q21. Implement the 15-puzzle problem using the branch and bound method. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define N 4   // 4x4 puzzle

// Structure for a puzzle state
typedef struct Node {
    int puzzle[N][N];
    int x, y;           // blank tile position
    int level;          // depth (number of moves so far)
    int cost;           // heuristic + level
    struct Node* parent;
} Node;

// Goal state
int goal[N][N] = {
    {1,  2,  3,  4},
    {5,  6,  7,  8},
    {9, 10, 11, 0},
    {13,14, 15, 12}
};

// Directions: up, down, left, right
int row[] = { 1, -1, 0, 0 };
int col[] = { 0, 0, -1, 1 };

// Manhattan distance heuristic
int calculateCost(int puzzle[N][N]) {
    int cost = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (puzzle[i][j] != 0) {
                int value = puzzle[i][j];
                int targetX = (value - 1) / N;
                int targetY = (value - 1) % N;
                cost += abs(i - targetX) + abs(j - targetY);
            }
        }
    }
    return cost;
}

// Allocate a new node
Node* newNode(int puzzle[N][N], int x, int y, int newX, int newY, int level, Node* parent) {
    Node* node = (Node*)malloc(sizeof(Node));
    memcpy(node->puzzle, puzzle, sizeof(node->puzzle));

    // swap blank tile
    int temp = node->puzzle[x][y];
    node->puzzle[x][y] = node->puzzle[newX][newY];
    node->puzzle[newX][newY] = temp;

    node->x = newX;
    node->y = newY;
    node->level = level;
    node->parent = parent;
    node->cost = calculateCost(node->puzzle);
    return node;
}

// Print puzzle
void printPuzzle(int puzzle[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (puzzle[i][j] == 0) printf("   ");
            else printf("%2d ", puzzle[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Print path from root to goal
void printPath(Node* root) {
    if (root == NULL) return;
    printPath(root->parent);
    printPuzzle(root->puzzle);
}

// Priority queue (min-heap) for nodes
typedef struct {
    Node* nodes[10000];
    int size;
} MinHeap;

void swap(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

void push(MinHeap* heap, Node* node) {
    heap->nodes[heap->size] = node;
    int i = heap->size;
    heap->size++;

    while (i && (heap->nodes[i]->cost + heap->nodes[i]->level) < 
                (heap->nodes[(i-1)/2]->cost + heap->nodes[(i-1)/2]->level)) {
        swap(&heap->nodes[i], &heap->nodes[(i-1)/2]);
        i = (i-1)/2;
    }
}

Node* pop(MinHeap* heap) {
    if (heap->size <= 0) return NULL;
    Node* root = heap->nodes[0];
    heap->nodes[0] = heap->nodes[--heap->size];

    int i = 0;
    while (1) {
        int smallest = i;
        int left = 2*i + 1;
        int right = 2*i + 2;

        if (left < heap->size && 
            (heap->nodes[left]->cost + heap->nodes[left]->level) < 
            (heap->nodes[smallest]->cost + heap->nodes[smallest]->level))
            smallest = left;

        if (right < heap->size && 
            (heap->nodes[right]->cost + heap->nodes[right]->level) < 
            (heap->nodes[smallest]->cost + heap->nodes[smallest]->level))
            smallest = right;

        if (smallest != i) {
            swap(&heap->nodes[i], &heap->nodes[smallest]);
            i = smallest;
        } else break;
    }
    return root;
}

// Check if solved
int isSolved(int puzzle[N][N]) {
    return memcmp(puzzle, goal, sizeof(goal)) == 0;
}

// Solve puzzle
void solve(int puzzle[N][N], int x, int y) {
    MinHeap heap;
    heap.size = 0;

    Node* root = (Node*)malloc(sizeof(Node));
    memcpy(root->puzzle, puzzle, sizeof(root->puzzle));
    root->x = x;
    root->y = y;
    root->parent = NULL;
    root->level = 0;
    root->cost = calculateCost(puzzle);

    push(&heap, root);

    while (heap.size) {
        Node* min = pop(&heap);

        if (isSolved(min->puzzle)) {
            printf("Solution found in %d moves:\n\n", min->level);
            printPath(min);
            return;
        }

        for (int i = 0; i < 4; i++) {
            int newX = min->x + row[i];
            int newY = min->y + col[i];
            if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
                Node* child = newNode(min->puzzle, min->x, min->y, newX, newY, min->level + 1, min);
                push(&heap, child);
            }
        }
    }
}

int main() {
    int puzzle[N][N] = {
        {1,  2,  3,  4},
        {5,  6,  0,  8},
        {9, 10,  7, 12},
        {13,14, 11, 15}
    };

    // Find blank position
    int x, y;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (puzzle[i][j] == 0) { x = i; y = j; }

    printf("Initial state:\n\n");
    printPuzzle(puzzle);

    printf("Goal state:\n\n");
    printPuzzle(goal);

    solve(puzzle, x, y);

    return 0;
}

