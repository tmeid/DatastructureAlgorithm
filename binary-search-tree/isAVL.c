#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

// Nh?n xét: 
// 1. t?i node dang xét n?u l?y leftmost-subtree - rightmost-subtree: -1/+1: balanced, > 1: l?ch trái (Left left case/ left rigth case), < -1 : l?ch ph?i (right right case/ right left case)
// 2. v?y làm sao bi?t dang thu?c case nào trong 4 case trên?
// - N?u node du?c chèn vào < giá tr? c?a node dang xét->left => trái trái
// - N?u > : trái ph?i
// - tuong t? v?i ph?i ph?i và ph?i trái

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
    
    // insett node 7 s? làm cây không d?t AVL
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
      // neu item = node->data thi k insert
      return node;
    
    // neu insert thanh cong thi tinh balanced factor, neu roi vào 1 in 4 case sau thi không ph?i là AVL:
    int balancedFac = balanceFactor(node);

    // lech trai
    if(balancedFac > 1){
      // trai trai:
      if(item < node->left->data)
        // xoay phai tai node mat can bang va return pivot m?i l?i cho ham da goi truoc do (node->left or node->right)
        return rotateRight(node);
      else if(item > node->left->data){
      // xoay phai tai node->left, sau do xoay phai tai node bi mat can bang, remian pivot moi lai cho ham da goi de quy
        node->left = rotateLeft(node->left);
        return rotateRight(node);
      }
    }
    // lech phai
    else if(balancedFac < -1){
      // phai phai:
      if(item > node->right->data)
        return rotateLeft(node);
      else if(item < node->right->data){
        node->right = rotateRight(node->right);
        return rotateLeft(node);
      }
    }
    //  n?u node dang xét cân b?ng thì không c?n xoay cây, ch? c?n return node l?i cho node->left ho?c node->right c?a l?n g?i d? quy tru?c. l?n tr? d? quy cu?i cùng return l?i cho main.
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
