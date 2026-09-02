#include"polynomial.h"
#include"stdio.h"
int main(void) {
	int pow_1[] = {1,3,5,7,9,4,-2,-11,3,-3};
	int coe_1[] = {3,4,15,6,18,3,20,11,3,2};
	int pow_2[] = { 2,4,6,7,9,-4,10,12,-6,11 };
	int coe_2[] = {1,3,5,6,8,4,6,12,42,10};
	node* head_1 = create_polynomial(pow_1, coe_1, 10);
	node* head_2 = create_polynomial(pow_2, coe_2, 10);
	//node* list = polynomial_add_2(head_1,head_2);
	node* list = polynomial_multi(head_1, head_2);
	list = combine_like_terms_2(list);
	while (list != NULL) {
		printf("%dx^%d+", list->coefficient, list->power);
		list = list->next;
	};
	printf("0");
	return 0;
};