#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"binary-heap.h"
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
	struct heap* node = init_heap(20);
	insert(node, 2);
	insert(node, 1);
	printf("the array[%d]'s num is %d\n", 0, node->array[0]);//the array[0]'s num is 1
	delete_top(node);
	printf("the array[%d]'s num is %d\n", 0, node->array[0]);//the array[0]'s num is 2
	printf("the heap's size is %d \n", node->size);//1
	insert(node, 3);
	insert(node, 6);
	insert(node, 8);
	insert(node, 9);
	insert(node, -1);
	for (int i = 0; i < node->size; i++) {
		printf("the array[%d]'s num is %d\n", i, node->array[i]);
	}
	/*the array[0]'s num is -1
the array[1]'s num is 3
the array[2]'s num is 2
the array[3]'s num is 8
the array[4]'s num is 9
the array[5]'s num is 6*/
	delete_top(node);
	for (int i = 0; i < node->size; i++) {
		printf("the array[%d]'s num is %d\n", i, node->array[i]);
	}/*the array[0]'s num is 2
the array[1]'s num is 3
the array[2]'s num is 6
the array[3]'s num is 8
the array[4]'s num is 9*/
	return 0;
};