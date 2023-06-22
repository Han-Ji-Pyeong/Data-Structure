#include <stdio.h>
#include <stdlib.h>

// Node structure for binary search tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to insert a new node into the BST
struct Node* insert(struct Node* root, int data) {
    struct Node* new_node = newNode(data);
    if (root == NULL) {
        return new_node;
    } else {
        struct Node* curr = root;
        while (1) {
            if (data < curr->data) {
                if (curr->left == NULL) {
                    curr->left = new_node;
                    break;
                } else {
                    curr = curr->left;
                }
            } else {
                if (curr->right == NULL) {
                    curr->right = new_node;
                    break;
                } else {
                    curr = curr->right;
                }
            }
        }
    }
    return root;
}

// Function to search for a node in the BST
struct Node* search(struct Node* root, int data) {
    struct Node* curr = root;
    while (curr != NULL) {
        if (curr->data == data) {
            return curr;
        } else if (data < curr->data) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return NULL;
}

// Function to print the BST inorder
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Main function to test the BST
int main() {
    struct Node* root = NULL;
    root = insert(root, 5);
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 1);
    root = insert(root, 9);
    printf("Inorder traversal of BST: ");
    inorder(root);
    printf("\n");
    struct Node* node = search(root, 7);
    if (node != NULL) {
        printf("Found node with data %d\n", node->data);
    } else {
        printf("Node not found\n");
    }
    return 0;
}
