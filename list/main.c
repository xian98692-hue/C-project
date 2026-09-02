#include"ListNode.h"


int main(void) {
	int value[] = {5,10,15,20,25,30,40,50};
	int k = sizeof(value)/sizeof(value[0]);
	printf("%d\n", k);
	list_node* head=create_node(value, k);
	/*
	int arr[] = { 666,777,888,999,111 };
	insert_node(arr, k, &head->next);
	printf_list(head);
	printf("\n");
	normal_delete(111, &head);
	printf_list(head);
	*/

	lazy_delete_mark(5, &head);
	printf("%d\n",head->delete_mark == true);//1
	//printf_list(head);
	lazy_delete_mark(20, &head);
	lazy_delete_mark(25, &head);
	lazy_delete_mark(50, &head);
	lazy_delete(&head);
	printf_list(head);
	return 0b1111;
};