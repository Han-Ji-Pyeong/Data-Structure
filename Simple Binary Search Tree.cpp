#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    struct node *left;
    struct node *right;
};

struct node *newNode(int x){
    struct node *currentNewNode = (struct node*) malloc(sizeof(struct node));
    currentNewNode->key = x;
    currentNewNode->left = NULL;
    currentNewNode->right = NULL;

    return currentNewNode;
}

struct node *insert(struct node *root, int x){
    if(root == NULL) return newNode(x);
    else if(x < root->key) root->left = insert(root->left, x);
    else if(x > root->key) root->right = insert(root->right, x);

    return root;
}   

void printAll(struct node *root){
    if(root == NULL) return;
    printAll(root->left);
    printf(" %d", root->key);
    printAll(root->right);
}

struct node *freeAll(struct node *root){
    if(root == NULL) return NULL;
    root->left = freeAll(root->left);
    root->right = freeAll(root->right);
    free(root);
    return NULL;
}

int main(void){
    printf("Binary Search Tree\n");
    struct node *root = NULL;

    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 3);
    root = insert(root, 12);
    root = insert(root, 8);
    root = insert(root, 19);

    printAll(root);
    printAll(root);
    return 0;
}

