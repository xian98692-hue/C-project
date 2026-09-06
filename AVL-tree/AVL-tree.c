#include"AVL-tree.h"
#include<stdlib.h>
avl_node* create_node(int num) {
	avl_node* new_node = (avl_node*)malloc(sizeof(avl_node));
	if (new_node == NULL) {
		printf("malloc is NULL.");
		return NULL;
	};
	new_node->height = 0;
	new_node->left_tree = new_node->right_tree = NULL;
	new_node->num = num;
	return new_node;
}
avl_node* recursion_insert_node(avl_node* node, int num) {
	if (node == NULL) {
		printf("the currnet node is NULL.\n");
		avl_node* new_node = create_node(num);
		return new_node;
	};
	if (num < node->num) {
		printf("the node'num is greater than the inserted num.\n");
		node->left_tree = recursion_insert_node(node->left_tree, num);
	}
	else if (num > node->num) {
		printf("the node'num is less than the inserted num.\n");
		node->right_tree = recursion_insert_node(node->right_tree, num);
	};
}