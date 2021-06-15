#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// https://stackoverflow.com/questions/27688422/c-stack-using-array
// INT_MIN = -2147483648

#define EMPTY (-1)
#define STACK_LEN 5
#define STACK_EMPTY INT_MIN

struct Stack{
  int top;
  unsigned capacity;
  int* array;
};

struct Stack* createStack(unsigned capacity);
bool isFull(struct Stack* stack);
bool isEmpty(struct Stack* stack);
void push(struct Stack* stack, int item);
int pop(struct Stack* stack);
int peek(struct Stack* stack);

int main(void) {
  struct Stack* stack = createStack(STACK_LEN);
  push(stack, 10);
  push(stack, 20);
  push(stack, 30);
  push(stack, 40);
  push(stack, 60);
  push(stack, 70);
 
  printf("%d ", stack->top);
}

struct Stack* createStack(unsigned capacity){
  struct Stack* stack = malloc(sizeof *stack);
  stack->top = EMPTY;
  stack->capacity = capacity;
  stack->array = malloc(capacity * sizeof *stack->array);

  // return structure pointer of type struct Stack
  return stack;
}

// stack is full if top = last index
bool isFull(struct Stack* stack){
  return (stack->top) == (stack->capacity - 1);
}

bool isEmpty(struct Stack* stack){
  return (stack->top) == EMPTY;
}

void push(struct Stack* stack, int item){
  // if stack is full:
  if(isFull(stack))
    return;
  //else:
  //++stack->top: increase index first
  stack->array[++stack->top] = item;
  printf("%d is pushed to the stack\n", item);
  
}
int pop(struct Stack* stack){
  // if empty:
  if(isEmpty(stack))
    return STACK_EMPTY;

  // pop value then decrease index
  return stack->array[stack->top--];
  

}
// function return top value without removing it:
int peek(struct Stack* stack){
  if(isEmpty(stack))
    return STACK_EMPTY;
  return stack->array[stack->top];
}
