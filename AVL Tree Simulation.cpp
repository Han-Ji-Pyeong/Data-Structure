#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node* left;
    struct Node* right;
    int bf;
    int height;
};

struct Node* createNewNode(int val) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->bf = 0;
    newNode->height = 1;
    return newNode;
}

void updateNode(struct Node* root) {
    if (root == NULL)
        return;

    int left = root->left ? root->left->height : 0;
    int right = root->right ? root->right->height : 0;

    root->height = 1 + (left > right ? left : right);
    root->bf = left - right;
}

struct Node* leftRotate(struct Node* oldRoot) {
    if (oldRoot == NULL)
        return NULL;

    struct Node* newRoot = oldRoot->right;
    struct Node* temp = newRoot->left;

    newRoot->left = oldRoot;
    oldRoot->right = temp;

    updateNode(oldRoot);
    updateNode(newRoot);

    return newRoot;
}

struct Node* rightRotate(struct Node* oldRoot) {
    if (oldRoot == NULL)
        return NULL;

    struct Node* newRoot = oldRoot->left;
    struct Node* temp = newRoot->right;

    newRoot->right = oldRoot;
    oldRoot->left = temp;

    updateNode(oldRoot);
    updateNode(newRoot);

    return newRoot;
}

struct Node* rotation(struct Node* root) {
    if (root == NULL)
        return NULL;

    if (root->bf <= -2) { // Slanted right
        if (root->right->bf >= 1) // Slanted right-left
            root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    else if (root->bf >= 2) { // Slanted left
        if (root->left->bf <= -1) // Slanted left-right
            root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    return root;
}

struct Node* insert(struct Node* root, int val) {
    if (root == NULL)
        return createNewNode(val);

    if (val > root->val)
        root->right = insert(root->right, val);
    else if (val < root->val)
        root->left = insert(root->left, val);
    else {
        printf("Duplicate value\n");
        return root;
    }

    updateNode(root);
    root = rotation(root);
    return root;
}

struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

struct Node* deleteNode(struct Node* root, int val) {
    if (root == NULL)
        return root;

    if (val < root->val)
        root->left = deleteNode(root->left, val);
    else if (val > root->val)
        root->right = deleteNode(root->right, val);
    else {
        if (root->left == NULL || root->right == NULL) {
            struct Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else {
            struct Node* temp = minValueNode(root->right);
            root->val = temp->val;
            root->right = deleteNode(root->right, temp->val);
        }
    }

    if (root == NULL)
        return root;

    updateNode(root);
    root = rotation(root);
    return root;
}

void printTree(struct Node* root, int tabs) {
    if (root == NULL)
        return;

    printTree(root->right, tabs + 1);

    for (int i = 0; i < tabs; i++)
        printf("\t");

    printf("%d (%d, %d)\n", root->val, root->height, root->bf);

    printTree(root->left, tabs + 1);
}

void print(struct Node* root) {
    printTree(root, 0);
    printf("---------------------------------------\n");
}

int main(void) {
    struct Node* root = NULL;
    int choice, val;

    do {
        printf("1. Add node\n");
        printf("2. Delete node\n");
        printf("3. Show all nodes\n");
        printf("4. Print tree\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to add: ");
                scanf("%d", &val);
                root = insert(root, val);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                root = deleteNode(root, val);
                break;
            case 3:
                printf("All nodes: ");
                print(root);
                break;
            case 4:
                printf("Tree:\n");
                print(root);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    } while (choice != 0);

    return 0;
}
