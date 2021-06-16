#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#include<math.h>

/* Phân tích:
 *
 * 3 poles: source (S), auxililary (A), target (T)
 * n : the orginal disks of source pole
 * analyze images with 2 cases: odd, even. I assume that
 * 1: total minimum of moving to finish the game = 2^n - 1
 * 2: even: T => odd: A
 *          A =>      T 
 * Ex: n = odd: step 1. S->T  ==> n: even S->A 
              step 2. S->A              S->T 
              step 3. T->A              A->T
 * 3: n = odd:
 Has 3 cases: for(step = 1 d?n 2^n - 1): 
                + case 1: step % 3 = 1 (S -> T or T -> S)
                + case 2: step % 3 = 2 (S -> A or A -> S)
                + case 3: step % 3 = 0 (A -> T or T -> A)
  -  n = even 
 Has 3 cases: + case 1: step % 3 = 1 (S -> A or A -> S)
                + case 2: step % 3 = 2 (S -> T or T -> S)
                + case 3: step % 3 = 0 (T -> A or A -> T)
  => swap A and T with n = even
 * 4: all of 3 cases above all have in common: 
                + case 1: FROM is empty, move disk from TO -> FROM
                + case 2: TO is empty, move disk from FROM -> TO
                + case 3: peek(FROM) > peek(TO), move disk from TO -> FROM
                + case 4: peek(TO) > peek(FROM), move disk from FROM -> TO
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

  int disks = 10;
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
    char tmp = auxiliary;
    auxiliary = destiny;
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
