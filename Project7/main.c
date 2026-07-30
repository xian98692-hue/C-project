#include"hash.h"
#include"array.h"
#include"stdio.h"
int main(void) {
	// 例子 1：哈希字符串（虽然它带 len，但通常传 strlen）
	char* str = "hello";
	uint32_t h1 = hash_fnv1a(str, 5); // 处理 'h','e','l','l','o' 这5个字节
	// 例子 2：哈希一个整数数组（二进制数据）
	int arr[3] = { 100, 200, 300 };
	// 注意：这里传入的是 arr（等同于 &arr[0]），长度是整个数组占用的字节数
	uint32_t h2 = hash_fnv1a(arr, sizeof(arr));

	// 例子 3：哈希一个结构体
	struct Point { int x; int y; } pt = { 10, 20 };
	uint32_t h3 = hash_fnv1a(&pt, sizeof(pt)); // 处理该结构体内存区域的原始字节
	printf("%u,%u,%u\n", h1, h2, h3);
	printf("%x,%x,%x\n", h1, h2, h3);
	array_cpy();

	return 666;
};