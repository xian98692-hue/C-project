#include <stdio.h>
#include <stdlib.h>
#include"euler-func.h"
long long phi_efficient(long long n) {
	if (n <= 0) return 0;
	long long result = n;
	for (long long p = 2; p * p <= n; p++) {
		if (n % p == 0) {
			result = result / p * (p - 1);
			while (n % p == 0) {
				n /= p;
			}
		}
	}
	if (n > 1) {
		result = result / n * (n - 1);
	}
	return result;
}
struct node* initialize_node(int capa, int val) {
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	if (new_node == NULL) {
		return NULL;
	}
	new_node->top = 0;
	new_node->capacity = capa;
	new_node->value = val;
	new_node->array = (struct node**)calloc(capa, sizeof(struct node*));
	if (new_node->array == NULL) {
		free(new_node);
		return NULL;
	}
	return new_node;
}
void free_graph(struct node* x) {
	if (!x) return;
	for (int i = 0; i < x->top; i++)
		free_graph(x->array[i]);   // 递归释放，子节点各自的 array 也会被释放
	free(x->array);
	free(x);
}

void point_to(struct node* x, struct node* y) {
	if (x->top >= x->capacity) {
		x->capacity *= 2;
		x->array = realloc(x->array, x->capacity * sizeof(struct node*));
		if (!x->array)return;
	}
	x->array[x->top++] = y;
}
void print_graph(struct node* x) {
	int cnt = x->top;
	struct node** arr = x->array;
	printf("the current node's num is %d\ncapacity is %d\nsize is %d\n", x->value, x->capacity, x->top);
	while (cnt > 0) {
		printf("the node points to %d\n", arr[--cnt]->value);
	}
}