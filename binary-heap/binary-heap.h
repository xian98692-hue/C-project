#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H
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

typedef struct left_heap {
	struct left_heap* lchild;
	struct left_heap* rchild;
	int value;
	int npl;
}leh;
leh* create_leh_node(int val);
leh* merge(leh* x, leh* y);
leh* merge1(leh* x, leh* y);//保证x的值小于y的值
leh* insert_leh(leh* root, int val);
leh* delete_leh_top(leh* root);
void swapchild(leh* node);
void print_leh(leh* root);
void free_leh(leh* root);

leh* iteration_merge(leh* x, leh* y);
#endif