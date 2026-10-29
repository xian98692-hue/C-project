#define MAIN

#ifdef MAIN
#include<stdio.h>
#include<time.h>
#include"euler-func.h"
int main(void) {
	srand((unsigned)time(NULL));
	int size = 10000;
	struct node* graph = initialize_node(10, 1);
	for (int i = 0; i < size; i++) {
		struct node* temp = initialize_node(1, rand() % 10001);
		point_to(graph, temp);
	}
	print_graph(graph);

	free_graph(graph);
	return 0;
}

#endif // MAIN
