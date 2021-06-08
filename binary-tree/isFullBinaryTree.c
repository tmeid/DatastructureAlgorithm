#include <stdio.h>
#include<stdlib.h>
#include <stdbool.h>

struct Node{
  int data;
  struct Node* left;
  struct Node* right;
};

typedef struct Node Node;

bool isFullBinaryTree(Node* root);
Node* create(int item);

int main(void) {
  Node* root = create(1);
  root->left = create(2);
  root->right = create(3);
  root->left->left = create(4);
  root->left->right = create(5);

  // root->right->left = create(6);

  if(isFullBinaryTree(root))
    printf("This is a full binary tree");
  else
    printf("This is not");

  return 0;
}

bool isFullBinaryTree(Node* node){
  // base case:
  if(node->left == NULL && node->right == NULL)
    return true;
  
  //recursive case:
  //if node has 2 child:
  if(node->left && node->right)
    return isFullBinaryTree(node->left) && isFullBinaryTree(node->right);

  return false;
}

Node* create(int item){
  Node* newnode = (Node*)malloc(sizeof(Node));
  newnode->data= item;
  newnode->left = newnode->right = NULL;
  return newnode;
}
