#include "stdint.h"
#include "stdio.h"
#include "ListNode.h"


list_node* create_node(int val[], int len) {
	list_node* node = (list_node*)malloc(sizeof(list_node));
	list_node* head = node;
	for (int i = 0; i < len; i++) {
		list_node* next_node = (list_node*)malloc(sizeof(list_node));
		if (node == NULL) {
			printf("malloc null.");
			break;
		};
		if (i == len - 1) {
			next_node = NULL;
		};//为了终止打印
		node->value = val[i];
		node->next = next_node;
		node = node->next;
	};
	return head;
};
void printf_list(list_node* head) {
	while (head != NULL) {
		printf("%d->", head->value);
		head = head->next;
	};
};

void free_list(list_node* head) {
	list_node* tmp = NULL;
	while (head != NULL) {
		tmp = head;
		head = head->next;
		free(tmp);//一块内存被free后，不能再被->访问
	};
	if (head == NULL) {
		printf("\nfree successfully.");
	};

};