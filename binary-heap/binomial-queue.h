#ifndef BINOMIAL_QUEUE_H
#define BINOMIAL_QUEUE_H
#include<stdbool.h>
typedef struct binomial_queue_node {
	struct binomial_queue_node* left_bro;
	struct binomial_queue_node* next;
	unsigned int degree;
	int value;
}node;

typedef struct forest//数组里，下标i对于第i棵树
{
	node** array;
	unsigned int capacity;
}queue;
node* merge_node(node* x, node* y);
queue* merge_queue(queue* x, queue* y);
queue* insert_queue(queue* forest, int val);
queue* delete_and_find_min(queue* forest, int* num);
unsigned int get_height(node* x);
bool check_same_height(node* x, node* y);
void print_queue(queue* forest);
void print_tree(node* root);
queue* create_queue(unsigned int capa, int val);
void clear_queue(queue* x);
#endif // !BINOMIAL_QUEUE_H