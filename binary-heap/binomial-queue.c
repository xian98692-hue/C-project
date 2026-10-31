#include<stdlib.h>
#include<stdio.h>
#include"binomial-queue.h"
unsigned int get_height(node* x) {
	unsigned int sum = 0;
	while (x != NULL)
	{
		x = x->next;
		sum++;
	}
	return sum;
}
bool check_same_height(node* x, node* y) {
	if (get_height(x) == get_height(y)) {
		return 1;
	}
	else {
		return 0;
	}
}
queue* insert_queue(queue* forest, int val) {
	queue* new_queue = create_queue(10, val);
	return merge_queue(forest, new_queue);
}
queue* delete_and_find_min(queue* forest,int* num) {
	if (!forest)return NULL;
	int min=-999 ;
	int index = 0;
	for (int i = 0; i < forest->capacity; i++) {
		if (forest->array[i]&&min==-999) {
			min = forest->array[i]->value;
		}
		if (forest->array[i] && forest->array[i]->value < min) {
			min = forest->array[i]->value;
			index = i;
		}
	}
	*num = min;
	forest->array[index] = NULL;
	return forest;
}
queue* create_queue(unsigned int capa,int value) {
	queue* new_queue = malloc(sizeof(queue));
	if (new_queue == NULL) {
		return NULL;
	}
	new_queue->capacity = capa;
	new_queue->array = calloc(new_queue->capacity, sizeof(node*));
	if (new_queue->array == NULL) {
		free(new_queue);
		return NULL;
	}
	new_queue->array[0]->value = value;
	return new_queue;
}
node* merge_node(node* x, node* y) {
	if (x == NULL) {
		return y;
	}
	else if (y == NULL) {
		return x;
	}
	if (check_same_height(x, y) == 0) {
		printf("the two nodes'height not equal.\n");
		return NULL;
	}
	if (x->value > y->value) {//保证x->value的值小于等于y->value
		node* temp = y;
		y = x;
		x = temp;
	}
	node* tmp = x->next;
	x->next = y;
	y->left_bro = tmp;
	x->degree++;
	return x;
}
queue* merge_queue(queue* x, queue* y) {
	if (!x)return y;
	else if (!y)return x;
	/*
	类似于二进制加法，有进位
	*/
	//merge_node()返回的是以较小值作为根的2个同阶树的合并结果，不含进位
	//需要把上一次的合并结果和进位合并，产生新的结果和进位
	int n = x->capacity > y->capacity ? x->capacity : y->capacity;
	if (x->capacity < n) {
		x->array = realloc(x->array, sizeof(node*) * n);
		if (!x->array)return NULL;
		x->capacity = n;
	}
	node* carry = NULL;
	node** a = x->array;
	node** b = y->array;
	for (int i = 0; i < n; i++) {
		node* t1 =a[i];
		node* t2 = (i < y->capacity) ?b[i] : NULL;
		unsigned int cnt = (t1!=NULL) + (t2!=NULL) + (carry!=NULL);
		switch (cnt) {
		case 0:
			a[i] = NULL;
			break;
		case 1:
			if (t1)a[i] = t1;
			else if (t2)a[i] = t2;
			else if (carry)a[i] = carry;
			carry = NULL;
			break;
		case 2:
			if (t1 && t2) {
				carry = merge_node(t1, t2);
				a[i] = NULL;
			}
			else if (t1 && carry) {
				carry = merge_node(t1, carry);
				a[i] = NULL;
			}
			else if (t2 && carry) {
				carry = merge_node(t2, carry);
				a[i] = NULL;
			}
			break;
		case 3:/* 三棵:留一棵,另两棵合并成进位 */
			a[i] = carry;
			carry = merge_node(t1, t2);
			break;
		}
	}
	if (carry) {
		x->array = realloc(x->array, sizeof(node*) * (n+1));
		x->array[n] = carry;
		carry = NULL;
	}
	return x;
}