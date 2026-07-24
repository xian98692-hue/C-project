#include"stack.h"
#include"stdio.h"

int main() {
	stack* head = create_stack_node(111);
	//printf_stack(head);
	head = push_stack(head, 222);
	head = push_stack(head, 222);
	head = push_stack(head, 333);
	head = push_stack(head, 444);
	head = push_stack(head, 555);
	head = push_stack(head, 666);
	head = pop_stack(head);
	printf_stack(head);
	return 666;
};