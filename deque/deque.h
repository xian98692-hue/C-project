#ifndef DEQUE_H
#define DEQUE_H

typedef struct deque {
	int num;
	struct deque* forward;
	struct deque* behind;
}deque;

deque* Push(int x, deque* head);
deque* Inject(int x, deque* tail);
deque* Pop(deque** head);
deque* Eject(deque** tail);
void PrintDeque(deque* node,char c);
deque* create_deque(int x[],int len,char choice);
deque* create_node(int x);
#endif