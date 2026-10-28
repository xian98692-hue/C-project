#include<stdlib.h>
#include<stdio.h>
#include"binary-heap.h"

leh* create_leh_node(int val) {
	leh* new_node = malloc(sizeof(leh));
	if (new_node == NULL) {
		printf("the node malloc fail.\n");
		return NULL;
	}
	new_node->value = val;
	new_node->npl = 0;
	new_node->lchild = new_node->rchild = NULL;
	return new_node;
}
leh* merge(leh* x, leh* y) {
	if (x == NULL) {
		return y;
	}
	else if (y == NULL) {
		return x;
	}
	if (x->value < y->value) {
		return merge1(x, y);
	}
	else if (x->value >= y->value) {
		return merge1(y, x);
	}
}
/*每一次操作都把当前节点的右子树和另一个树合并，同时检查npl值，如果左<右就交换左右子树，然后更新npl值 */
leh* merge1(leh* x, leh* y) {
	if (x->lchild == NULL) {
		x->lchild = y;
		return x;
	}
	x->rchild = merge(x->rchild, y);
	if (x->lchild->npl < x->rchild->npl) {
		swapchild(x);
	}
	x->npl = 1 + x->rchild->npl;
	return x;
}
void swapchild(leh* node) {
	leh* l = node->lchild;
	leh* r = node->rchild;
	node->lchild = r;
	node->rchild = l;
}
leh* insert_leh(leh* root, int val) {
	leh* new_node = create_leh_node(val);
	return merge(root, new_node);
}
leh* delete_leh_top(leh* root) {
	if (root == NULL) {
		return NULL;
	}
	leh* l = root->lchild;
	leh* r = root->rchild;
	free(root);
	return merge(l, r);
}
void print_leh(leh* root) {
	if (root == NULL) {
		printf("the current node is NULL.\n");
		return;
	}
	printf("the node's value is %d.\n", root->value);
	if (root->lchild != NULL)print_leh(root->lchild);
	if (root->rchild != NULL)print_leh(root->rchild);
	return;
}
void free_leh(leh* root) {
	if (root == NULL) {
		return;
	}
	free_leh(root->lchild);
	free_leh(root->rchild);
	free(root);
	return;
}
leh* iteration_merge(leh* x, leh* y) {
	leh* array[100] = { 0 };
	int top = 0;
	if (x == NULL) {
		return y;
	}
	else if (y == NULL) {
		return x;
	}
	if (x->value > y->value) {
		leh* temp = y;
		y = x;
		x = temp;
	}//确保x的值较小
	leh* root = x;
	while (x->rchild&&y) {
		if (x->rchild->value > y->value) {
			leh* tmp = x->rchild;
			x->rchild = y;
			y = tmp;
		}
		array[top++] = x;//有必要在回溯的时候检查根节点的左序性质，所以储存根节点
		x = x->rchild;
	}
	if (y != NULL) {
		x->rchild = y;
		array[top++] = x;
	}
	while (top > 0) {
		leh* curr = array[--top];
		/*
		if (!curr->lchild) {
			leh* temp = curr->lchild;
			curr->lchild = curr->rchild;
			curr->rchild = temp;
		}
		else if (curr->rchild) {
			if (curr->lchild->npl < curr->rchild->npl) {
				leh* tmp = curr->lchild;
				curr->lchild = curr->rchild;
				curr->rchild = tmp;
			}
		}
		*/
		if ((!curr->lchild) || ((curr->rchild) && (curr->lchild->npl < curr->rchild->npl))) {
			leh* tmp = curr->lchild;
			curr->lchild = curr->rchild;
			curr->rchild = tmp;
		}
		curr->npl = curr->rchild?(1+curr->rchild->npl):0;
	}
	return root;;
}