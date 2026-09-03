#include"binary_tree.h"
#include"stdio.h"
int main(void) {
	int nums[20] = { 2,5,7 };
	/*
	int len = sizeof(nums) / sizeof(nums[0]);
	printf("%d", len);
	*/

	node* root = insert(6, NULL);
	root = insert(2, root);
    root = insert(7, root);
	root = insert(9, root);
	root = insert(3, root);
	root = insert(1, root);
	root = insert(5, root);
	root = insert(4, root);
	root = insert(0, root);
	
	printf_tree(root);
	return 0;
};