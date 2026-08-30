#include "stdlib.h"
#include "stdio.h"
#include "ListNode.h"


list_node* create_node(int val[], int len) {
	list_node* head=NULL;
	list_node* prev = NULL;
	list_node* node = NULL;
	for (int i = 0; i < len; i++) {
		node = (list_node*)malloc(sizeof(list_node));
		if (node == NULL) {
			printf("malloc = NULL.");
			return 0;
		};
		node->value = val[i];
		node->next = NULL;
		if (head==NULL) {
			head = node;
			prev = node;
		}
		else {
			
			prev->next = node;
			prev = node;
		};
	};
	return head;
};
void printf_list(list_node* head) {
	while (head != NULL) {
		printf("%d->", head->value);
		head = head->next;
	};
	
};

void free_list(list_node* head) {
	list_node* tmp = NULL;
	while (head != NULL) {
		tmp = head;
		head = head->next;
		free(tmp);//一块内存被free后，不能再被->访问
	};
	if (head == NULL) {
		printf("\nfree successfully.");
	};

};

//在任意节点上插入新节点
//二级指针可以修改外部变量
void insert_node(int val[], int length,list_node** old_node) {
	list_node* new_node = create_node(val, length);
	list_node* old_next_node = (*old_node)->next;//restore

	(*old_node)->next = new_node;//旧节点的指针内容被修改，指向新节点
	//要使得新链表的尾部节点指向原有的旧的接下来的节点地址
	for (int i = 1; i < length; i++) {
		new_node = new_node->next;
	};

	new_node->next = old_next_node;
};

void normal_delete(int val, list_node** head) {//标准删除算法，需防止free后节点断裂指向
	list_node* node = *head;
	list_node* prev = NULL;
	while (node != NULL) {
		if (node->value == val) {
			if (prev == NULL) {
				// 删除的是头节点
				*head = node->next;
			}
			else {
				// 删除的是中间或尾节点
				prev->next = node->next;
			}
			free(node);
			printf("Deleted %d successfully.\n", val);
			return;
		}
		prev = node;
		node = node->next;
	};
	printf("no target to be deleted.");
}

void lazy_delete_mark(int val, list_node** head) {
	list_node* node = *head;
	while (node != NULL) {
		if (node->value == val) {
			node->k = true;
			break;
		};
		node = node->next;
	};
	printf("not found target.");
}