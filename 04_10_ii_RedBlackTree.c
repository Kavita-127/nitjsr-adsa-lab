/* SET-4
   Q10. Implement the functions createTree(), deleteTree(), insertItem(), deleteItem(), serachItem() for AVL
        trees, i.e. height balanced binary search trees, red-black trees, B Trees and B+ Trees. */
// RED BLACK TREE

#include <stdio.h>
#include <stdlib.h>

// ---------- COLOR DEFINITIONS ----------
typedef enum { RED, BLACK } Color;

// ---------- NODE STRUCTURE ----------
typedef struct Node {
    int key;
    Color color;
    struct Node *left, *right, *parent;
} Node;

// ---------- GLOBAL ROOT ----------
Node *root = NULL;

Node* createNode(int key) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->color = RED;
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// ---------- ROTATIONS ----------
void leftRotate(Node **root, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void rightRotate(Node **root, Node *y) {
    Node *x = y->left;
    y->left = x->right;
    if (x->right)
        x->right->parent = y;

    x->parent = y->parent;
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

// ---------- FIX INSERT ----------
void fixInsert(Node **root, Node *z) {
    while (z->parent && z->parent->color == RED) {
        Node *gp = z->parent->parent;

        if (z->parent == gp->left) {
            Node *uncle = gp->right;

            if (uncle && uncle->color == RED) {
                gp->color = RED;
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z = gp;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK;
                gp->color = RED;
                rightRotate(root, gp);
            }
        } else {
            Node *uncle = gp->left;

            if (uncle && uncle->color == RED) {
                gp->color = RED;
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z = gp;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                gp->color = RED;
                leftRotate(root, gp);
            }
        }
    }
    (*root)->color = BLACK;
}

// ---------- INSERT ITEM ----------
void insertItem(int key) {
    Node *z = createNode(key);
    Node *y = NULL;
    Node *x = root;

    while (x != NULL) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else if (z->key > x->key)
            x = x->right;
        else {
            printf("Duplicate values not allowed!\n");
            free(z);
            return;
        }
    }

    z->parent = y;
    if (y == NULL)
        root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    fixInsert(&root, z);
    printf("%d inserted.\n", key);
}

// ---------- SEARCH ITEM ----------
Node* searchItem(Node *root, int key) {
    while (root != NULL) {
        if (key == root->key) return root;
        root = (key < root->key) ? root->left : root->right;
    }
    return NULL;
}

// ---------- INORDER TRAVERSAL ----------
void inorder(Node *root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d(%s) ", root->key, root->color == RED ? "R" : "B");
    inorder(root->right);
}

// ---------- DELETE TREE ----------
void deleteTree(Node *node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    free(node);
}

// ---------- MAIN MENU ----------
int main() {
    int choice, value;

    while (1) {
        printf("\n==== RED-BLACK TREE MENU ====\n");
        printf("1. Insert item\n");
        printf("2. Search item\n");
        printf("3. Display Inorder\n");
        printf("4. Delete Tree\n");
        printf("5. Exit\n");
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
                insertItem(value);
                break;

            case 2:
                printf("Enter value to search: ");
                scanf("%d", &value);
                if (searchItem(root, value))
                    printf("%d Found in Tree!\n", value);
                else
                    printf("%d NOT found!\n", value);
                break;

            case 3:
                if (root == NULL)
                    printf("Tree is empty!\n");
                else {
                    printf("Inorder Traversal: ");
                    inorder(root);
                    printf("\n");
                }
                break;

            case 4:
                deleteTree(root);
                root = NULL;
                printf("Tree deleted successfully!\n");
                break;

            case 5:
                deleteTree(root);
                printf("Exiting.\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}

