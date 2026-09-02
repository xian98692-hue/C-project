#include"binary_tree.h"
#include"stdlib.h"
node* create_tree_node(int num) {
	node* new_node = (node*)malloc(sizeof(node));
	if (new_node == NULL) {
		printf("malloc error.");
		return 0;
	};

	new_node->left_child = NULL;
	new_node->right_child = NULL;
	new_node->num = num;
}

node* create_tree(int nums[]) {
	int len = sizeof(nums) / sizeof(nums[0]);
	node* root = NULL;
	for (int i = 0; i < len; i++) {
		int curr_num = nums[i];
		node* new_node = create_tree_node(curr_num);
		
	}

};