#ifndef STACK_H
#define STACK_H

typedef struct stack {
	struct stack* next;
	int val;
}stack;
stack* pop_stack(stack* head);
stack* push_stack(stack* head,int val);
stack* create_stack_node(int val);
void printf_stack(stack* head);
#endif 
