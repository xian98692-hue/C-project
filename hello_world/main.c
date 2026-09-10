#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>

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
int main() {
	printf("Hello World.\n");
	int s[10] = { 29,438,1928,4839,283,990,47,42,384,1209 };
	for (int i = 0; i <= 9; i++) {
		printf("%d\n", not_include_nums(s[i]));
	};
	return 0;
};