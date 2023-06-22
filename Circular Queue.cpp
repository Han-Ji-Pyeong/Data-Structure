#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct CircularQueue {
    Node* front;
    Node* rear;
} CircularQueue;

void initializeQueue(CircularQueue* q) {
    q->front = NULL;
    q->rear = NULL;
}

int isQueueEmpty(CircularQueue* q) {
    return (q->front == NULL);
}

void enqueue(CircularQueue* q, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if (isQueueEmpty(q)) {
        q->front = newNode;
    }
    else {
        q->rear->next = newNode;
    }
    q->rear = newNode;
    q->rear->next = q->front;
}

int dequeue(CircularQueue* q) {
    int data = 0;
    Node* temp;
    if (isQueueEmpty(q)) {
        printf("Queue is empty.\n");
        return 0;
    }
    else if (q->front == q->rear) {
        data = q->front->data;
        free(q->front);
        q->front = NULL;
        q->rear = NULL;
    }
    else {
        temp = q->front;
        data = temp->data;
        q->front = q->front->next;
        q->rear->next = q->front;
        free(temp);
    }
    return data;
}

void display(CircularQueue* q) {
    Node* ptr = q->front;
    printf("\nCircular Queue:\n");
    if (isQueueEmpty(q)) {
        printf("Queue is empty.\n");
    }
    else {
        do {
            printf("%d ", ptr->data);
            ptr = ptr->next;
        } while (ptr != q->front);
    }
}

int main() {
    CircularQueue q;
    initializeQueue(&q);
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    display(&q);
    printf("\nDeleted value: %d", dequeue(&q));
    printf("\nDeleted value: %d", dequeue(&q));
    display(&q);
    enqueue(&q, 50);
    enqueue(&q, 60);
    display(&q);
    printf("\nDeleted value: %d", dequeue(&q));
    printf("\nDeleted value: %d", dequeue(&q));
    printf("\nDeleted value: %d", dequeue(&q));
    printf("\nDeleted value: %d", dequeue(&q));
    printf("\nDeleted value: %d", dequeue(&q));
    display(&q);
    return 0;
}
