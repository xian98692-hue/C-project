#include"array.h"
#include"stdio.h"
#include"string.h"
#include"stdint.h"
void array_cpy(void) {
    int src[5] = { 1, 2, 3, 4, 5 };
    int dest[5] = { 0 };

    // 计算总字节数：5个元素 * 每个int占4字节 = 20字节
    memcpy(dest, src, sizeof(src));

    // 验证结果
    for (int i = 0; i < 5; i++) {
        printf("%d ", dest[i]); // 输出：1 2 3 4 5
    };
};

void strlen_sizeof_cmp(void) {
    char str1[] = "Hello";      // 数组，实际占6字节（含\0）
    char* str2 = "Hello";       // 指针，指向字符串常量

    // 数组情况
    printf("\n%llu\n", sizeof(str1)); // 输出 6（整个数组容量）
    printf("%llu\n", strlen(str1)); // 输出 5（实际字符数，不含\0）

    // 指针情况（重点！）
    printf("%llu\n", sizeof(str2)); // 输出 8（指针变量本身的大小，在64位系统下）
    printf("%llu\n", strlen(str2)); // 输出 5（指针指向的字符串长度）

    // 动态分配内存
    char* dup = strdup("Hi");
    printf("%llu\n", sizeof(dup));  // 输出 8（指针大小，不是字符串长度！）
    printf("%llu\n", strlen(dup));  // 输出 2（正确获取长度）
    free(dup);

    printf("*'s size:%llu\n", sizeof(void*));//x86是4，x64是8
};