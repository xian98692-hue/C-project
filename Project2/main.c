#include"stdio.h"
#include "hei_mo_fa.h"

int main() {
	float number = Q_rsqrt(100);
	//printf("%.4f",number);
	
	char* s = "()[][][]";
	int len = strlen(s);
	//printf("%d", len);
    int k=isValid(s);
    printf("%d", k);
	return 0;

};