/*
队列：
先进先出
在尾部插入，在头部删除
*/
#include"stdlib.h"
#include"stdio.h"

typedef struct queue_node {
	int value;
	struct queue_node* forward;
	struct queue_node* behind;
	int number;
}queue_node;

queue_node* create_node(int value) {
	queue_node* node = (queue_node*)malloc(sizeof(queue_node));
	if (node == NULL) {
		return NULL;
	};
	node->forward = NULL;
	node->behind = NULL;
	node->value = value;
	node->number = 0;
	return node;
};
queue_node* insert(int val, queue_node* node) {
	queue_node* node_behind = create_node(val);
	if (node_behind == NULL) {
		printf("the %p is NULL",node_behind);
		return NULL;
	};
	node->behind = node_behind;
	node_behind->forward = node;
	node_behind->number = (node->number + 1);
	return node_behind;
};
queue_node* delete(queue_node* node) {//接受的是队列的末尾节点，删除的是头节点
	while (node->number != 0) {
		node = node->forward;
	};
	queue_node* tmp =node ;
	node = node->behind;
	free(tmp);
	node->forward = NULL;
	node->number = 0;//固定头节点number是0
	queue_node* dummy = node;
	while (node != NULL) {
		dummy = node;
		node = node->behind;
	};
	node = dummy;
	return node;
};
void print_node(queue_node* _node) {
	if (_node == NULL) {
		printf("the queue's node is NULL.");
	};
	while (_node != NULL) {
		printf("value=%d,number=%d\t", _node->value, _node->number);
		_node = _node->forward;
	};
};
queue_node* while_insert(int value[], int len, queue_node* _node) {
	for (int i = 0; i < len; i++) {
		_node = insert(value[i], _node);
	};
	return _node;
};

queue_node* free_queue(queue_node* _node) {
	queue_node* tmp = _node;
	while (_node != NULL) {
		tmp = _node;
		_node = _node->forward;
		free(tmp);
	};
	return _node;
};
int main() {
	queue_node* queue_node = create_node(111);
	queue_node = insert(222, queue_node);
	printf("\n222->111:\n");
	print_node(queue_node);

	queue_node=insert(333,queue_node);
	printf("\ntail insert 333:\n");
	print_node(queue_node);
	
	printf("\ndelete head:\n");
	queue_node = delete(queue_node);
	print_node(queue_node);
	
	printf("\ntail insert 444,555,666:\n");
	int value[] = { 444,555,666 };
	queue_node = while_insert(value, 3, queue_node);
	print_node(queue_node);
	
	printf("\ndelete head:\n");
	queue_node = delete(queue_node);
	print_node(queue_node);

	printf("\nfree queue:\n");
	queue_node=free_queue(queue_node);
	print_node(queue_node);
	return 0b1111;
};