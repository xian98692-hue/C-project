#include"ListNode.h"


int main(void) {
	int value[] = {5,10,15,20,25};
	int k = sizeof(value)/sizeof(value[0]);
	printf("%d\n", k);
	list_node* head=create_node(value, k);
	//printf_list(head);

	int array[] = { 30,35,40,45,50 };

	int arr[] = { 666,777,888,999,111 };
	insert_node(array, k, &head);
	insert_node(arr, k, &head->next);
	printf_list(head);

    free_list(head);
	return 0b1111;
};