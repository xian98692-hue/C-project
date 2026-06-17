#include<stdio.h>
#include<stdlib.h>
float Q_rsqrt(float number);
//  必须加这一句！告诉main函数：twoSum在别的文件里
int* twoSum(int* nums, int numsSize, float target, int* returnSize);
int main() {
	float target = 25;
	float y = Q_rsqrt(target);
	printf("result=%f\n",y);

	return 999;
}