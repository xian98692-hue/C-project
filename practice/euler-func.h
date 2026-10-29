long long phi_efficient(long long n);

struct node {
	struct node** array;
	int value;
	int capacity;
	int top;
};
struct node* initialize_node(int capa, int val);
void point_to(struct node* x, struct node* y);

void free_graph(struct node* x);

void print_graph(struct node* x);