#include"ListNode.h"


int main(void) {
	int value[] = {5,10,15,20,25};
	int k = sizeof(value)/sizeof(value[0]);
	printf("%d\n", k);
	list_node* head=create_node(value, k);
	int arr[] = { 666,777,888,999,111 };


	insert_node(arr, k, &head->next);
	printf_list(head);
	printf("\n");
	normal_delete(111, &head);
	printf_list(head);

    
	return 0b1111;
};