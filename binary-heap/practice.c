#include<stdio.h>
char* my_strcpy(char* dest, const char* src) {
	char* target = dest;
	while (*src != '\0') {
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return target;
}
size_t my_strlen(const char* src) {
	size_t cnt = 0;
	if (src == NULL) {
		return 0;
	}
	while (*src != '\0') {
		src++;
		cnt++;
	}
	return cnt;
}
char* my_strncpy(char* dest, const char* src, size_t n) {
	if (n == 0) return dest;
	char* res = dest;
	// 1. 复制 src 的字符，直到遇到 '\0' 或写满 n 个
	while (n > 0 && *src != '\0') {
		*dest++ = *src++;
		n--;
	}

	// 2. 如果 src 提前结束，剩余位置全部填 '\0'
	while (n > 0) {
		*dest++ = '\0';
		n--;
	}

	return res;
}