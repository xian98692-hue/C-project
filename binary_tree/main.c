#include"binary_tree.h"
#include"stdio.h"
int main(void) {
	int nums[20] = { 2,5,7 };
	/*
	int len = sizeof(nums) / sizeof(nums[0]);
	printf("%d", len);
	*/

	node* root = insert(6, NULL);
	node* root2 = insert(2, root);
    node* root3 = insert(7, root);
	root = insert(9, root);
	printf("%d\n",root2->num);//6
	printf("%d\n", root3->num);//6，说明返回的是树的根节点
	printf("%d\n", root->right_child->right_child->num);//9
	printf("%d\n", root->left_child->num);//2
	printf("%d\n", root->right_child->num);//7
	//printf_tree(root);
	return 0;
};