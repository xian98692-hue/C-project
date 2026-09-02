#include "stdint.h"
#include "hei_mo_fa.h"

float Q_rsqrt(float number) {
	int32_t i;
	float x2, y;
	const float threehalfs = 1.5f;
	x2 = number * 0.5f;
	y = number;
	i = *(int32_t*)&y;//比特位黑魔法
	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;
	y = y * (threehalfs - (x2 * y * y));
	y = y * (threehalfs - (x2 * y * y));//第二轮迭代
	return y;
}

int isValid(char* s) {
    int len = strlen(s);
    if (len == 0) {
        return true;
    };
    if (len % 2 != 0) {
        return false;
    };
    char* left_array = (char*)malloc((len / 2) * sizeof(char));
    if (left_array == NULL)return false;
    char* right_array = (char*)malloc((len / 2) * sizeof(char));
    if (right_array == NULL)return false;

    for (int i = 0; i < len; i++) {
        int j = 0;
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            left_array[j] = s[i];
            j++;
        };
    };
    for (int i = 0; i < len; i++) {
        int j = 0;
        if (s[i] == ')' || s[i] == ']' || s[i] == '}') {
            right_array[j] = s[i];
            j++;
        };
    };
    for (int i = 0; i < (len / 2); i++) {
        if (right_array[i] == '}') {
            right_array[i] = '{';
        }
        else if (right_array[i] == ']') {
            right_array[i] = '[';
        }
        else if (right_array[i] == ')') {
            right_array[i] = '(';
        };
    };
    if (right_array == left_array) {
        return true;
    }
    else {
        return false;
    };
}