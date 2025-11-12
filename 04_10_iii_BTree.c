/*SET-4
 Q10. Implement the functions createTree(), deleteTree(), insertItem(), deleteItem(), serachItem() for AVL
      trees, i.e. height balanced binary search trees, red-black trees, B Trees and B+ Trees. */
// B-TREE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define T 3   // Minimum degree of B-tree

struct BTreeNode {
    int keys[2*T - 1];
    struct BTreeNode* children[2*T];
    int n;
    bool leaf;
};

/* ---------------- CREATE TREE ---------------- */
struct BTreeNode* createTree() {
    struct BTreeNode* node = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    node->leaf = true;
    node->n = 0;
    for (int i = 0; i < 2*T; i++)
        node->children[i] = NULL;
    return node;
}

/* ---------------- DELETE TREE ---------------- */
void deleteTree(struct BTreeNode* root) {
    if (root == NULL) return;
    if (!root->leaf)
        for (int i = 0; i <= root->n; i++)
            deleteTree(root->children[i]);
    free(root);
}

/* ---------------- SEARCH ITEM ---------------- */
struct BTreeNode* searchItem(struct BTreeNode* root, int key) {
    if (root == NULL) return NULL;
    int i = 0;
    while (i < root->n && key > root->keys[i])
        i++;
    if (i < root->n && key == root->keys[i])
        return root;
    if (root->leaf) return NULL;
    return searchItem(root->children[i], key);
}

/* ------------------ HELPERS FOR INSERT ------------------ */
void splitChild(struct BTreeNode* parent, int idx, struct BTreeNode* y) {
    struct BTreeNode* z = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    z->leaf = y->leaf;
    z->n = T - 1;
    for (int j = 0; j < T - 1; j++)
        z->keys[j] = y->keys[j + T];
    if (!y->leaf) {
        for (int j = 0; j < T; j++)
            z->children[j] = y->children[j + T];
    }
    y->n = T - 1;
    for (int j = parent->n; j >= idx + 1; j--)
        parent->children[j + 1] = parent->children[j];
    parent->children[idx + 1] = z;
    for (int j = parent->n - 1; j >= idx; j--)
        parent->keys[j + 1] = parent->keys[j];
    parent->keys[idx] = y->keys[T - 1];
    parent->n++;
}

void insertNonFull(struct BTreeNode* x, int k) {
    int i = x->n - 1;
    if (x->leaf) {
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->n++;
    } else {
        while (i >= 0 && k < x->keys[i]) i--;
        if (x->children[i + 1]->n == 2*T - 1) {
            splitChild(x, i + 1, x->children[i + 1]);
            if (k > x->keys[i + 1]) i++;
        }
        insertNonFull(x->children[i + 1], k);
    }
}

/* ---------------- INSERT ITEM (top-level) ---------------- */
struct BTreeNode* insertItem(struct BTreeNode* root, int k) {
    if (root == NULL) {
        root = createTree();
    }
    if (root->n == 2*T - 1) {
        struct BTreeNode* s = createTree();
        s->leaf = false;
        s->children[0] = root;
        splitChild(s, 0, root);
        int i = 0;
        if (s->keys[0] < k) i++;
        insertNonFull(s->children[i], k);
        return s;
    } else {
        insertNonFull(root, k);
        return root;
    }
}

/* ------------------ HELPERS FOR DELETE ------------------ */
int getPred(struct BTreeNode* node, int idx) {
    struct BTreeNode* cur = node->children[idx];
    while (!cur->leaf)
        cur = cur->children[cur->n];
    return cur->keys[cur->n - 1];
}

int getSucc(struct BTreeNode* node, int idx) {
    struct BTreeNode* cur = node->children[idx + 1];
    while (!cur->leaf)
        cur = cur->children[0];
    return cur->keys[0];
}

void mergeNodes(struct BTreeNode* node, int idx) {
    struct BTreeNode* child = node->children[idx];
    struct BTreeNode* sibling = node->children[idx + 1];

    child->keys[T - 1] = node->keys[idx];
    for (int i = 0; i < sibling->n; i++)
        child->keys[i + T] = sibling->keys[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; i++)
            child->children[i + T] = sibling->children[i];
    }

    for (int i = idx + 1; i < node->n; i++)
        node->keys[i - 1] = node->keys[i];
    for (int i = idx + 2; i <= node->n; i++)
        node->children[i - 1] = node->children[i];

    child->n += sibling->n + 1;
    node->n--;
    free(sibling);
}

