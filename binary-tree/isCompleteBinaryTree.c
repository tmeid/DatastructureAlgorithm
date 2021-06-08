#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Node{
  int data;
  struct Node* left;
  struct Node* right;
};

typedef struct Node Node;

Node* create(int item);
int totalNodes(Node* node);
bool isCompleteBinaryTree(Node* node, int index, int totalNodes);

int main(void) {
  int nodes;

  Node* root = create(1);
  root->left = create(2);
  root->right = create(3);
  root->left->left = create(4);
  root->left->right = create(5);
  root->right->left = create(6);

  nodes = totalNodes(root);
  if(isCompleteBinaryTree(root, 0, nodes))
    printf("This is a complete binary tree");
  else  
    printf("This is not");

  return 0;


}

Node* create(int item){
  Node* newnode = (Node*)malloc(sizeof(Node));
  newnode->data = item;
  newnode->left = NULL;
  newnode->right = NULL;

  return newnode;
}

int totalNodes(Node* node){
  // base case:
   if(node == NULL)
    return 0;

  // recursive case:
  return 1 + totalNodes(node->left) + totalNodes(node->right);
}

bool isCompleteBinaryTree(Node* node, int index, int totalNodes){
  // base case:
  if(node == NULL)
    return true;
  
  else if(index >= totalNodes)
    return false;

  return isCompleteBinaryTree(node->left, 2*index + 1, totalNodes) && isCompleteBinaryTree(node->right, 2*index + 2, totalNodes);
}
