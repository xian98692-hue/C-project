#include"polynomial.h"
#include"stdio.h"
#include"stdlib.h"
node* create_node(int power, int coefficient) {
	node* head = (node*)malloc(sizeof(node));
	// 1. 增加内存分配失败的检查
	if (head == NULL) {
		// 可以在这里打印错误信息，或者直接返回 NULL，让上层处理
		printf("内存分配失败！\n");
		return NULL;
	};
	head->power = power;
	head->coefficient = coefficient;
	head->next = NULL;
	return head;
}

node* create_polynomial(int power[], int coefficient[],int len) {	
	node* head = NULL;
	node* tail = NULL;

	for (int i = 0; i < len; i++) {
		node* new_node = create_node(power[i], coefficient[i]);
		if (head == NULL) {
			head = new_node;
			tail = new_node;
		}
		else {
			tail->next = new_node;
			tail = new_node;
		};
	};
	return head;
}

node* polynomial_add_1(node* polynomial_1, node* polynomial_2) {
	node* head = NULL;
	node* tail = NULL;
	node* p1 = polynomial_1;
	node* p2 = polynomial_2;

	while (p1 != NULL && p2 != NULL) {
		int sum = p1->coefficient + p2->coefficient;
		node* new_node = create_node(p1->power, sum);
		if (head == NULL) {
			head = new_node;
			tail = new_node;
		};
		if (tail == NULL) {
			printf("take error.");
			return;
		};
		tail->next = new_node;
		tail = tail->next;

		p1 = p1->next;
		p2 = p2->next;
	};
	
	return head;
}


node* polynomial_add_2(node* poly1, node* poly2) {
	node* result_head = NULL;   // 结果链表头
	node* result_tail = NULL;   // 结果链表尾
	node* p1 = poly1;
	node* p2 = poly2;

	while (p1 != NULL && p2 != NULL) {
		int sum_coeff;
		int new_power;

		if (p1->power == p2->power) {
			sum_coeff = p1->coefficient + p2->coefficient;
			new_power = p1->power;
			p1 = p1->next;
			p2 = p2->next;
		}
		else if (p1->power < p2->power) {
			sum_coeff = p1->coefficient;
			new_power = p1->power;
			p1 = p1->next;
		}
		else { // p1->power > p2->power
			sum_coeff = p2->coefficient;
			new_power = p2->power;
			p2 = p2->next;
		}

		// 如果系数不为0，则创建节点并加入结果链表
		if (sum_coeff != 0) {
			node* new_node = create_node(new_power, sum_coeff);
			if (result_head == NULL) {
				result_head = new_node;
				result_tail = new_node;
			}
			else {
				result_tail->next = new_node;
				result_tail = new_node;
			}
		}
	}

	// 将剩余未遍历的节点直接复制到结果链表（注意：系数不变）
	node* remaining = (p1 != NULL) ? p1 : p2;
	while (remaining != NULL) {
		node* new_node = create_node(remaining->power, remaining->coefficient);
		if (result_head == NULL) {
			result_head = new_node;
			result_tail = new_node;
		}
		else {
			result_tail->next = new_node;
			result_tail = new_node;
		}
		remaining = remaining->next;
	}

	return result_head;
}