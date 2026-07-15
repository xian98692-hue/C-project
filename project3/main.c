#include "stdint.h"
#include "stdio.h"

typedef struct ListNode {
	int value;
	struct ListNode* next;
}listnode;

//创建节点
listnode* creat_new_node(int val) {
	listnode* new_node = (listnode*)malloc(sizeof(listnode));
	new_node->value = val;
	new_node->next = NULL; // 关键：初始化next为NULL，避免野指针
	return new_node;
}
//little->big
listnode* insert_node(listnode* node,int val) {
	listnode* dummy;
	dummy = creat_new_node(val);
	if (node->value < val) {
		node->next = dummy;
	};
	if (node->value >= val) {
		//val->value
		dummy->next = node;
		node = dummy;
	};
	return node;
}
void free_node(listnode* node) {
	listnode* dummy=NULL;
	while (node != NULL) {
		dummy = node;
		node = node->next;
		free(dummy);
	};
};
void main(void) {
	listnode* node_1 = creat_new_node(666);
	listnode* node_2 = insert_node(node_1, 777);
	listnode* node_3 = insert_node(node_2, 555);
	listnode* node_dummy = NULL;
	node_dummy = node_3;
	for (int i = 0; i < 3;i++) {
		printf("%d->\n", node_dummy->value);
		node_dummy = node_dummy->next;
	}
	free_node(node_3);
	return 999;
}