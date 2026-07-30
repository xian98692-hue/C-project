#ifndef _POLYNOMIAL_H
#define _POLYNOMIAL_H

typedef struct ListNode {
	unsigned int power;
	unsigned int coefficient;
	struct ListNode* next;
}node;
node* create_node(int power, int coefficient);
node* create_polynomial(int power[], int coefficient[], int len);
node* polynomial_add_1(node* polynomial_1,node* polynomial_2);
node* polynomial_add_2(node* poly_1, node* poly_2);
#endif
