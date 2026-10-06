#include"AVL-tree.h"
#include<stdlib.h>
#include<stdio.h>
avl_node* create_node(int num) {
	avl_node* new_node = (avl_node*)malloc(sizeof(avl_node));
	if (new_node == NULL) {
		printf("malloc is NULL.");
		return NULL;
	};
	new_node->height = 1;//叶子高度为1，空树高度为0
	new_node->left_tree = new_node->right_tree = NULL;
	new_node->num = num;
	return new_node;
}
avl_node* search_node(avl_node* node, int target) {
	while (node != NULL) {
		if (node->num > target) {
			node = node->left_tree;
		}
		else if (node->num < target) {
			node = node->right_tree;
		}
		else if (node->num == target) {
			printf("search the target successfully.");
			return node;
		};
	};
	if (node == NULL) {
		return NULL;
	};
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
	}
	else {
		return node;//重复值不插入
	};
	Updateheight(node);

	int balance = get_balance(node);//left-right
	//get_balance()返回的值大于0是左重，小于0是右重
	if (balance == 2 && get_balance(node->left_tree) >= 0) {//LL
		return right_rotation(node);
	}
	else if (balance == -2 && get_balance(node->right_tree) < 0) {//RR
		return left_rotation(node);
	}
	else if (balance == 2 && get_balance(node->left_tree) < 0) {//LR
		avl_node* left_node = left_rotation(node->left_tree);
		node->left_tree = left_node;
		return right_rotation(node);
	}
	else if (balance == -2 && get_balance(node->right_tree) >= 0) {//RL
		avl_node* right_node = right_rotation(node->right_tree);
		node->right_tree = right_node;
		return left_rotation(node);
	};

	return node;
}
void printf_tree(avl_node* root) {
	if (root == NULL) {
		printf("the current node is NULL.\n");
		return;
	};
	printf("the current node's num is %d.\n", root->num);
	printf_tree(root->left_tree);
	//printf("the current node's num is %d.\n",root->num);
	printf_tree(root->right_tree);
}
avl_node* left_rotation(avl_node* node) {
	avl_node* right_node = node->right_tree;
	avl_node* right_left_node = right_node->left_tree;

	right_node->left_tree = node;
	node->right_tree = right_left_node;
	//左旋：应对RR，左子树挂到右子树上。
	Updateheight(node);
	Updateheight(right_node);

	return right_node;//返回新的子树根
}

avl_node* right_rotation(avl_node* node) {
	avl_node* left_node = node->left_tree;
	avl_node* left_right_node = left_node->right_tree;

	left_node->right_tree = node;
	node->left_tree = left_right_node;

	Updateheight(node);
	Updateheight(left_node);

	return left_node;
}

avl_node* Updateheight(avl_node* node) {
	if (node == NULL) {
		return NULL;
	};
	node->height = max_height(return_height(node->left_tree), return_height(node->right_tree)) + 1;//子树的高度再加一
	return node;
}

int max_height(int a, int b) {
	return (a >= b) ? a : b;
}

int return_height(avl_node* node) {
	return node == NULL ? 0 : node->height;
}

int get_balance(avl_node* node) {
	if (node == NULL) {
		return 0;
	};
	if (node->left_tree == NULL && node->right_tree) {
		return -return_height(node->right_tree);
	}
	else if (node->right_tree == NULL && node->left_tree) {
		return return_height(node->left_tree);
	}
	else if (node->left_tree == NULL && node->right_tree == NULL) {
		return 0;
	}
	return return_height(node->left_tree) - return_height(node->right_tree);
}

avl_node* delete_node(avl_node* node, int target_num) {
	if (!node) {
		printf("the current node is NULL.\n");
		return NULL;
	};
	if (target_num < node->num) {
		node->left_tree = delete_node(node->left_tree, target_num);
	}
	else if (target_num > node->num) {
		node->right_tree = delete_node(node->right_tree, target_num);
	}
	else if (target_num == node->num) {
		if (node->left_tree && node->right_tree) {
			avl_node* min_node = find_min(node->right_tree);
			node->num = min_node->num;
			printf("find the target.%d\n", target_num);
			node->right_tree = delete_node(node->right_tree, min_node->num);
		}
		else {
			//0个或1个子节点
			avl_node* temp = node->left_tree ? node->left_tree : node->right_tree;
			free(node);
			return temp;
		}
	};

	Updateheight(node);
	int balance = get_balance(node);

	if (balance > 1 && get_balance(node->left_tree) > 0) {//LL
		return right_rotation(node);
	}
	else if (balance > 1 && get_balance(node->left_tree) < 0) {//LR
		node->left_tree = left_rotation(node->left_tree);
		return right_rotation(node);
	}
	else if (balance < -1 && get_balance(node->right_tree) < 0) {//RR
		return left_rotation(node);
	}
	else if (balance < -1 && get_balance(node->right_tree)>0) {//RL
		node->right_tree = right_rotation(node->right_tree);
		return left_rotation(node);
	};

	return node;
}

