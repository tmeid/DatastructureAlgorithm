#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#include<string.h>

// input: a+b*(c^d-e)^(f+g*h)-i
// ouput: abcd^e-fgh*+^*+i-

#define STACK_EMPTY INT_MIN
#define EMPTY (-1)

struct Stack{
  int top;
  unsigned capacity;
  int* array;
};

struct Stack* createStack(unsigned capacity);
bool isEmpty(struct Stack* stack);
void push(struct Stack* stack, int item);
int pop(struct Stack* stack);
int peek(struct Stack* stack);
void infixToPostfix(char* str);
bool isOperand(char alpha);
int precedence(char chr);


int main(){
  char str[] = "a+b*(c^d-e)^(f+g*h)-i";
  // char str[] = "4*((2+6)/3) - 2^3^4";
  printf("infix: %s\n", str);
  printf("postfix: ");
  infixToPostfix(str); 
  return 0; 
}

struct Stack* createStack(unsigned capacity){
  struct Stack* stack = malloc(sizeof *stack);
  stack->top = EMPTY;
  stack->capacity = capacity;
  stack->array = malloc(capacity * sizeof *stack->array);
  return stack;
}

// return true if the stack is empty, fasle: not empty
bool isEmpty(struct Stack* stack){
  return (stack->top == EMPTY);
}

void push(struct Stack* stack, int item){
  stack->array[++stack->top] = item;
  return;
}

int pop(struct Stack* stack){
  if(isEmpty(stack))
    return STACK_EMPTY;
  
  return stack->array[stack->top--];
  
}
int peek(struct Stack* stack){
  if(isEmpty(stack))
    return STACK_EMPTY;
  return stack->array[stack->top];
}

void infixToPostfix(char* str){
  struct Stack* stack = createStack(strlen(str));

  for(int i = 0; i < strlen(str); i++){
    // print operand
    if(isOperand(str[i])){
      printf("%c ", str[i]);
    }
    // ignore space character
    else if(str[i] == ' ')
      continue;
    // push first operator/ '('
    else if(stack->top == EMPTY){
      push(stack, str[i]);
    }
    else if(str[i] == '(')
      push(stack, str[i]);

    else if(str[i] == ')'){
      while(peek(stack) != '('){
        printf("%c ", pop(stack));
      }
      // delete '(' character in stack
      pop(stack);
    }
    

    // when the stack not empty, we need compare precedece, if top's precedence >= current operator's precedence ==> print top, push current operator only if the current operator's precedence > top's precedence
    else{
      // until stack if empty or the current operator's precedence > the top's precedence, stop while loop
      while(!isEmpty(stack) && precedence(peek(stack)) >= precedence(str[i]))
        printf("%c ", pop(stack));

      //push current operator to the stack:
      // current operator has precedence > top ==> push it to the stack:
      push(stack, str[i]);
    }
  }
  // pop all operator in the stack
  while(!isEmpty(stack))
    printf("%c ", pop(stack));
}


bool isOperand(char chr){
  return (chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z') || (chr >= '0' && chr <= '9');
}
int precedence(char chr){
  if(chr == '^')
    return 3;
  else if(chr == '*' || chr == '/' || chr == '%')
    return 2;
  else if(chr == '+' || chr == '-')
    return 1;
  else 
    // '(' character:
    return -1;
}
 

