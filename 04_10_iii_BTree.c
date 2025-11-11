#include <stdio.h>
#include <stdlib.h>

// AVL Tree Node
typedef struct AVLNode {
    int key;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

// Function to get the height of the node
int height(AVLNode *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Create a new AVL node
AVLNode* createNode(int key) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1; // New node is initially at leaf
    return node;
}

// Right rotate
AVLNode* rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Left rotate
AVLNode* leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Get balance factor
int getBalance(AVLNode *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Insert a key
AVLNode* insertItem(AVLNode* node, int key) {
    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insertItem(node->left, key);
    else if (key > node->key)
        node->right = insertItem(node->right, key);
    else
        return node; // No duplicates allowed

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Left Left
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Find node with minimum key
AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Delete a key
AVLNode* deleteItem(AVLNode* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteItem(root->left, key);
    else if (key > root->key)
        root->right = deleteItem(root->right, key);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            AVLNode* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            AVLNode* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteItem(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // Left Left
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Search for a key
AVLNode* searchItem(AVLNode* root, int key) {
    if (root == NULL || root->key == key)
        return root;
    if (key < root->key)
        return searchItem(root->left, key);
    return searchItem(root->right, key);
}

// Delete entire tree
void deleteTree(AVLNode* node) {
    if (node == NULL)
        return;
    deleteTree(node->left);
    deleteTree(node->right);
    free(node);
}

// Print level order
void printLevelOrder(AVLNode* root) {
    if (root == NULL) return;

    AVLNode* queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;
    int level = 1;

    while (front < rear) {
        int nodeCount = rear - front;
        printf("Level %d: ", level++);
        for (int i = 0; i < nodeCount; i++) {
            AVLNode* node = queue[front++];
            printf("%d ", node->key);
            if (node->left != NULL)
                queue[rear++] = node->left;
            if (node->right != NULL)
                queue[rear++] = node->right;
        }
        printf("\n");
    }
}

// Create tree
AVLNode* createTree() {
    return NULL;
}

// Main program
int main() {
    AVLNode* root = createTree();
    int choice, key;
    
    printf("\nAVL Tree Operations:\n");
    printf("1. Insert\n2. Delete\n3. Search\n4. Display Level Order\n5. Delete Tree & Exit\n");
    while (1) {
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) { // Input validation
            while (getchar() != '\n');
            printf("Invalid input! Try again.\n");
            continue;
        }
        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                if (scanf("%d", &key) != 1) { while (getchar() != '\n'); printf("Invalid input!\n"); break; }
                root = insertItem(root, key);
                break;
            case 2:
                printf("Enter key to delete: ");
                if (scanf("%d", &key) != 1) { while (getchar() != '\n'); printf("Invalid input!\n"); break; }
                root = deleteItem(root, key);
                break;
            case 3:
                printf("Enter key to search: ");
                if (scanf("%d", &key) != 1) { while (getchar() != '\n'); printf("Invalid input!\n"); break; }
                AVLNode* found = searchItem(root, key);
                if (found) printf("Key %d found.\n", key);
                else printf("Key %d not found.\n", key);
                break;
            case 4:
                printLevelOrder(root);
                break;
            case 5:
                deleteTree(root);
                printf("Tree deleted. Exiting.\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
