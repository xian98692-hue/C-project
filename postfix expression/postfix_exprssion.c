#include"postfix_expression.h"
#include"stdlib.h"
#include"ctype.h"
int postfix(char express[], int len) {
	int stack_exprss[MAX_SIZE] = { 0 };
	int top = 0;
	for (int i = 0; i < len; i++) {
		char curr = express[i];
		if (isdigit(curr) ){//curr >= '0' && curr <= '9'
			stack_exprss[top++] = curr-'0';//此时top指向空位置
		}
		else if (curr == '+') {
			int first = stack_exprss[--top];
			int second = stack_exprss[--top];
			stack_exprss[top++] = first+second;
		}
		else if (curr == '*') {
			int first = stack_exprss[--top];
			int second = stack_exprss[--top];
			stack_exprss[top++] = first * second;
		}else if (isspace(curr)) {
			continue;
		};
	};
	return stack_exprss[--top];
}

int char_to_int(char x) {
	int num=0;
	if (x >= '0' && x <= '9') {
		num = x - '0';
	};
	return num;
}

int postfix_list(char express[], int len) {
	stack* head = NULL;
	for (int i = 0; i < len; i++) {
		char curr = express[i];
		if (isdigit(curr)) {
			int int_curr = curr - '0';
			if (head == NULL) {
				head = create_stack_node(int_curr);
			}
			else if (head != NULL) {
				head = push_stack(head, int_curr);
			};
		}
		else if (isspace(curr)) {
			continue;
		}
		else if (curr == '+') {
			int first = head->val;

			head = pop_stack(head);
			int second = head->val;
			int result = first + second;
			head->val = result;
		}
		else if (curr == '*') {
			int first = head->val;
			head = pop_stack(head);
			int second = head->val;
			int result = first * second;
			head->val = result;
		};
	};
	return head->val;
}