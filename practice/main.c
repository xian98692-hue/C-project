#include<stdbool.h>
#include<stdio.h>
bool int_shift_are_arithmetic(void) {//判断机器是否使用算术右移
	int x = ~0;
	return (x >> 1) == x;
}

int main() {
	printf("int_shift_are_arithmetic() = %d\n",
		int_shift_are_arithmetic());
	return 0;
}