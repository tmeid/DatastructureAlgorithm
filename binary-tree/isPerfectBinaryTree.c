#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node{
  int data;
  struct Node * left;
  struct Node * right;
};

typedef  struct Node Node;

Node * create(int item);
bool isPerfectBinaryTree(Node* node, int depth);
int depthOfLeftmostLeaf(Node * node);

int main(void) {
  int d;

  Node* root = create(1);
  root->left = create(2);
  root->right = create(3);
  root->left->left = create(4);
  root->left->right = create(5);
  root->right->left = create(6);
  // root->right->right = create(7);

  d = depthOfLeftmostLeaf(root);

  if(isPerfectBinaryTree(root, d))
    printf("is a perfect binary tree");
  else
    printf("not a perfect binary tree");

  return 0;
}

Node * create(int item){
  Node* node =(Node*)malloc(sizeof(Node));
  node->left = NULL;
  node->right = NULL;
  node->data = item;

  return node;
}
bool isPerfectBinaryTree(Node* node, int depth){
  // empty tree
  if(node == NULL)
    return true;
  
  // base case: reach the leaf
  else if(node->left == NULL && node->right == NULL)
    return depth == 0;

  // node has 1 node:
  else if(node->left == NULL || node->right == NULL)
    return false;

  return isPerfectBinaryTree(node->left, depth - 1) && isPerfectBinaryTree(node->right, depth -1);

}

int depthOfLeftmostLeaf(Node * node){
  int d = -1;
  while(node != NULL){
    d++;
    node = node->left;
  }
  return d;
}
