#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


struct Node {
    char name[20];
    char short_name[4];
    int quantity;
    float price;
    float total_cost;
    struct Node *prev;
    struct Node *next;
};


void insert(struct Node **head, char name[], char short_name[], int quantity, float price) {
    struct Node *new_node = (struct Node*) malloc(sizeof(struct Node));
    strcpy(new_node->name, name);
    strcpy(new_node->short_name, short_name);
    new_node->quantity = quantity;
    new_node->price = price;
    new_node->total_cost = (float)quantity * price;
    new_node->next = NULL;


    if (*head == NULL) {
        new_node->prev = NULL;
        *head = new_node;
        return;
    }


    struct Node *curr = *head;
    while (curr->next != NULL) {
        curr = curr->next;
    }


    curr->next = new_node;
    new_node->prev = curr;
}


struct Node* find_node(struct Node *head, const char name[]) {
    struct Node *current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 || strcmp(current->short_name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}


void update(struct Node *head, const char full_name[], int new_quantity) {
    struct Node *node = find_node(head, full_name);
    if (node == NULL) {
        printf("%s not found in list\n", full_name);
        return;
    }


    node->quantity = new_quantity;
    node->total_cost = (float)new_quantity * node->price;
}


void printList(struct Node *head) {
    struct Node *current = head;
    printf("%-10s %-10s %-10s %-15s\n", "Name", "Short Name", "Quantity", "Total Cost");
    printf("-----------------------------------------------------\n");
    while (current != NULL) {
        printf("%-10s %-10s %-10d $%.2f      $%.2f\n", current->name, current->short_name, current->quantity, current->total_cost, current->price);
        current = current->next;
    }
    printf("\n");
}


double getTotalCost(struct Node *head) {
    struct Node *temp = head;
    double total = 0.0;
    while (temp != NULL) {
        total += (temp->quantity * temp->price);
        temp = temp->next;
    }
    return total;
}


void freeList(struct Node *head) {
    struct Node *temp = head;
    while (temp != NULL) {
        struct Node *next = temp->next;
        free(temp);
        temp = next;
    }
}


int countNodes(struct Node *head) {
    int count = 0;
    struct Node *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}


int main() {
    struct Node *head = NULL;
    insert(&head, "Apple", "apl", 0, 0.50);
    insert(&head, "Banana", "bnn", 0, 0.25);
    insert(&head, "Orange", "org", 0, 0.60);
    insert(&head, "Pear", "per", 0, 0.40);
    printList(head);


    printf("\nChoose an option:\n");
    printf("1. Buy\n");
    printf("2. Update item\n");
    printf("3. Checkout\n");


    struct Node *tmp_head = NULL;
    while (true) {
        printf("Enter option number: ");
        int option;
        scanf("%d", &option);
        if (option == 1) {
            char short_name[4];
            int quantity;
            printf("Enter short name and quantity (e.g. apl 3): ");
            scanf("%s %d", short_name, &quantity);
            update(head, short_name, quantity);
            insert(&tmp_head, find_node(head, short_name)->name, short_name, quantity, find_node(head, short_name)->price);
        } else if (option == 2) {
            printf("Enter items you want to update and quantity (e.g. apl 3).\n");
            printf("Enter 'done' when finished.\n");
            char input[20];
            while (true) {
                printf("> ");
                scanf("%s", input);
                if (strcmp(input, "done") == 0) {
                    break;
                }
                int quantity;
                scanf("%d", &quantity);
                update(head, input, quantity);
            }
        } else if (option == 3) {
            printf("\nYour shopping list:\n");
            printList(tmp_head);
            printf("-----------------------------------------------------\n");
            double total_cost = getTotalCost(tmp_head);
            printf("Total cost for %d items: $%.2lf\n", countNodes(tmp_head), total_cost);
            printf("-----------------------------------------------------\n");
            printf("\n");
            printList(head);
            printf("\n");
            printf("Choose an option:\n");
            printf("2. Update item\n");
            printf("3. Checkout\n");
            break;
        }
    }


    freeList(head);
    freeList(tmp_head);
    return 0;
}

