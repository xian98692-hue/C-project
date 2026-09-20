#include"experiment.h"
#include<stdio.h>
int main(void) {
	unsigned count = factorial(12);
	printf("%d.\n", count);
	int arr1[rows][same] = { {1,2,3},{1,2,1} };
	int arr2[same][columns] = { {2,2},{1,1},{3,9} };
	int res[rows][columns] = { 0 };
	matrix_multi(arr1, arr2, res);
	for (int a = 0; a < rows; a++) {
		for (int b = 0; b < columns; b++) {
			printf("the num is %d.\n", res[a][b]);
		}
	}
	int arr[5] = { 1,2,3,4,5 };
	int* nums = &arr[0];//int* nums=arr;
	two_variable_traversal(nums, 5);
	three_variable_traversal(nums, 5);
	printf("the permutation is %d.\n", count_permutation(10, 3));
	printf("the combinations count is %d.\n", count_combination(5, 3));
	return 0;
}