#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct avl_tree {
	struct avl_tree* left_tree;
	struct avl_tree* right_tree;
	int num;
	int height;
}avl_node;

avl_node* recursion_insert_node(avl_node* node, int num);
avl_node* search_node(avl_node* node, int target);
avl_node* update_height(avl_node* node);
avl_node* left_rotation(avl_node* node);
avl_node* right_rotation(avl_node* node);

#endif