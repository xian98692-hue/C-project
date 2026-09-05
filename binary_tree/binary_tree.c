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
	//printf("the current node's num is %d\n", root->num);
	printf_tree(root->left_child);
	printf("the current node's num is %d\n", root->num);
	printf_tree(root->right_child);
	//printf("the current node's num is %d\n", root->num);
}

node* find_max(node* root) {
	if (root == NULL) {
		return NULL;
	};
	while (root->right_child != NULL) {
		root = root->right_child;
	};
	return root;
}
node* find_min(node* root) {
	if (root == NULL) {
		printf("the root is NULL.can not be found min node.\n");
		return NULL;
	};
	while (root->left_child != NULL) {
		root = root->left_child;
	};
	printf("successfully find the min node.the node's num is %d.\n", root->num);
	return root;
}
node* delete_node(int target_num, node* root) {
	if (root == NULL) {
		printf("the input is NULL.");
		return NULL;
	};
	printf("the target num would be deleted is %d.\n",target_num);
	const node* const_root = root;
	node* prev = NULL;
	while (root != NULL) {
		if (target_num < root->num) {
			prev = root;
			root = root->left_child;
		}
		else if (target_num > root->num) {
			prev = root;
			root = root->right_child;
		}
		else if (target_num == root->num) {
			if (root->right_child == NULL && root->left_child == NULL) {
				printf("the deleted node is leave.\n");
				if (prev->left_child == root) {
					printf("prev's left child is the deleted leave.\n");
					prev->left_child = NULL;
				}
				else if (prev->right_child == root) {
					printf("prev's right child is the deleted leave.\n");
					prev->right_child = NULL;
				}
				free(root);

				return const_root;
			}
			else if (root->right_child == NULL && root->left_child != NULL && prev->left_child == root) {
				printf("the deleted node only has one child.\n");
				prev->left_child = root->left_child;
				free(root);
				return const_root;
			}
			else if (root->left_child == NULL && root->right_child != NULL && prev->right_child == root) {
				printf("the deleted node only has one child.\n");
				prev->right_child = root->right_child;
				free(root);
				return const_root;
			}
			else if (root->right_child == NULL && root->left_child != NULL && prev->right_child == root) {
				printf("the deleted node only has one child.\n");
				prev->right_child = root->left_child;
				free(root);
				return const_root;
			}
			else if (root->left_child == NULL && root->right_child != NULL && prev->left_child == root) {
				printf("the deleted node only has one child.\n");
				prev->left_child = root->right_child;
				free(root);
				return const_root;
			}
			else if (root->left_child != NULL && root->right_child != NULL) {
				printf("the deleted node has two childs.\n");

				break;
			};
		};
	};
	printf("the prev node's num is %d\n", prev->num);//10
	printf("the curr node's num is %d\n", root->num);//4
	node* min_node = root->right_child;
	prev = root;
	printf("be copied.now the prev node's num is %d\n", prev->num);//4
	while (min_node->left_child != NULL) {
		prev = min_node;
		min_node = min_node->left_child;
	};
	printf("the prev node is the min node's parent.the prev node's num is %d\n", prev->num);//4
	printf("successfully find the min node.the node's num is %d.\n", min_node->num);//5
	root->num = min_node->num;
	node* right_min_node = min_node->right_child;
	prev->right_child = right_min_node;
	printf("the target node has been deleted.the cuur node's num is %d\n",prev->num);
	free(min_node);

	return const_root;
}

node* recursion_delete_node(int target_num, node* root) {
	if (root == NULL) {
		printf("can not find the target.\n");
		return NULL;
	};
	if (target_num < root->num) {
		printf("the current node's num is greater than target.\n");
	
		root->left_child = recursion_delete_node(target_num, root->left_child);
	}
	else if (target_num > root->num) {
		printf("the current node's num is less than target.\n");
	
		root ->right_child= recursion_delete_node(target_num, root->right_child);
	}
	else if (target_num == root->num) {
		printf("the target num has been found successfully.\n");
		if (root->left_child && root->right_child) {
			printf("the deleted node has two childs.\n");
			node* temp = find_min(root->right_child);
			root->num = temp->num;
			root->right_child = recursion_delete_node(temp->num, root->right_child);//右子树中的最小节点一定是叶子或单孩节点
		}
		else {
			node* temp = NULL;
			if (root->left_child == NULL) {
				temp = root->right_child;
			}
			else {
				temp = root->left_child;
			};
			free(root);
			printf("successfully delete the target num.\n");
			return temp;
		};
	};
}