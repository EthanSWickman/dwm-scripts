#ifndef STACK_H
#define STACK_H

struct node;

struct stack { 
  struct node* top;  
};

/* returns null if stack is empty */
void* stack_pick(struct stack);

void stack_push(struct stack, void*);

void stack_delete(struct stack);

#endif