#define _CRT_SECURE_NO_WARNINGS
#define MASTER
#ifdef MASTER
#include<stdio.h>
#include"binomial-queue.h"
int main(void) {
	int nums[10] = { 0 };
	int cnt = 0;
	queue* root = NULL;
	while (cnt < 10) {
		printf("the num[%d] is ", cnt);
		scanf("%d", &nums[cnt]);
		root = insert_queue(root, nums[cnt]);
		cnt++;
	}
	print_queue(root);
	clear_queue(root);
	return 0;
}

#endif // MASTER
