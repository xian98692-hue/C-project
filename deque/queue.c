#include"deque.h"
#include"stdio.h"
#include"stdlib.h"
deque* Push(int x, deque* head) {
	deque* new_node= create_node(x);
	head->forward = new_node;
	new_node->behind = head;
	head = head->forward;

	return head;
};

deque* Inject(int x, deque* tail) {
	deque* new_node = create_node(x);
	tail->behind = new_node;
	new_node->forward = tail;
	tail = tail->behind;
	return tail;
};
deque* create_node(int x) {

	deque* node= (deque*)malloc(sizeof(deque));
	if (node == NULL) {
		perror("malloc failed");
		return NULL;
	};
	//printf("Allocated node at %p, size=%zu\n", (void*)node, sizeof(deque));
	node->num = x;
	node->forward = NULL;
	node->behind = NULL;

	return node;
}
deque* create_deque(int x[],int len,char choice) {
	deque* head=NULL;
	deque* tail=NULL;
	if (len <= 0) {
		printf("len<=0");
		return NULL;
	};
	for (int i = 0; i < len; i++) {
		deque* node = create_node(x[i]);
		if (head == NULL) {
			head = tail = node;
		}
		else {
			tail->behind = node;
			node->forward =tail;
			tail= node;
		};

	};
	if (choice == 'h') {
		return head;
	}
	else if (choice == 't') {
		return tail;
	}
	else {
		printf("error choice.");
		return NULL;
	};
};

void PrintDeque(deque* node,char c) {
	while (node != NULL) {
		if (c == 'h') {
			printf("%d->", node->num);
			node = node->behind;
		}
		else if (c == 't') {
			printf("%d<-", node->num);
			node = node->forward;
		}
		else {
			printf("error");
			break;
		};
	};
}

int Pop(deque** head) {
	int x=(*head)->num;
	deque* temp = *head;
	*head = (*head)->behind;
	free(temp);
	return x;
}

int Eject(deque** tail) {
	int x = (*tail)->num;
	deque* temp = *tail;
	*tail = (*tail)->forward;
	free(temp);
	return x;
}