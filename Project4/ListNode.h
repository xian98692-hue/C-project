#include"stdbool.h"
#ifndef LISTNODE_H
#define LISTNODE_H

typedef struct list_node {
	int value;
	bool k;
	struct list_node* next;
}list_node;

list_node* create_node(int val[], int len);
void printf_list(list_node* head);
void free_list(list_node* head);
void insert_node(int val[], int length, list_node** old_node);
void normal_delete(int val, list_node** head);

void lazy_delete_mark(int val, list_node** head);
#endif 
