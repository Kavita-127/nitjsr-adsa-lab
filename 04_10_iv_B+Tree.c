/* SET-4
   Q10. Implement the functions createTree(), deleteTree(), insertItem(), deleteItem(), serachItem() for AVL
        trees, i.e. height balanced binary search trees, red-black trees, B Trees and B+ Trees. */

//B+ TREE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ORDER 3  // Maximum keys per node

struct BPTreeNode {
    int keys[ORDER];
    struct BPTreeNode* children[ORDER+1];
    struct BPTreeNode* next;
    bool leaf;
    int n;
};

struct BPTreeNode* createNode(bool leaf) {
    struct BPTreeNode* node = (struct BPTreeNode*)malloc(sizeof(struct BPTreeNode));
    node->leaf = leaf;
    node->n = 0;
    node->next = NULL;
    for (int i = 0; i <= ORDER; i++) node->children[i] = NULL;
    return node;
}

struct BPTreeNode* createTree() {
    return createNode(true);
}

struct BPTreeNode* searchItem(struct BPTreeNode* root, int key, int* pos) {
    if (root == NULL) return NULL;

    int i = 0;
    while (i < root->n && key > root->keys[i]) i++;

    if (root->leaf) {
        if (i < root->n && root->keys[i] == key) {
            if (pos) *pos = i;
            return root;
        }
        return NULL;
    }
    return searchItem(root->children[i], key, pos);
}

void splitLeaf(struct BPTreeNode* parent, int idx, struct BPTreeNode* leaf) {
    int mid = (ORDER+1)/2;
    struct BPTreeNode* newLeaf = createNode(true);

    newLeaf->n = leaf->n - mid;
    for (int i = 0; i < newLeaf->n; i++)
        newLeaf->keys[i] = leaf->keys[mid+i];

    leaf->n = mid;
    newLeaf->next = leaf->next;
    leaf->next = newLeaf;

    for (int i = parent->n; i > idx; i--) {
        parent->keys[i] = parent->keys[i-1];
        parent->children[i+1] = parent->children[i];
    }
    parent->keys[idx] = newLeaf->keys[0];
    parent->children[idx+1] = newLeaf;
    parent->n++;
}

void splitInternal(struct BPTreeNode* parent, int idx, struct BPTreeNode* child) {
    int mid = child->n/2;
    struct BPTreeNode* newChild = createNode(false);

    newChild->n = child->n - mid - 1;
    for (int i = 0; i < newChild->n; i++)
        newChild->keys[i] = child->keys[mid+1+i];
    for (int i = 0; i <= newChild->n; i++)
        newChild->children[i] = child->children[mid+1+i];

    int upKey = child->keys[mid];
    child->n = mid;

    for (int i = parent->n; i > idx; i--) {
        parent->keys[i] = parent->keys[i-1];
        parent->children[i+1] = parent->children[i];
    }
    parent->keys[idx] = upKey;
    parent->children[idx+1] = newChild;
    parent->n++;
}

void insertNonFull(struct BPTreeNode* node, int key) {
    if (node->leaf) {
        int i = node->n - 1;
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i+1] = node->keys[i];
            i--;
        }
        node->keys[i+1] = key;
        node->n++;
    } else {
        int i = node->n - 1;
        while (i >= 0 && key < node->keys[i]) i--;

        i++;
        if (node->children[i]->n == ORDER) {
            if (node->children[i]->leaf)
                splitLeaf(node, i, node->children[i]);
            else
                splitInternal(node, i, node->children[i]);

            if (key > node->keys[i]) i++;
        }
        insertNonFull(node->children[i], key);
    }
}

struct BPTreeNode* insertItem(struct BPTreeNode* root, int key) {
    if (root->n == ORDER) {
        struct BPTreeNode* newRoot = createNode(false);
        newRoot->children[0] = root;

        if (root->leaf)
            splitLeaf(newRoot, 0, root);
        else
            splitInternal(newRoot, 0, root);

        int i = (key > newRoot->keys[0]);
        insertNonFull(newRoot->children[i], key);

        return newRoot;
    } else {
        insertNonFull(root, key);
        return root;
    }
}

void deleteTree(struct BPTreeNode* root) {
    if (root == NULL) return;
    if (!root->leaf) {
        for (int i = 0; i <= root->n; i++)
            deleteTree(root->children[i]);
    }
    free(root);
}

struct BPTreeNode* deleteItem(struct BPTreeNode* root, int key) {
    if (root == NULL) return NULL;
    if (root->leaf) {
        int i = 0;
        while (i < root->n && root->keys[i] != key) i++;
        if (i == root->n) return root;

        for (; i < root->n-1; i++)
            root->keys[i] = root->keys[i+1];
        root->n--;
    } else {
        int i = 0;
        while (i < root->n && key > root->keys[i]) i++;
        root->children[i] = deleteItem(root->children[i], key);
    }
    return root;
}

void traverse(struct BPTreeNode* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }
    while (!root->leaf) root = root->children[0];
    printf("B+ Tree (in leaf order): ");
    while (root) {
        for (int i = 0; i < root->n; i++)
            printf("%d ", root->keys[i]);
        root = root->next;
    }
    printf("\n");
}

int main() {
    struct BPTreeNode* root = createTree();
    int choice, key, pos;
    struct BPTreeNode* result;

    while (1) {
        printf("\n--- B+ Tree Operations ---\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Display\n");
        printf("5. Delete Entire Tree\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter key to insert: ");
            scanf("%d", &key);
            root = insertItem(root, key);
            printf("Key %d inserted.\n", key);
            break;
        case 2:
            printf("Enter key to delete: ");
            scanf("%d", &key);
            root = deleteItem(root, key);
            printf("Key %d deleted (if it existed).\n", key);
            break;
        case 3:
            printf("Enter key to search: ");
            scanf("%d", &key);
            result = searchItem(root, key, &pos);
            if (result)
                printf("Key %d found in leaf at position %d.\n", key, pos);
            else
                printf("Key %d not found.\n", key);
            break;
        case 4:
            traverse(root);
            break;
        case 5:
            deleteTree(root);
            root = createTree();
            printf("Tree deleted and reset.\n");
            break;
        case 6:
            deleteTree(root);
            printf("Exiting program.\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}


