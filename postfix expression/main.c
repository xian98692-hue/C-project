#include"stack.h"
#include"postfix_expression.h"
int main(void) {
	

	char express[] = "7 5 2 5+8*+3+*";
	int k=postfix(express, 14);
	printf("%d\n", k);

	int x = postfix_list(express, 14);
	printf("%d", x);
	return 0;
}