void borrowFromPrev(struct BTreeNode* node, int idx) {
    struct BTreeNode* child = node->children[idx];
    struct BTreeNode* sibling = node->children[idx - 1];

    for (int i = child->n - 1; i >= 0; i--)
        child->keys[i + 1] = child->keys[i];
    if (!child->leaf) {
        for (int i = child->n; i >= 0; i--)
            child->children[i + 1] = child->children[i];
    }
    child->keys[0] = node->keys[idx - 1];
    if (!child->leaf)
        child->children[0] = sibling->children[sibling->n];
    node->keys[idx - 1] = sibling->keys[sibling->n - 1];
    child->n += 1;
    sibling->n -= 1;
}

void borrowFromNext(struct BTreeNode* node, int idx) {
    struct BTreeNode* child = node->children[idx];
    struct BTreeNode* sibling = node->children[idx + 1];

    child->keys[child->n] = node->keys[idx];
    if (!child->leaf)
        child->children[child->n + 1] = sibling->children[0];
    node->keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; i++)
        sibling->keys[i - 1] = sibling->keys[i];
    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; i++)
            sibling->children[i - 1] = sibling->children[i];
    }

    child->n += 1;
    sibling->n -= 1;
}

void fill(struct BTreeNode* node, int idx) {
    if (idx != 0 && node->children[idx - 1]->n >= T)
        borrowFromPrev(node, idx);
    else if (idx != node->n && node->children[idx + 1]->n >= T)
        borrowFromNext(node, idx);
    else {
        if (idx != node->n)
            mergeNodes(node, idx);
        else
            mergeNodes(node, idx - 1);
    }
}

void deleteFromNode(struct BTreeNode* node, int k) {
    int idx = 0;
    while (idx < node->n && node->keys[idx] < k)
        idx++;

    if (idx < node->n && node->keys[idx] == k) {
        if (node->leaf) {
            for (int i = idx + 1; i < node->n; i++)
                node->keys[i - 1] = node->keys[i];
            node->n--;
        } else {
            if (node->children[idx]->n >= T) {
                int pred = getPred(node, idx);
                node->keys[idx] = pred;
                deleteFromNode(node->children[idx], pred);
            } else if (node->children[idx + 1]->n >= T) {
                int succ = getSucc(node, idx);
                node->keys[idx] = succ;
                deleteFromNode(node->children[idx + 1], succ);
            } else {
                mergeNodes(node, idx);
                deleteFromNode(node->children[idx], k);
            }
        }
    } else {
        if (node->leaf) return;
        bool flag = (idx == node->n);
        if (node->children[idx]->n < T)
            fill(node, idx);
        if (flag && idx > node->n)
            deleteFromNode(node->children[idx - 1], k);
        else
            deleteFromNode(node->children[idx], k);
    }
}

/* ---------------- DELETE ITEM (top-level) ---------------- */
struct BTreeNode* deleteItem(struct BTreeNode* root, int k) {
    if (root == NULL) return NULL;
    deleteFromNode(root, k);
    if (root->n == 0) {
        struct BTreeNode* tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->children[0];
        free(tmp);
    }
    return root;
}

/* --------------- INORDER DISPLAY (top-level) --------------- */
void inorder(struct BTreeNode* node) {
    if (node == NULL) return;
    int i;
    for (i = 0; i < node->n; i++) {
        if (!node->leaf)
            inorder(node->children[i]);
        printf("%d ", node->keys[i]);
    }
    if (!node->leaf)
        inorder(node->children[i]);
}

/* ---------------- MAIN MENU ---------------- */
int main() {
    struct BTreeNode* root = createTree();
    int choice, key;

    while (1) {
        printf("\n--- B-Tree Menu ---\n");
        printf("1. Insert\n2. Delete\n3. Search\n4. Display (in-order)\n5. Delete Tree\n6. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            // handle non-integer input
            printf("Invalid input. Exiting.\n");
            break;
        }

        if (choice == 6) {
            deleteTree(root);
            printf("Exiting program.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insertItem(root, key);
                printf("Inserted %d.\n", key);
                break;

            case 2:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                root = deleteItem(root, key);
                printf("Deleted %d (if existed).\n", key);
                break;

            case 3:
                printf("Enter key to search: ");
                scanf("%d", &key);
                if (searchItem(root, key))
                    printf("Key %d found.\n", key);
                else
                    printf("Key %d not found.\n", key);
                break;

            case 4:
                printf("B-Tree contents (in-order): ");
                inorder(root);
                printf("\n");
                break;

            case 5:
                deleteTree(root);
                root = createTree();
                printf("Tree cleared.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}
