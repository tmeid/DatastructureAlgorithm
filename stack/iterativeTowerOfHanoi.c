#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#include<math.h>

/* Ph�n t�ch:
 *
 * C� 3 tr?: source (S), auxililary (A), target (T)
 * n : s? g? ban d?u c?a tr? source
 * Sau khi ph�n t�ch h�nh v? 2 tru?ng h?p n ch?n v� l?, r�t ra v�i quy lu?t:
 * QL1: T?ng s? l?n d?ch chuy?n nh? nh?t c�c kh?i g? d? ho�n th�nh game: 2^n - 1
 * QL2: Khi so s�nh quy lu?t c?a ch?n v� l? c� 1 s? di?u sau: S gi? nguy�n, b�n ch?n l� A th� b�n l? d?i th�nh T v� ngu?c l?i
 * VD: n: l? S->T  ==> n: ch?n S->A 
             S->A              S->T 
             T->A              A->T
 * QL3: �?i v?i n = l? th� ta nh?n th?y:
 C� 3 case: khi ch?y for(step = 1 d?n 2^n - 1): 
                + case 1: step % 3 = 1 (S -> T or T -> S)
                + case 2: step % 3 = 2 (S -> A or A -> S)
                + case 3: step % 3 = 0 (A -> T or T -> A)
  - K?t h?p v?i QL2, khi n ch?n case 1 tr? th�nh: S->A / A->S
                                case 2: S->T / T->S
                                case 3: T->A / A->T
  => ta th?c hi?n quy lu?t 3 theo n l?, c�n n ch?n ta ch? c?n ho�n d?i gi?a A v� T.
 * QL4: 1 trong 3 case tr�n c� 1 di?m chung l� d?u chuy?n g? t? FROM d?n TO, v� l?i t?o ra ti?p nh?ng case sau:
                + case 1: FROM l� empty, th� g? t? TO -> FROM
                + case 2: TO l� empty th� g? t? FROM -> TO
                + case 3: FROM > TO (x�t gi� tr? c?a g? dang ? tr�n c�ng c?a 2 tr?): th� g? t? TO -> FROM
                + case 4: TO > FROM (x�t gi� tr? c?a g? dang ? tr�n c�ng c?a 2 tr?): th� g? t? FROM -> TO
 *
 * PERFECT :D:D 
 *
 */

#define STACK_EMPTY INT_MIN

struct Stack{
  int data;
  struct Stack * next;
};

typedef struct Stack Stack; 
void push(Stack ** root, int item);
int pop(Stack ** root);
int peek(Stack* root);
bool isEmpty(Stack * root);

void msg(int no, int disk, char from, char to);
void move(int no, Stack ** fromPole, Stack ** toPole, char from, char to);
void iterative(int totalDisks, Stack ** src, Stack ** aux, Stack ** target);

int main(void) {
  Stack * source = NULL;
  Stack * auxiliary = NULL;
  Stack * target = NULL;

  int disks = 5;
  for(int i = disks; i >= 1; i--){
    push(&source, i);
  }

  iterative(disks, &source, &auxiliary, &target);
  return 0;
}

void msg(int no, int disk, char from, char to){
  printf("%d. Move disk %d from %c to %c\n", no, disk, from, to);
}
void move(int no, Stack ** fromPole, Stack ** toPole, char from, char to){
  int fromPoleValue = peek(*fromPole);
  int toPoleValue = peek(*toPole);

  if(fromPoleValue == STACK_EMPTY){
    push(fromPole, pop(toPole));
    msg(no, toPoleValue, to, from);
  }
  else if(toPoleValue == STACK_EMPTY){
    push(toPole, pop(fromPole));
    msg(no, fromPoleValue, from, to);
  }
  else if(fromPoleValue > toPoleValue){
    push(fromPole, pop(toPole));
    msg(no, toPoleValue, to, from);
  }
  else if(toPoleValue > fromPoleValue){
    push(toPole, pop(fromPole));
    msg(no, fromPoleValue, from,to);
  }

  return;
}
void iterative(int totalDisks, Stack ** src, Stack ** aux, Stack ** target){
  char source = 'S';
  char auxiliary = 'A';
  char destiny = 'T';

  if(totalDisks % 2 == 0){
    char tmp = source;
    source = destiny;
    destiny = tmp;
  }

  int minSteps = pow(2, totalDisks) - 1;
  for(int step = 1; step <= minSteps; step++){
    if(step % 3 == 1)
      move(step, src, target, source, destiny);
    else if(step % 3 == 2)
      move(step, src, aux, source, auxiliary);
    else if(step % 3 == 0)
      move(step, target, aux, destiny, auxiliary);
  }

  return;
}

void push(Stack ** root, int item){
  Stack * newnode = (Stack*)malloc(sizeof(Stack));
  if(newnode == NULL){
    printf("out of memory");
    return;
  }
  newnode->data = item;
  newnode->next = (*root);
  (*root) = newnode;
    
}
bool isEmpty(Stack * root){
  return root == NULL;
}
int pop(Stack ** root){
  if(isEmpty(*root))
    return STACK_EMPTY;
  
  Stack* node = (*root);
  int item = node->data;
  (*root) = node->next;

  free(node);
  return item;

}
int peek(Stack* root){
  if(isEmpty(root))
    return STACK_EMPTY;
  
  return root->data;
}

