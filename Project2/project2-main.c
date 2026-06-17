#include<stdio.h>
#include<stdlib.h>
// 🔴 必须加这一句！告诉main函数：twoSum在别的文件里
int* twoSum(int* nums, int numsSize, int target, int* returnSize);
int main() {
	int nums[] = { 2,7,11,15 };
	int target = 9;
	int returnSize;
	int* res = twoSum(nums, 4, target, &returnSize);
	printf("xiabiao:%d,%d\n",res[0], res[1]);

	int x = 10;
	int*p=&x;   // 定义一个整型指针
	// & 取地址：把x的地址交给p
	printf("zhizhendizhi:%p",p);
	free(res);
	return 999;
}