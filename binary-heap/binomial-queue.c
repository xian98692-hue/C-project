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
	queue* new_queue = create_queue(1, val);
	if (new_queue == NULL) return forest;
	if (forest == NULL) {
		return new_queue;
	}
	queue* result = merge_queue(forest, new_queue);
	free(new_queue->array);
	free(new_queue);
	return result;
}
queue* delete_and_find_min(queue* forest, int* num) {//把被删根的孩子链拆成若干棵二项树，再和原森林合并
	if (forest == NULL || num == NULL) return forest;
	int index = -1;
	for (unsigned int i = 0; i < forest->capacity; ++i) {
		if (forest->array[i] != NULL) {
			index = (int)i;
			break;
		}
	}
	if (index == -1) {
		*num = 0;
		return forest;
	}
	int min = forest->array[index]->value;
	for (unsigned int i = (unsigned int)index + 1; i < forest->capacity; ++i) {
		if (forest->array[i] != NULL && forest->array[i]->value < min) {
			min = forest->array[i]->value;
			index = (int)i;
		}
	}
	*num = min;
	//root是最小值对应的一棵树
	node* root = forest->array[index];
	forest->array[index] = NULL;
	unsigned int child_cap = root->degree;
	queue* child_forest = malloc(sizeof(queue));//新建一个子树集合，对应的森林、二级指针数组都需要分配内存
	if (child_forest == NULL) {
		return forest;
	}
	child_forest->capacity = child_cap;//集合的阶，对应分开的子树最多有多少个
	child_forest->array = child_cap ? calloc(child_cap, sizeof(node*)) : NULL;
	//如果阶是0，说明原本要删除的节点只有一个node结构体，剩余的子树是NULL
	if (child_cap && child_forest->array == NULL) {
		free(child_forest);
		return forest;
	}
	//新建一个child_forest代表这棵树除去根节点外、分散开来的树集合
	node* child = root->next;
	while (child != NULL) {
		node* sibling = child->left_bro;
		child->left_bro = NULL;
		child_forest->array[child->degree] = child;//child是集合里其中的一棵树
		child = sibling;//每棵树原本是通过左兄弟连接的，现在断开
	}
	free(root);//root是最小值的根节点，删除对应内存
	forest = merge_queue(forest, child_forest);//合并操作复制的是指针的值，不是指针指向的内存
	free(child_forest->array);//释放的是指针数组即指针本身的内存，不会释放指针指向的内存
	free(child_forest);//结构体
	return forest;
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
		unsigned int old_cap = x->capacity;
		node** tmp = realloc(x->array, sizeof(node*) * n);
		if (tmp == NULL) return NULL;
		x->array = tmp;
		x->capacity = n;
		for (unsigned int i = old_cap; i < n; ++i) {
			x->array[i] = NULL;
		}
	}
	node* carry = NULL;
	node** a = x->array;
	node** b = y->array;
	for (int i = 0; i < n; i++) {
		node* t1 = a[i];
		node* t2 = (i < y->capacity) ? b[i] : NULL;
		unsigned int cnt = (t1 != NULL) + (t2 != NULL) + (carry != NULL);
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
		node** tmp = realloc(x->array, sizeof(node*) * (n + 1));
		if (tmp == NULL) return NULL;
		x->array = tmp;
		x->array[n] = carry;
		x->capacity = n + 1;
	}
	return x;
}
queue* create_queue(unsigned int capa, int value) {
	if (capa <= 0) capa = 1;
	queue* new_queue = malloc(sizeof(queue));
	if (new_queue == NULL) return NULL;
	new_queue->capacity = capa;
	new_queue->array = calloc(capa, sizeof(node*));
	if (new_queue->array == NULL) {
		free(new_queue);
		return NULL;
	}
	node* n = malloc(sizeof(node));
	if (n == NULL) {
		free(new_queue->array);
		free(new_queue);
		return NULL;
	}
	n->left_bro = NULL;
	n->next = NULL;
	n->degree = 0;
	n->value = value;
	new_queue->array[0] = n;
	return new_queue;
}
void print_queue(queue* forest) {
	for (int i = 0; i < forest->capacity; i++) {
		print_tree(forest->array[i]);
	}
}
void print_tree(node* root) {
	if (root == NULL) {
		return;
	}
	//打印顺序：根->左兄弟->下一个next
	printf("the node's value is %d.\n", root->value);
	print_tree(root->left_bro);
	print_tree(root->next);
}
void clear_queue(queue* x) {//有k个节点，就删除k次节点
	int sum = 0;
	for (int i = 0; i < x->capacity; i++) {
		if (x->array[i]) {
			sum += (1 << (x->array[i]->degree));
		}
	}
	int temp = 0;
	for (int j = 0; j < sum; j++) {
		delete_and_find_min(x, &temp);
	}
}