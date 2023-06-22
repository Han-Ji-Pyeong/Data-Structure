#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node{

    int binusianID;
    char binusianName[26];
    char binusianType[9];
    struct node *left;
    struct node *right;

};

struct node *newNode(int binusianID, char binusianName[], char binusianType[]){

    struct node *currentNewNode = (struct node*) malloc(sizeof(struct node));
    currentNewNode->binusianID = binusianID;
    strcpy(currentNewNode->binusianName, binusianName);
    strcpy(currentNewNode->binusianType, binusianType);
    currentNewNode->left = NULL;
    currentNewNode->right = NULL;

    return currentNewNode;

}

struct node *insert(struct node *root, int binusianID, char binusianName[], char binusianType[]){

    if(root == NULL) return newNode(binusianID, binusianName, binusianType);
    else if(binusianID < root->binusianID) root->left = insert(root->left, binusianID, binusianName, binusianType);
    else if(binusianID > root->binusianID) root->right = insert(root->left, binusianID, binusianName, binusianType);

    return root;
}

void preOrderTraversal(struct node *root){
    if(root == NULL) return;
    printf("=============================================\n");
    printf("| Binusian ID: | Binusian Name: | Position: |\n", root->binusianID, root->binusianName, root->binusianType);
    printf("=============================================\n");
    printf("|          %d |         %s|     %s|\n", root->binusianID, root->binusianName, root->binusianType);
    printf("==================");
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}


struct node *deleteNode(struct node *root, int binusianID){
    if(root == NULL) return root;
    else if(binusianID < root->binusianID) root->left = deleteNode(root->left, binusianID);
    else if(binusianID > root->binusianID) root->right = deleteNode(root->right, binusianID);
    else{
        if(root->left == NULL && root->right == NULL){
            free(root);
            root=NULL;
        }
        else if(root->left == NULL){
            struct node *temp = root;
            root = root->right;
            free(temp);
        }
        else if(root->right == NULL){
            struct node *temp = root;
            root = root->left;
            free(temp);
        }
        else{
            struct node *temp = root->right;
            while(temp->left != NULL) temp = temp->left;
            root->binusianID = temp->binusianID;
            strcpy(root->binusianName, temp->binusianName);
            strcpy(root->binusianType, temp->binusianType);
            root->right = deleteNode(root->right, temp->binusianID);
        }
    }
    return root;
}

int main(void){

printf("====================================================\n");
printf("| School of Computer Science Stakeholders Database |\n");
printf("====================================================\n");

int choice;
struct node *root = NULL;

do{
    printf("1. Insert\n");
    printf("2. Show View <Pre-Order>\n");
    printf("3. Delete\n");
    printf("4. Exit\n");
    printf("Choice: ");
    scanf("%d", &choice);

    switch(choice){
        case 1:{
            int binusianID;
            char binusianName[26];
            char binusianType[9];

            printf("Enter Binusian ID (1-999): ");
            scanf("%d", &binusianID);
            if(binusianID < 1 || binusianID > 999){
                printf("Invalid Binusian ID! Please enter a number between 1 and 999.\n");
                break;
            }

            printf("Enter Binusian Name (5-25 characters): ");
            scanf(" %[^\n]s", binusianName);
            if(strlen(binusianName) < 5 || strlen(binusianName) > 25){
                printf("Invalid Binusian Name! Please enter a name between 5 and 25 characters.\n");
                break;
            }

            printf("Enter Binusian Type (Student or Lecturer): ");
            scanf(" %[^\n]s", binusianType);
            if(strcasecmp(binusianType, "Student") != 0 && strcasecmp(binusianType, "Lecturer") != 0){
                printf("Invalid Binusian Type! Please enter 'Student' or 'Lecturer'.\n");
                break;
            }

            if(root != NULL && (root->binusianID == binusianID)){
                printf("Binusian ID already exists! Please enter a unique ID.\n");
                break;
            }

            root = insert(root, binusianID, binusianName, binusianType);
            printf("Stakeholder data has been successfully inserted!\n");
            break;
        }
        case 2:{
            if(root == NULL){
                printf("No data...\n");
                break;
            }

            printf("=== List of Stakeholders ===\n");
            preOrderTraversal(root);
            printf("===========================\n");
            printf("Close View <Pre-Order>\n");
            printf("Choice: ");
            scanf("%d", &choice);
            break;
        }
        case 3:{
            if(root == NULL){
                printf("No data to delete...\n");
                break;
            }

            int binusianID;
            printf("Enter Binusian ID to delete: ");
            scanf("%d", &binusianID);

            root = deleteNode(root, binusianID);
            printf("Stakeholder data with Binusian ID %d has been successfully deleted!\n", binusianID);
            break;
        }
        case 4:{
            printf("Exiting the program... Goodbye!\n");
            break;
        }
        default:{
            printf("Invalid choice! Please enter a valid choice (1-4).\n");
            break;
        }
    }

} while(choice != 4);

return 0;
}
