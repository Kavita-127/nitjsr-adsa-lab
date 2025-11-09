#include <stdio.h>
#include <stdlib.h>

/* Binary Tree Node */
struct Node {
    int data;
    struct Node *left, *right;
};

/* Create new node */
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

/* Insert into BST  */
struct Node* insert(struct Node* root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);

    return root;
}

/* Stack for preorder traversal */
struct Node* stack[100];
int top = -1;

void push(struct Node* node) {
    stack[++top] = node;
}

struct Node* pop() {
    if (top == -1)
        return NULL;
    return stack[top--];
}

int isEmpty() {
    return top == -1;
}

/* Preorder traversal without recursion */
void preorder(struct Node* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    push(root);

    while (!isEmpty()) {
        struct Node* current = pop();
        printf("%d ", current->data);

        /* Push right first and then left next */
        if (current->right)
            push(current->right);
        if (current->left)
            push(current->left);
    }
    printf("\n");
}

int main() {
    struct Node* root = NULL;
    int n, value;

    printf("How many values do you want to insert? ");
    scanf("%d", &n);

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        root = insert(root, value);
    }

    printf("\nPreorder Traversal (without recursion): ");
    preorder(root);

    return 0;
}
