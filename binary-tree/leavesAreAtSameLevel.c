#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Node{
  int data;
  struct Node* left;
  struct Node* right;
};
typedef struct Node node;

node* create(int item);
int depthOfLeftmostLeaf(node* node);
bool areSameLevel(node* node, int depthLeft);


int main(void) {
  node* root = create(1);
  root->left = create(2);

  root->right = create(3);
  root->right->left = create(4);


  if(areSameLevel(root, depthOfLeftmostLeaf(root)))
    printf("same level");
  else
    printf("not");
  return 0;
}

node* create(int item){
  node* newnode = (node*)malloc(sizeof(node));
  newnode->data = item;
  newnode->left = NULL;
  newnode->right = NULL;
  return newnode;
}

int depthOfLeftmostLeaf(node* node){
  int d = -1;
  while(node != NULL){
    d++;
    node = node->left;
  } 
  return d;
}

bool areSameLevel(node* node, int depthLeft){
  if(node == NULL)
    return true;

  // meet a leaf
  if(node->left == NULL && node->right == NULL)
    return depthLeft == 0;

  return areSameLevel(node->left, depthLeft - 1) && areSameLevel(node->right, depthLeft - 1);
}
