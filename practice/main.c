//#define ENABLE_BINARY_NUM  
#define MAIN
#ifdef ENABLE_BINARY_NUM
#include "binary-num.h"
#endif

#include"euler-func.h"
#ifdef MAIN

#include<stdio.h>
#include<stdlib.h>
#include"sort.h"
int main() {
#ifdef ENABLE_BINARY_NUM
	print_binary_num(27283, 14);
	printf("\n");
	truncate_bianry_num(27283, '1', 7);
	truncate_bianry_num(27283, '0', 7);
#endif
	
	int size = 10;
	int* num = malloc(sizeof(int)*size);
	int arr[10] = { 2,7,4,1,0,12,-6,9,3,-5};
	for (int i = 0; i < size; i++) {
		num[i] = arr[i];
	}
	//bubble_sort(num, size);//-6 -5 0 1 2 3 4 7 9 12
	//insertion_sort(num, size);//-6 -5 0 1 2 3 4 7 9 12
	//shell_sort(num, size);//-6 -5 0 1 2 3 4 7 9 12
	//selection_sort(num, size);//-6 -5 0 1 2 3 4 7 9 12
	//merge_sort(num, size);//-6 -5 0 1 2 3 4 7 9 12
	merge_sort_iteration(num, size);
	for (int cnt = 0; cnt < size; cnt++) {
		printf("%d ", num[cnt]);
	}
	free(num);
	
	/*
	// 使用当前时间作为随机数种子，确保每次运行结果不同
	srand((unsigned int)time(NULL));

	for (int i = 1; i <= 10; i++) {
		// 生成 1 到 100000 之间的随机数
		long long n = rand() % 100000 + 1;
		long long result = phi_efficient(n);
		printf("the %02d test:n=%-6lld,phi(n)=%-6lld\n", i, n, result);
	}
	*/
	return 0;
}
#endif