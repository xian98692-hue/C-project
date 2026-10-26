
struct heap {
	int* array;
	int size;
	int capacity;
};
struct heap* init_heap(int max_capacity);
void insert(struct heap* heap, int num);
void delete_top(struct heap* heap);
void sink(struct heap* heap, int curr_idx);
//检查堆序性
int check_heap_sequence(struct heap* heap);
void delete_root(struct heap* heap);
void print_heap(struct heap* heap);