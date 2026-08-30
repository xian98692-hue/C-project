#include"deque.h"
#include"stdio.h"
int main(void) {
	int x[] = { 1,2,3,4,5 };
	deque* head = create_deque(x, 5, 'h');
	deque* tail = create_deque(x, 5, 't');
	if (head == NULL) {
		printf("Deque creation failed.\n");
		return 1;
	};

	//head = Push(0, head);
	tail = Inject(666, tail);
	PrintDeque(head,'h');
	printf("\n");
	PrintDeque(tail, 't');

	printf("\n");

	int k=Pop(&head);
	printf("%d\n", k);
	PrintDeque(head, 'h');
	return 0;
};