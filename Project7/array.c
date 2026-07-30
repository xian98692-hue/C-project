#include"array.h"
#include"stdio.h"
#include"string.h"
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