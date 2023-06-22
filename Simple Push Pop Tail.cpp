#include<stdio.h>
#include<stdlib.h>
//link list

struct Node{
 int val;
 Node* next;
}*head = NULL, *tail = NULL;


Node* makeNode(int val){
 Node* newNode = (Node*)malloc(sizeof(Node*));
 newNode->val = val;
 newNode->next = NULL;
 return newNode;
}

void pushHead(int val){
 Node* newNode = makeNode(val);
 if(head==NULL){
  head=newNode;
  tail=newNode;
 }else{
  newNode->next = head;
  head = newNode;
 }
}

void pushTail(int val){
 Node *newNode = makeNode(val);
 if(head == NULL){
  head = newNode;
  tail = newNode;
 }else{
  tail->next = newNode;
  tail = newNode;
 }
}

void print(){
 Node* curr = head;
 while(curr!=NULL){
  printf("%d ->", curr->val);
  curr = curr->next;
 }
 printf("NULL\n");
 if(head!=NULL){
  printf("Head: %d\n", head->val);
 }
 if(tail!=NULL){
  printf("Tail : %d\n", tail->val);
 }
}

int main()
{
 pushHead(5);
 print();
 pushHead(7);
 print();
 
 pushTail(4);
 print();
 pushTail(8);
 print();
 
 return 0;
}