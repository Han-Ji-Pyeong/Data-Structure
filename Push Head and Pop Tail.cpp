#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Node {
    char patientName[100];
    int patientAge;
    char inputDescription[100];
    char colorCode[20];

    Node* next;
}*head = NULL, *tail = NULL;

Node* createNode(char patientName[], int patientAge, char inputDescription[], char colorCode[]){
    Node* newNode = (Node*) malloc(sizeof(Node));
    strcpy(newNode->patientName, patientName);
    newNode->patientAge = patientAge;
    strcpy(newNode->inputDescription, inputDescription);
    strcpy(newNode->colorCode, colorCode);

    newNode->next = NULL;
    return newNode;
}

void popHead(){
    if(head == NULL){
        return;
    }else if(head == tail){
        free(head);
        head = NULL;
        tail = NULL;
    }
    else{
    Node* temp = head->next;
    free(head);
    head = temp;
    }
}

void pushTail(char patientName[], int patientAge, char inputDescription[], char colorCode[]){
    Node* newNode = createNode(patientName, patientAge, inputDescription, colorCode);
    if(head == NULL){
        head = newNode;
        tail = newNode;
    }
    else{
        tail->next = newNode;
        tail = newNode;
    }
    return;
}

void printQueue(char patientName[], int patientAge, char inputDescription[], char colorCode[]){
    Node* curr = head;
    while(curr != NULL){
        printf("[ %s | %d | %s | %s ] ->", curr->patientName, curr->patientAge, curr->inputDescription, curr->colorCode);
        curr = curr->next;
    }
    printf("\n");
}

void printCoolQueue(char patientName[], int patientAge, char inputDescription[], char colorCode[]){
    int i= 0;
    Node *curr = head;
    printf("Patient List: \n");
    printf("-----------------------------------------------------------------------------------------------\n");
    printf("| No  | Name               | Age | Description/s                                     | Code   |\n");
    while(curr != NULL){
        printf("| %d | %s               | %d | %s                                        1   | Code   |\n", i+1, curr->patientName, curr->patientAge, curr->inputDescription, curr->colorCode);
        curr = curr->next;
        i++;
    }

     printf("-----------------------------------------------------------------------------------------------\n");
}

void printMenu(){
    printf("BlueJack Hospital\n");
    printf("=================\n");
    printf("1. Insert\n");
    printf("2. View\n");
    printf("3. Next Queue\n");
    printf("4. Exit\n");
    printf("5. Print The List\n");
    printf(">> ");
}

int main(void){
    char patientName[100], inputDescription[100], colorCode[100];
    int input, patientAge;

    do{
        int counter = 0;
        printMenu();
        scanf("%d", &input); getchar();

        if(input == 1){
            do{
                printf("Input Patient Name[4-25]: ");
                scanf("%[^\n]", &patientName); getchar();
            }while(strlen(patientName) < 4 || strlen(patientName) > 25);

            do{
                printf("Input Patient Age[>=0]: ");
                scanf("%d", &patientAge); getchar();
            }while(patientAge < 0);

            do{
                printf("Input Description[>= 6 Characters]: ");
                scanf("%[^\n]", &inputDescription); getchar();
            }while(strlen(inputDescription) < 6);

            do{
                printf("Input Code [Red|Yellow|Green]: ");
                scanf("%[^\n]", &colorCode); getchar();
            }while(strcmp(colorCode, "Red") == 0 && strcmp(colorCode, "Yellow") == 0 && strcmp(colorCode, "Green") == 0);


            pushTail(patientName, patientAge, inputDescription, colorCode);
            printf("\n");
            printf("Insert Success\n\n");
        }

        else if(input == 2){
            Node* curr = head;
            if(head == NULL){
                printf("\nThere is no queue yet !\n");
                printf("Press Enter to continue...\n\n");
            }
            else{
                printCoolQueue(patientName, patientAge, inputDescription, colorCode);
            }

        }
        else if(input == 3){
            Node* curr = head;
                    if(head == NULL){
                        printf("\nThere is no queue yet !\n");
                        printf("Press Enter to continue...\n\n");
                    }
                    else {
                        printf("The next patient is : \n");
                        printf("Name          : %s\n", curr->patientName);
                        printf("Age           : %d\n", curr->patientAge);
                        printf("Description   : %s\n", curr->inputDescription);
                        printf("Code          : %s\n", curr->colorCode);
                        printf("\n Press Enter to continue...\n\n");
                        popHead();
                    }
        }
        else if(input == 4){
            return 0;
        }
        else if(input == 5){
            printQueue(patientName, patientAge, inputDescription, colorCode);
        }
    }while(input >= 1 && input <= 5);
    return 0;
}


