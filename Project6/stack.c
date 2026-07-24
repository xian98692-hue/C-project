# include"stack.h"
#include"stdio.h"

stack* create_stack_node(int val) {
	stack* head = (stack*)malloc(sizeof(stack));
	head->val = val;
	head->next = NULL;
	return head;
};
stack* push_stack(stack* head, int val) {
	stack* new_head = (stack*)malloc(sizeof(stack));
	new_head->val = val;
	new_head->next = head;
	return new_head;
};
stack* pop_stack(stack* head) {
	stack* new_head = head->next;
	free(head);
	return new_head;
};

void printf_stack(stack* head) {
	stack* tmp = head;
	while (tmp != NULL) {
		printf("%d->\n", tmp->val);
		tmp = tmp->next;
	};
};