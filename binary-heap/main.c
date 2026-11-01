#define _CRT_SECURE_NO_WARNINGS
//#define MAIN
#include <stdio.h>
int not_include_nums(int n) {
	int count = 0;
	char t[32];
	for (int i = 0; i <= n; i++) {
		sprintf(t, "%d", i);        // 把整数 i 转成字符串
		if (strchr(t, '1') == NULL && strchr(t, '9') == NULL) {
			count++;
		};
	};
	return count;
}

void array_malloc(int* returnSize, int** returnColumnSizes) {
	//创建二维数组，分配内存
	int row = *returnSize;
	int** res = (int**)malloc(sizeof(int*) * row);
	if (res == NULL) {
		printf("malloc res failed.\n");
		return;
	}
	//returnColumnSizes的行数和二维数组的行数一致，即等于row
	for (int i = 0; i < row; i++) {
		int columns = (*returnColumnSizes)[i];
		res[i] = (int*)malloc(sizeof(int) * columns);
		if (res[i] == NULL) {
			printf("malloc failed.the i num is %d.\n", i);
		}
		if (res[i] != NULL) {
			printf("malloc successfully.the i num is %d.\n", i);
		}
	}
	for (int i = 0; i < row; i++) {
		free(res[i]);
	}
	free(res);
	printf("free ok.\n");
}
#ifdef MAIN
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"binary-heap.h"

int main() {
	/*
	printf("Hello World.\n");

	int s[10] = { 29,438,1928,4839,283,990,47,42,384,1209 };
	for (int i = 0; i <= 9; i++) {
		printf("%d\n", not_include_nums(s[i]));
	};

	int array[3] = {
		1,2,3
	};
	int* arr = array;
	int** returnColumnSizes =&arr ;
	int size = 3;//3行
	int* returnSize = &size;
	array_malloc(returnSize,returnColumnSizes);
	*/
	/*
	srand((unsigned)time(NULL));
	struct heap* new_heap = init_heap(20);
	for (int j = 0; j < 100; j++) {
		int r = -10000 + rand() % 20001;
		insert(new_heap, r);
	}
	printf("the heap's size is %d \n", new_heap->size);
	//printf("the array[%d]'s num is %d\n",0, new_heap->array[0]);
	*/
	/*
	struct heap* h = init_heap(10);

	int a[] = { 1, 3, 2, 7, 8, 9, 10 };
	for (int i = 0; i < 7; i++) {
		insert(h, a[i]);
	}

	// 手动破坏：把根改成 100
	h->array[0] = 100;
	print_heap(h);

	sink(h, 0);
	print_heap(h);
	// 期望恢复最小堆，根变成 2 或 3
	check_heap_sequence(h);
	*/

	leh* root=NULL;
	leh* root1=NULL;
	int arr[8] = { 3,10,21,14,23,8,17,26 };
	int att[8] = { 1,5,-7,9,12,-9,25,22 };
	for (int i = 0; i < 8; i++) {
		root = insert_leh(root, arr[i]);
		root1 = insert_leh(root1, att[i]);
	}
	printf("\n");
	root = iteration_merge(root, root1);
	print_leh(root);
	free_leh(root);
	return 0;
};
#endif