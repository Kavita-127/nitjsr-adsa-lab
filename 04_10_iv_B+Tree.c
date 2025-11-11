#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ORDER 3 // Max keys per node

typedef struct BPTreeNode {
    int keys[ORDER];
    struct BPTreeNode* children[ORDER + 1];
    struct BPTreeNode* next; // For leaf nodes
    int numKeys;
    bool isLeaf;
} BPTreeNode;

// Create a new node
BPTreeNode* createNode(bool isLeaf) {
    BPTreeNode* node = (BPTreeNode*)malloc(sizeof(BPTreeNode));
    node->isLeaf = isLeaf;
    node->numKeys = 0;
    node->next = NULL;
    for(int i=0;i<ORDER+1;i++) node->children[i]=NULL;
    return node;
}

// Create tree
BPTreeNode* createTree() {
    return createNode(true);
}

// Find the leaf node where a key should be
BPTreeNode* findLeaf(BPTreeNode* root, int key) {
    BPTreeNode* current = root;
    while(!current->isLeaf) {
        int i;
        for(i = 0; i < current->numKeys; i++) {
            if(key < current->keys[i]) break;
        }
        current = current->children[i];
    }
    return current;
}

// Search key
BPTreeNode* searchItem(BPTreeNode* root, int key) {
    BPTreeNode* leaf = findLeaf(root, key);
    for(int i=0;i<leaf->numKeys;i++) {
        if(leaf->keys[i]==key) return leaf;
    }
    return NULL;
}

// Split child node
void splitChild(BPTreeNode* parent, int index, BPTreeNode* child) {
    int mid = ORDER/2;
    BPTreeNode* newChild = createNode(child->isLeaf);
    newChild->numKeys = child->numKeys - mid;
    
    for(int i=0;i<newChild->numKeys;i++)
        newChild->keys[i] = child->keys[i+mid];
    
    if(!child->isLeaf) {
        for(int i=0;i<=newChild->numKeys;i++)
            newChild->children[i] = child->children[i+mid];
    }

    child->numKeys = mid;
    
    for(int i=parent->numKeys;i>index;i--)
        parent->children[i+1] = parent->children[i];
    parent->children[index+1] = newChild;

    for(int i=parent->numKeys-1;i>=index;i--)
        parent->keys[i+1] = parent->keys[i];
    parent->keys[index] = newChild->keys[0];
    parent->numKeys++;
    
    if(child->isLeaf) {
        newChild->next = child->next;
        child->next = newChild;
    }
}

// Insert in non-full node
void insertNonFull(BPTreeNode* node, int key) {
    if(node->isLeaf) {
        int i = node->numKeys-1;
        while(i>=0 && node->keys[i]>key) {
            node->keys[i+1] = node->keys[i];
            i--;
        }
        node->keys[i+1] = key;
        node->numKeys++;
    } else {
        int i = node->numKeys-1;
        while(i>=0 && node->keys[i]>key) i--;
        i++;
        if(node->children[i]->numKeys == ORDER) {
            splitChild(node, i, node->children[i]);
            if(key > node->keys[i]) i++;
        }
        insertNonFull(node->children[i], key);
    }
}

// Insert key
BPTreeNode* insertItem(BPTreeNode* root, int key) {
    if(root->numKeys == ORDER) {
        BPTreeNode* newRoot = createNode(false);
        newRoot->children[0] = root;
        splitChild(newRoot, 0, root);
        insertNonFull(newRoot, key);
        return newRoot;
    } else {
        insertNonFull(root, key);
        return root;
    }
}

// Print level order
void printLevelOrder(BPTreeNode* root) {
    if(!root) return;
    BPTreeNode* queue[1000];
    int front=0, rear=0;
    queue[rear++] = root;
    int level=1;
    while(front<rear) {
        int nodeCount = rear-front;
        printf("Level %d: ", level++);
        for(int i=0;i<nodeCount;i++) {
            BPTreeNode* node = queue[front++];
            for(int j=0;j<node->numKeys;j++) printf("%d ", node->keys[j]);
            if(!node->isLeaf) {
                for(int j=0;j<=node->numKeys;j++) queue[rear++] = node->children[j];
            }
        }
        printf("\n");
    }
}

// Delete tree
void deleteTree(BPTreeNode* node) {
    if(!node) return;
    if(!node->isLeaf) {
        for(int i=0;i<=node->numKeys;i++)
            deleteTree(node->children[i]);
    }
    free(node);
}

// Delete key (simplified: only works for leaf nodes, full B+ deletion is complex)
void deleteItem(BPTreeNode* root, int key) {
    BPTreeNode* leaf = findLeaf(root, key);
    int i;
    for(i=0;i<leaf->numKeys;i++) {
        if(leaf->keys[i]==key) break;
    }
    if(i==leaf->numKeys) {
        printf("Key %d not found.\n", key);
        return;
    }
    for(;i<leaf->numKeys-1;i++)
        leaf->keys[i] = leaf->keys[i+1];
    leaf->numKeys--;
}

// Main function
int main() {
    BPTreeNode* root = createTree();
    int choice, key;
    while(1) {
        printf("\nB+ Tree Operations:\n");
        printf("1. Insert\n2. Delete\n3. Search\n4. Display Level Order\n5. Delete Tree & Exit\n");
        printf("Enter your choice: ");
        if(scanf("%d",&choice)!=1){ while(getchar()!='\n'); printf("Invalid input!\n"); continue;}
        switch(choice) {
            case 1:
                printf("Enter key to insert: ");
                if(scanf("%d",&key)!=1){ while(getchar()!='\n'); printf("Invalid input!\n"); break;}
                root = insertItem(root,key);
                break;
            case 2:
                printf("Enter key to delete: ");
                if(scanf("%d",&key)!=1){ while(getchar()!='\n'); printf("Invalid input!\n"); break;}
                deleteItem(root,key);
                break;
            case 3:
                printf("Enter key to search: ");
                if(scanf("%d",&key)!=1){ while(getchar()!='\n'); printf("Invalid input!\n"); break;}
                if(searchItem(root,key)) printf("Key %d found.\n",key);
                else printf("Key %d not found.\n",key);
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
