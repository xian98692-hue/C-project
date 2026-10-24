#include<stdbool.h>
#include<stdio.h>
bool int_shift_are_arithmetic(void) {//判断机器是否使用算术右移
	int x = ~0;
	return (x >> 1) == x;
}

//一个函数：从一个数中选取第k位，判断某一位的状态
int select_num_binary(int num, int k) {
	int w = sizeof(int) * 8;//num的位数
	if (k >= w || k < 0) {
		printf("not proper k.\n");
		return -999;
	}
	int x = (1 << k) ;//获取一个数，第k位是1，其余都是0
	int res = (num & x)^x;//如果第k位是1，得到000...0001000...，res=0;如果第k位是0，得到000...,res=1
	//printf("the %d position is %d\n",k, !res);
	return !res;//return ((num>>k)&1)^1
}
//一个函数：打印出一个数的二进制形式，打印位数随函数决定
void print_binary_num(int num, int w) {
	if (w >= (sizeof(num) * 8)||w<0) {
		printf("error.not proper bits nums.\n");
		return;
	}
	for (int i = w; i >= 0; i--) {
		int y = select_num_binary(num, i);
		printf("%d", y);
	}
}
//截断：2种方法
void truncate_bianry_num(int num, char s,int position) {
	if (position >= (sizeof(num) * 8) || position < 0) {
		printf("the position is not proper.\n");
		return;
	}
	if (s == '0'){
		int res = num & ((1 << (position + 1)) - 1);
		print_binary_num(res, position);
		printf("\n");
	}
	else if (s == '1') {
		int temp = num;
		for (int i = position+1; i < (sizeof(num) * 8); i++) {
			if (select_num_binary(temp, i) == 1) {
				num -= (1 << i);
			}
	}
		print_binary_num(num, position);
		printf("\n");
	}
	else {
		return;
	}
}
int main() {
	printf("int_shift_are_arithmetic() = %d\n",
		int_shift_are_arithmetic());
	print_binary_num(27282, 14);//110101010010010
	printf("\n");
	truncate_bianry_num(27282, '1', 7);//10010010
	truncate_bianry_num(27282, '0', 7);//10010010
	return 0;
}