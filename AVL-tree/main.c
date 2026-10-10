#include"AVL-tree.h"
#include<stdio.h>
int main(void) {
	/*
	avl_node* tree = recursion_insert_node(NULL, 9);
	tree = recursion_insert_node(tree, 4);
	tree = recursion_insert_node(tree, 12);
	tree = recursion_insert_node(tree, 5);
	tree = recursion_insert_node(tree, 3);
	tree = recursion_insert_node(tree, 2);
	tree = recursion_insert_node(tree, 1);

	tree = delete_node(tree, 9);
	printf_tree(tree);
	*/
	avl_node* tree = iteration_insert_node(NULL, 9);
	tree = iteration_insert_node(tree, 4);
	tree = iteration_insert_node(tree, 12);
	tree = iteration_insert_node(tree, 5);
	tree = iteration_insert_node(tree, 6);
	tree = iteration_insert_node(tree, 3);
	tree = iteration_insert_node(tree, 8);
	tree = iteration_insert_node(tree, 7);
	tree = iteration_insert_node(tree, 14);
	printf_tree(tree);
	return 0;
};