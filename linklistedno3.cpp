#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void nodeInsert(struct Node** head, int data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL || data < (*head)->data) {
        newNode->next = *head;
        *head = newNode;
    }
    else {
        struct Node* curr = *head;
        while (curr->next != NULL && curr->next->data <= data) {
            curr = curr->next;
        }
        newNode->next = curr->next;
        curr->next = newNode;
    }
}

void printListAscending(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void printListDescending(struct Node* head) {
    if (head == NULL) {
        return;
    }
    printListDescending(head->next);
    printf("%d ", head->data);
}

int main() {
    struct Node* head = NULL;
    int input;
    printf("Input how many numbers you want to store: ");
    scanf("%d", &input);
    for (int i = 0; i < input; ++i) {
        int sc;
        scanf("%d", &sc);
        nodeInsert(&head, sc);
    }

    printf("Ascending: ");
    printListAscending(head);

    printf("Descending: ");
    printListDescending(head);

    return 0;
}
