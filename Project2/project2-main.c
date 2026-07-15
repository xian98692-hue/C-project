#include<stdio.h>
#include<stdlib.h>
float Q_rsqrt(float number);
int main() {
	float target = 25;
	float y = Q_rsqrt(target);
	printf("result=%f\n",y);

	return 999;
}