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
		printf("new node's num is %d.\n", curr->num);
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


node* iteration_insert(int num, node* root) {
	if (root == NULL) {
		node* new_node = create_tree_node(num);
		printf("the root is NULL.the new node's num:%d\n", num);
		return new_node;
	};
	node* temp = root;
	node* prev=NULL;
	while (root != NULL) {
		if (num < root->num) {
			prev = root;
			root = root->left_child;
		}
		else if (num > root->num) {
			prev = root;
			root = root->right_child;
		}
		else if (num == root->num) {
			printf("the num has already exited.");
			return temp;
		};
	};
	printf("have been in target.the new node's num:%d\n",num);
	root = create_tree_node(num);
	if (prev->num < root->num) {
		prev->right_child = root;
	}
	else if (prev->num > root->num) {
		prev->left_child = root;
	};
	return temp;
};

void printf_tree(node* root) {
	if (root == NULL) {
		printf("the node is NULL.\n");
		return;
	};
	//printf("the curr node's num is %d\n", root->num);
	printf_tree(root->left_child);
	//printf("the curr node's num is %d\n", root->num);
	printf_tree(root->right_child);
	printf("the curr node's num is %d\n", root->num);
}