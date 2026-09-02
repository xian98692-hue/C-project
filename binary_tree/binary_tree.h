#ifndef BINARY_TREE
#define BINARY_TREE

typedef struct tree_node {
	struct tree_node* left_child;
	struct tree_node* right_child;
	int num;
}node;

node* create_tree_node(int num);
node* insert(int num, node* root);
node* iteration_insert(int num,node* root );
void printf_tree(node* root);
#endif // !BINARY_TREE
