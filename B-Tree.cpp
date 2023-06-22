#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_KEYS 3
#define MIN_KEYS (MAX_KEYS / 2)

struct BTreeNode {
    int keys[MAX_KEYS];
    struct BTreeNode* children[MAX_KEYS + 1];
    int numKeys;
    bool isLeaf;
};

struct BTreeNode* createNode(bool isLeaf);
void insertNonFull(struct BTreeNode* node, int key);
void splitChild(struct BTreeNode* parentNode, int childIndex);
void insert(struct BTreeNode** root, int key);
void traverse(struct BTreeNode* node);

struct BTreeNode* createNode(bool isLeaf) {
    struct BTreeNode* newNode = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    newNode->numKeys = 0;
    newNode->isLeaf = isLeaf;
    for (int i = 0; i < MAX_KEYS + 1; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

void insertNonFull(struct BTreeNode* node, int key) {
    int i = node->numKeys - 1;
    if (node->isLeaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->numKeys++;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        if (node->children[i + 1]->numKeys == MAX_KEYS) {
            splitChild(node, i + 1);
            if (key > node->keys[i + 1]) {
                i++;
            }
        }
        insertNonFull(node->children[i + 1], key);
    }
}

void splitChild(struct BTreeNode* parentNode, int childIndex) {
    struct BTreeNode* childNode = parentNode->children[childIndex];
    struct BTreeNode* newNode = createNode(childNode->isLeaf);
    newNode->numKeys = MIN_KEYS;

    for (int i = 0; i < MIN_KEYS; i++) {
        newNode->keys[i] = childNode->keys[i + MIN_KEYS + 1];
    }

    if (!childNode->isLeaf) {
        for (int i = 0; i < MIN_KEYS + 1; i++) {
            newNode->children[i] = childNode->children[i + MIN_KEYS + 1];
        }
    }

    childNode->numKeys = MIN_KEYS;

    for (int i = parentNode->numKeys; i > childIndex; i--) {
        parentNode->children[i + 1] = parentNode->children[i];
    }

    parentNode->children[childIndex + 1] = newNode;

    for (int i = parentNode->numKeys - 1; i >= childIndex; i--) {
        parentNode->keys[i + 1] = parentNode->keys[i];
    }

    parentNode->keys[childIndex] = childNode->keys[MIN_KEYS];
    parentNode->numKeys++;
}

void insert(struct BTreeNode** root, int key) {
    struct BTreeNode* rootNode = *root;
    if (rootNode == NULL) {
        *root = createNode(true);
        (*root)->keys[0] = key;
        (*root)->numKeys = 1;
    } else {
        if (rootNode->numKeys == MAX_KEYS) {
            struct BTreeNode* newRoot = createNode(false);
            newRoot->children[0] = rootNode;
            *root = newRoot;
            splitChild(newRoot, 0);
            insertNonFull(newRoot, key);
        } else {
            insertNonFull(rootNode, key);
        }
    }
}

void traverse(struct BTreeNode* node) {
    int i;
    for (i = 0; i < node->numKeys; i++) {
        if (node->isLeaf == false) {
            traverse(node->children[i]);
        }
        printf("%d ", node->keys[i]);
    }

    if (node->isLeaf == false) {
        traverse(node->children[i]);
    }
}

int main() {
    struct BTreeNode* root = NULL;

    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 5);
    insert(&root, 6);
    insert(&root, 12);
    insert(&root, 30);
    insert(&root, 7);
    insert(&root, 17);

    printf("B-tree traversal: ");
    traverse(root);
    printf("\n");

    return 0;
}
