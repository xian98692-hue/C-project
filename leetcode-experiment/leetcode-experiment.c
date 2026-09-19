#include"experiment.h"
/*
void deduplicate(int** res, int rows) {
	//去重
	//把res内重复的数组去掉，不分顺序
	//排序后比较
	for (int i = 0; i < rows; i++) {//先对内部的每一个数组的整数进行排序
		int curr_i = res[i][0];
		int curr_j = res[i][1];
		int curr_k = res[i][2];
		if (curr_i < curr_k < curr_j) {
			res[i][1] = curr_k;
			res[i][2] = curr_j;
		}
		else if (curr_j < curr_i < curr_k) {
			res[i][0] = curr_j;
			res[i][1] = curr_i;
		}
		else if (curr_k < curr_j < curr_i) {
			res[i][0] = curr_k;
			res[i][2] = curr_i;
		}
		else if (curr_k < curr_i < curr_j) {
			res[i][0] = curr_k;
			res[i][1] = curr_i;
			res[i][2] = curr_j;
		}

	}

}
*/
unsigned factorial(unsigned n) {
	if (n == 0 || n == 1) {
		return 1;
	}
	return n * factorial(n - 1);
}

void matrix_multi(int arr1[rows][same], int arr2[same][columns],int res[rows][columns]) {
	for (int a = 0; a < rows; a++) {
		for (int b = 0; b < columns; b++) {
			res[a][b] = 0;
			for (int c = 0; c < same; c++) {
				res[a][b] += arr1[a][c] * arr2[c][b];
			}
		}
	}
}
void two_variable_traversal(int* nums,int numsSize) {//遍历2个变量的不同组合，计算组合的数量
	for (int i = 0; i < numsSize; i++) {
		for (int j = i + 1; j < numsSize; j++) {
			printf("the traversal nums combination is %d--%d.\n", nums[i], nums[j]);
		}
	}
}
unsigned int count_combination(unsigned int n,unsigned int k) {//n是目标的个数，k是要取的变量的个数
	//计算组合数
	return count_permutation(n, k) / count_permutation(k, k);
}
unsigned count_permutation(unsigned n,unsigned k) {
	//计算排列数
	if (n < k) {
		printf("n<k.\n");
		return 0;
	}
	else if (n == k) {
		return factorial(k);
	}
	unsigned res = 1;
	for (int i = 0; i < k; i++) {
		res *= n;
		n = n - 1;
	}
	return res;
}