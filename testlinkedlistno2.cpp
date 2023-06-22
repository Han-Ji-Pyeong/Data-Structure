#include <stdio.h>
#include <stdlib.h>
 
struct node {
    int data;
struct node *next;
};
 
struct node *head = NULL;
struct node *tail=NULL;




void pushFront(int data) {
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = head;
    head = newNode;
}
 
void printList() {
    struct node *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
 
int main() {
    pushFront(12);
    pushFront(9);
    pushFront(7);
    pushFront(6);
    pushFront(5);
    pushFront(1);
 
    printList();
 
    return 0;
}

