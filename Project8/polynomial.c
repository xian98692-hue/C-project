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
			return -999;
		};
		tail->next = new_node;
		tail = tail->next;

		p1 = p1->next;
		p2 = p2->next;
	};
	
	return head;
}

//加法函数的时间复杂度 O(n + m)
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
		if (result_head == NULL) {//如果前面系数都等于0且第一次循环完还有剩余，result_head=NULL
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
/*外层每遍历 1 个 p1 节点，内层就要完整遍历 p2 的 m 个节点。

总执行次数 = n × m → 时间复杂度 O(n × m)。*/
node* polynomial_multi(node* poly1, node* poly2) {//len是相乘结果的项数，不含合并同类项
	node* p1 = poly1;
	node* p2 = poly2;
	node* head=NULL;
	node* tail=NULL;
	//一次相乘创建一个新节点，系数相乘,指数相加；
	//p1 p2长度相等
	while (p1 != NULL) {
		while (p2 != NULL) {
			int new_power = p1->power + p2->power;
			int new_coe = p1->coefficient * p2->coefficient;
			node* new_node = create_node(new_power, new_coe);
			if (head == NULL) {
				head = new_node;
				tail = new_node;
			}
			else if (head != NULL) {
				tail->next = new_node;
				tail = tail->next;
			};
			p2 = p2->next;
		};
		p1 = p1->next;
		p2 = poly2;
	};
	return head;
	
}

node* combine_like_terms(node** head) {
	node* first = *head;
	node* second = first->next;
	//比较当前节点的幂次和另一个节点的幂次是否相等，每次比较完都把另一个节点移到下一位，
	// 若second移到最后，就把second移到头，first移到下一点，直至first移到最后比较完全
	//如果幂次相等，first系数相加，把second置0
	//为了避免重复比较，second总是至少与first相差一个边
	node* second_head = first->next;

	while (second_head!=NULL) {
		while (second != NULL) {
			if (first->power == second->power) {
				first->coefficient += second->coefficient;
				second->power = 0;
				second->coefficient = 0;
			};
			second = second->next;
		};
		first = first->next;
		second_head = second_head->next;
		second = second_head;
	}

	return *head;
}
//实现复杂度是 O(K²),其中 K = M×N,M、N分别为两个多项式的项数
node* combine_like_terms_2(node* head) {
	if (head == NULL) return NULL;

	node* p1 = head;
	// 外层循环：遍历每个节点作为基准
	while (p1 != NULL) {
		node* prev = p1;          // 前驱指针，用于删除 p1 后面的节点
		node* p2 = p1->next;      // 内层从 p1 的下一个开始
		while (p2 != NULL) {
			if (p1->power == p2->power) {
				// 系数相乘
				p1->coefficient += p2->coefficient;
				// 删除 p2 节点
				prev->next = p2->next;
				free(p2);
				p2 = prev->next;  // 继续下一个
			}
			else {
				prev = p2;
				p2 = p2->next;
			}
		}
		p1 = p1->next;  // 移动外层指针
	}
	// 第二步：删除所有系数为 0 的节点（包括头节点）
	node* dummy = create_node(0, 0);  // 哑节点简化头删除
	dummy->next = head;
	node* prev = dummy;
	node* curr = head;
	while (curr != NULL) {
		if (curr->coefficient == 0) {
			prev->next = curr->next;
			free(curr);
			curr = prev->next;
		}
		else {
			prev = curr;
			curr = curr->next;
		}
	}
	head = dummy->next;
	free(dummy);  // 释放哑节点
	return head;
}