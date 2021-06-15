#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

// 
// 1. leftmost-subtree - rightmost-subtree: -1/+1: balanced, > 1: left case (Left left case/ left rigth case), < -1 : right case (right right case/ right left case)
// 2. 
// - If node is inserted has value < value of current node->left => left left
// - > : left right
// - similarly with right case

struct Node{
    int data;
    struct Node* left;
    struct Node* right;
};

typedef struct Node str_node;

str_node* create(int item);
str_node* insert(str_node* node, int item);
bool isAVL(str_node* node);
int treeLevel(str_node* node);
int max(int a, int b);
int balanceFactor(str_node* node);
void inOrder(str_node* node);

str_node* rotateLeft(str_node* node);
str_node* rotateRight(str_node* node);

int main(){
    str_node* root = NULL;

    root = insert(root, 13);
    root = insert(root, 10);
    root = insert(root, 15);
    root = insert(root, 16);
    root = insert(root, 11);
    root = insert(root, 5);
    root = insert(root, 4);
    root = insert(root, 6);
    
    // insert node 7 => BST is now unbalanced
    root = insert(root, 7);


    printf("root: %d\n", treeLevel(root));
    inOrder(root);
    printf("\nleft child of root: %d", root->left->data);


    return 0;
}

str_node* create(int item){
    str_node* newnode = (str_node*)malloc(sizeof(str_node));
    newnode->data = item;
    newnode->left = NULL;
    newnode->right = NULL;

    return newnode;
}

str_node* insert(str_node* node, int item){
    if(node == NULL)
        return create(item);

    if(item < node->data)
        node->left = insert(node->left, item);
    else if(item > node->data)
        node->right = insert(node->right, item);
    else
      // if item = node->data => not insert
      return node;
    
    // if insert successfully => calc balanced factor:
    int balancedFac = balanceFactor(node);

    // left case
    if(balancedFac > 1){
      // left left:
      if(item < node->left->data)
        // right rotate at the unbalanced node, then return new pivot to the function call(node->left or node->right recursive function above)
        return rotateRight(node);
      else if(item > node->left->data){
      // left rotate, then right rotate at the unbalances node, next return the new pivot to the recursive function (node->left or node->right above)
        node->left = rotateLeft(node->left);
        return rotateRight(node);
      }
    }
    // right case
    else if(balancedFac < -1){
      // right right
      if(item > node->right->data)
        return rotateLeft(node);
      else if(item < node->right->data){
        node->right = rotateRight(node->right);
        return rotateLeft(node);
      }
    }
    //  if BST is AVL, no need to rotate, return node to the recursive function. in the end, return root to main
    return node;
}
int treeLevel(str_node* node){
    // base case:
    if(node == NULL)
        return -1;
    else if(node->left == NULL && node->right == NULL)
      return 0;
    return 1 + max(treeLevel(node->left), treeLevel(node->right));
}
bool isAVL(str_node* node){
    if(node == NULL)    
        return true;
    if(abs(treeLevel(node->left) - treeLevel(node->right)) > 1)
        return false;
    return isAVL(node->left) && isAVL(node->right);
    
}
int max(int a, int b){
  return a > b ? a : b;
}

int balanceFactor(str_node* node){
  return treeLevel(node->left) - treeLevel(node->right);
}

void inOrder(struct Node *root){
  if(root == NULL)
    return;

  inOrder(root->left);
  printf("%d ", root->data);
  inOrder(root->right);
}

str_node* rotateLeft(str_node* node){
  // store new root
  str_node* pivot = node->right;
  // store left subtree of new root (if exist)
  str_node* moveRight = pivot->left;
  
  //root becomes left subtree of new root:
  pivot->left = node;
  node->right = moveRight;
  
    

  return pivot;  
}

str_node* rotateRight(str_node* node){
  // store new root
  str_node* pivot = node->left;
  // store left subtree of new root (if exist)
  str_node* moveLeft = pivot->right;
  
  //root becomes left subtree of new root:
  pivot->right = node;

  
  node->left = moveLeft;
  
    

  return pivot; 
}
