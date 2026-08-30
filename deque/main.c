#include"deque.h"
#include"stdio.h"
int main(void) {
	int x[] = { 1,2,3,4,5 };
	deque* head = create_deque(x, 5, 'h');
	if (head == NULL) {
		printf("Deque creation failed.\n");
		return 1;
	};

	head = Push(0, head);

	PrintDeque(head,'h');

	return 0;
};