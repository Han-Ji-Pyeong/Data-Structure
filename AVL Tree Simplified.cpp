#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
	int val, bf, height; 
	Node *right, *left; 
};

Node *createNode(int val){
	Node *newNode = (Node*)malloc(sizeof(Node)); 
	newNode->val = val; 
	newNode->bf = 0; 
	newNode->height = 1; 
	newNode->right = NULL;
	newNode->left = NULL; 
	return newNode; 
}

void updateNode(Node *root){
	if(root == NULL){ //memorize this, should be easy 
		return; 
	}
	int left = root->left ? root->left->height : 0; // just memorize one of this 
	int right = root->right ? root->right->height : 0; 
	
	root->height = 1 + (left > right ? left : right); //memorize both 27 and 28 
	root->bf = left-right; 
}

Node *leftRotate(Node *oldRoot){ //for right rotate, it's basically the same, just the other way around	
	if(oldRoot == NULL){
		return NULL; 
	}
	
	Node *newRoot= oldRoot->right; 
	Node *temp = newRoot->left; 
	
	newRoot->left = oldRoot; 
	oldRoot->right = temp; 
	
	updateNode(oldRoot); 
	updateNode(newRoot); 
	
	return newRoot; 
} 

Node *rightRotate(Node *oldRoot){
	if(oldRoot == NULL){
		return NULL; 
	}
	Node *newRoot = oldRoot->left; 
	Node *temp = newRoot->right; 
	
	newRoot->right = oldRoot; 
	oldRoot->left = temp; 
	
	updateNode(oldRoot);
	updateNode(newRoot); 
	
	return newRoot; 
}

Node *rotation(Node *root){
	if(root == NULL){
		return NULL; 
	}
	else if(root->bf <= -2){
		if(root->right->bf >= 1){
			root->right = rightRotate(root->right); 
		}
		return leftRotate(root);
	}
	else if(root->bf >= 2){
		if(root->left->bf >= 1){
			root->left = leftRotate(root->left);
		}
		return rightRotate(root); 
	}
	return root;  
}

Node *insert(Node *root, int val){
	if(root == NULL){
		return createNode(val); 
	}
	else if(val > root->val){
		root->right = insert(root->right, val);
	}
	else if(val < root->val){
		root->left = insert(root->left, val); 
	}
	else{
		printf("Duplicate value\n"); 
	}
	updateNode(root); 
	root = rotation(root);
	return root; 
	
}

Node* deleteNode(Node* root, int val) {
	if (root == NULL) {
		printf("Value not found\n");
		return NULL;
	}

	if (val < root->val) {
		root->left = deleteNode(root->left, val);
	} else if (val > root->val) {
		root->right = deleteNode(root->right, val);
	} else {
		if (root->left == NULL && root->right == NULL) {
			free(root);
			return NULL;
		} else if (root->left == NULL) {
			Node* temp = root->right;
			free(root);
			return temp;
		} else if (root->right == NULL) {
			Node* temp = root->left;
			free(root);
			return temp;
		} else {
			Node* successor = root->right;
			while (successor->left != NULL) {
				successor = successor->left;
			}
			root->val = successor->val;
			root->right = deleteNode(root->right, successor->val);
		}
	}

	updateNode(root);
	root = rotation(root);

	return root;
}

void preOrder(Node *root){
	if(root == NULL){
		return; 
	}
	else{
		printf("%d ", root->val);
		preOrder(root->left);
		preOrder(root->right);	
	}
}

void postOrder(Node *root){
	if(root == NULL){
		return; 
	}
	else{
		postOrder(root->left);
		postOrder(root->right); 
		printf("%d ", root->val);
	}
}

void inOrder(Node *root){
	if(root == NULL){
		return; 
	}
	else{
		inOrder(root->left); 
		printf("%d ", root->val); 
		inOrder(root->right);
	}
}

void printMenu(){
	printf("1. Insert Value\n");
	printf("2. Print Orders\n");
	printf("3. Delete\n"); 
	printf("4. Exit\n"); 
	printf(">> "); 
}


int main(){
	
	Node *root = NULL; 
	
	int number = 0, option;
	
	do{
		system("cls"); 
		printMenu(); 
		scanf("%d", &option);
		switch(option){
			case 1:
				printf("Insert the value you want to add: "); scanf("%d", &number); 
				root = insert(root, number); 
				break;	
			case 2:
				printf("inOrder :"); inOrder(root); printf("\n"); 
				printf("postOrder :"); postOrder(root); printf("\n");
				printf("preOrder :"); preOrder(root);  printf("\n");
				getchar(); getchar(); 
				break; 
			case 3:
				printf("Enter the value you want to delete: ");
				scanf("%d", &number);
				root = deleteNode(root, number);
				break;
		}
	}while(option != 4);
	
}
