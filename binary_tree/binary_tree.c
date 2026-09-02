#include"binary_tree.h"
#include"stdlib.h"
#include"stdio.h"
node* create_tree_node(int num) {
	node* new_node = (node*)malloc(sizeof(node));
	if (new_node == NULL) {
		printf("malloc error.");
		return NULL;
	};

	new_node->left_child = NULL;
	new_node->right_child = NULL;
	new_node->num = num;
}
node* insert(int num, node* root) {
	node* curr = root;
	if (curr == NULL) {
		curr = create_tree_node(num);
		return curr;
	};
	if (num < curr->num) {
		curr->left_child = insert(num, curr->left_child);
	}
	else if (num > curr->num) {
		curr->right_child = insert(num, curr->right_child);
	}
	else if (num == curr->num) {
		return root;
	};
	return root;
}

void printf_tree(node* root) {
	if (root == NULL) {
		return;
	};
	printf("%d\n",root->num);
	

	printf_tree(root->left_child);
	printf_tree(root->right_child);
}

node* iteration_insert(int num, node* root) {

};