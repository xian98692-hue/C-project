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