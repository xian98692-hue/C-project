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

node* find_max(node* root);
node* find_min(node* root);
node* delete_node(int target_num, node* root);

node* recursion_delete_node(int target_num, node* root);
#endif // !BINARY_TREE
