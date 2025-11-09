#include <stdio.h>
#include <stdlib.h>

// -------- AVL NODE STRUCTURE --------
struct Node {
    int key;
    struct Node *left, *right;
    int height;
};

// -------- UTILITY FUNCTIONS --------
int getHeight(struct Node *n) {
    return (n == NULL) ? 0 : n->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

struct Node* createNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

// -------- ROTATIONS --------
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}

struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}

int getBalance(struct Node* n) {
    return (n == NULL) ? 0 : getHeight(n->left) - getHeight(n->right);
}

// -------- INSERT --------
struct Node* insertItem(struct Node* root, int key) {
    if (root == NULL)
        return createNode(key);

    if (key < root->key)
        root->left = insertItem(root->left, key);
    else if (key > root->key)
        root->right = insertItem(root->right, key);
    else {
        printf("Duplicate value not allowed!\n");
        return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);

    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// -------- SEARCH --------
struct Node* searchItem(struct Node* root, int key) {
    while (root != NULL) {
        if (key == root->key)
            return root;
        else if (key < root->key)
            root = root->left;
        else
            root = root->right;
    }
    return NULL;
}

// -------- GET MIN NODE --------
struct Node* getMinNode(struct Node* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

// -------- DELETE --------
struct Node* deleteItem(struct Node* root, int key) {
    if (searchItem(root, key) == NULL) {
        printf("ERROR: %d not found, nothing deleted.\n", key);
        return root;
    }

    if (key < root->key)
        root->left = deleteItem(root->left, key);
    else if (key > root->key)
        root->right = deleteItem(root->right, key);
    else {
        if (root->left == NULL || root->right == NULL) {
            struct Node* temp = (root->left) ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            struct Node* temp = getMinNode(root->right);
            root->key = temp->key;
            root->right = deleteItem(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// -------- DELETE TREE --------
void deleteTree(struct Node* root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

// -------- INORDER DISPLAY --------
void inorder(struct Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

// -------- MAIN (MENU) --------
int main() {
    struct Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\n==== AVL TREE MENU ====\n");
        printf("1. Insert item\n");
        printf("2. Delete item\n");
        printf("3. Search item\n");
        printf("4. Display Inorder\n");
        printf("5. Delete Tree\n");
        printf("6. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Enter numbers only.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insertItem(root, value);
                break;

            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteItem(root, value);
                break;

            case 3:
                printf("Enter value to search: ");
                scanf("%d", &value);
                if (searchItem(root, value))
                    printf("%d Found in Tree!\n", value);
                else
                    printf("%d NOT found!\n", value);
                break;

            case 4:
                if (root == NULL) {
                    printf("Tree is deleted or empty. Nothing to display!\n");
                } else {
                    printf("Inorder Traversal: ");
                    inorder(root);
                    printf("\n");
                }
                break;

            case 5:
                deleteTree(root);
                root = NULL;
                printf("Tree deleted successfully!\n");
                break;

            case 6:
                deleteTree(root);
                printf("Exiting program!\n");
                return 0;

            default:
                printf("Invalid choice. Try again!\n");
        }
    }
}
