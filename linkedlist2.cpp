#include <stdio.h>
#include <stdlib.h>

// Define the node structure
typedef struct node {
    int data;
    struct node* next;
} Node;

// Define a function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Define a function to insert a node in sorted order
void sortedInsert(Node** headRef, int data) {
    Node newNode = createNode(data);
    Node* curr = headRef;
    Node prev = NULL;

    // Find the right position to insert the new node
    while (curr != NULL && curr->data < data) {
        prev = curr;
        curr = curr->next;
    }

    // Insert the new node at the appropriate position
    if (prev == NULL) {
        newNode->next = *headRef;
        headRef = newNode;
    } else {
        newNode->next = prev->next;
        prev->next = newNode;
    }
}

// Define a function to print the linked list in ascending order
void printAscending(Node head) {
    printf("Linked list in ascending order: ");
    Node* curr = head;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

// Define a function to print the linked list in descending order
void printDescending(Node* head) {
    printf("Linked list in descending order: ");
    Node* curr = head;
    int arr[1000], i = 0;

    // Store the data in an array
    while (curr != NULL) {
        arr[i++] = curr->data;
        curr = curr->next;
    }

    // Print the data in reverse order
    for (int j = i - 1; j >= 0; j--) {
        printf("%d ", arr[j]);
    }
    printf("\n");
}
int main() {
    // Create the head node
    Node* head = NULL;

    // Insert some numbers into the linked list in sorted order
    sortedInsert(&head, 5);
    sortedInsert(&head, 1);
    sortedInsert(&head, 8);
    sortedInsert(&head, 3);
    sortedInsert(&head, 2);
    sortedInsert(&head, 7);

    // Print the linked list in ascending and descending order
    printAscending(head);
    printDescending(head);

    return 0;
}