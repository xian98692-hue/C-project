#include"binary_tree.h"
#include"stdio.h"
int main(void) {
	int nums[20] = { 2,5,7 };
	/*
	int len = sizeof(nums) / sizeof(nums[0]);
	printf("%d", len);
	*/

	node* root = insert(10, NULL);
	root = insert(4, root);
    root = insert(12, root);
	root = insert(3, root);
	root = insert(5, root);
	root = insert(11, root);
	root = insert(13, root);
	root = insert(1, root);
	root = insert(6, root);
	node* max_node = find_max(root);
	//printf("%d\n", max_node->num);

	root=recursion_delete_node(12, root);
	printf_tree(root);
	return 0;
};