avl_node* find_min(avl_node* node) {
	if (node == NULL) {
		printf("the input node is NULL.\n");
		return NULL;
	};
	avl_node* parent = NULL;
	while (node) {
		parent = node;
		node = node->left_tree;
	};
	return parent;
}

/*
插入后必须能从插入点一路回溯到根。但avl_node 没有 parent 指针，
所以需要在向下查找插入位置时，用一个栈把路径上的节点保存下来。
插入完成后，从栈顶，也就是插入节点的父节点开始，向上逐个更新高度、计算平衡因子、做旋转，
并把旋转后的新子树根接回它的父节点或更新整棵树的根
*/
avl_node* iteration_insert_node(avl_node* node, int num) {
	if (node == NULL) {
		avl_node* new_node = create_node(num);
		return new_node;
	}
	avl_node* head = node;
	avl_node* prev = node;
	avl_node* stack[100] = { 0 };
	int top = -1;

	while (node != NULL) {
		if (num < node->num) {
			prev = node;
			stack[++top] = prev;
			node = node->left_tree;
		}
		else if (num > node->num) {
			prev = node;
			stack[++top] = prev;
			node = node->right_tree;
		}
		else {
			printf("the target num has been exited.no need insert.\n");
			return head;
		}
	}
	avl_node* new_node = create_node(num);
	if (prev->num > num) {
		prev->left_tree = new_node;
	}
	else {
		prev->right_tree = new_node;
	}
	while (top != 0) {
		avl_node* curr_parent = stack[top--];
		Updateheight(curr_parent);
		prev = stack[top];
		int balance = get_balance(curr_parent);
		if (balance > 1) {
			int bal = get_balance(curr_parent->left_tree);
			if (bal > 0) {
				//LL
				if (prev->num > curr_parent->num) {
					prev->left_tree = right_rotation(curr_parent);
				}
				else if (prev->num < curr_parent->num)
				{
					prev->right_tree = right_rotation(curr_parent);
				}
			}
			else if (bal < 0) {
				//LR
				curr_parent->left_tree = left_rotation(curr_parent->left_tree);
				if (prev->num > curr_parent->num) {
					prev->left_tree = right_rotation(curr_parent);
				}
				else if (prev->num < curr_parent->num) {
					prev->right_tree = right_rotation(curr_parent);
				}

			}
		}
		else if (balance < -1) {
			int bal = get_balance(curr_parent->right_tree);
			if (bal > 0) {
				//RL
				curr_parent->right_tree = right_rotation(curr_parent->right_tree);
				if (prev->num > curr_parent->num) {
					prev->left_tree = left_rotation(curr_parent);
				}
				else if (prev->num < curr_parent->num) {
					prev->right_tree = left_rotation(curr_parent);
				}
			}
			else if (bal < 0) {
				//RR
				if (prev->num > curr_parent->num) {
					prev->left_tree = left_rotation(curr_parent);
				}
				else if (prev->num < curr_parent->num) {
					prev->right_tree = left_rotation(curr_parent);
				}
			}
		}
	}
	Updateheight(stack[0]);
	int balance = get_balance(stack[0]);
	if (balance > 1) {
		int bal = get_balance(head->left_tree);
		if (bal > 0) {
			//LL
			head = right_rotation(head);
		}
		else if (bal < 0) {
			//LR
			head->left_tree = left_rotation(head->left_tree);
			head = right_rotation(head);

		}
	}
	else if (balance < -1) {
		int bal = get_balance(head->right_tree);
		if (bal > 0) {
			//RL,右子树左重，父节点右重
			head->right_tree = right_rotation(head->right_tree);
			head = left_rotation(head);
		}
		else if (bal < 0) {
			//RR
			head = left_rotation(head);
		}
	}
	return head;
}
