#include "stack.h"

struct node {
  void* data;
  void* next;
}

void* stack_pop(struct stack* stk) {
  
  return stk->top; 
}