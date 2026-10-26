#include<stdio.h>
#include<stdlib.h>
#include"binary-heap.h"
struct heap* init_heap(int max_capacity) {
	struct heap* H;
	if (max_capacity < 10) {
		printf("the capacity is too small.");
		return NULL;
	}
	H = (struct heap*)malloc(sizeof(struct heap));
	if (H == NULL) {
		printf("the heap malloc error.");
		return NULL;
	}
	H->array = (int*)malloc(sizeof(int) * max_capacity);
	if (H->array == NULL) {
		printf("the array malloc error.");
		free(H);
		return NULL;
	}
	H->size = 0;
	H->capacity = max_capacity;
	for (int cnt = 0; cnt < max_capacity; cnt++) {
		H->array[cnt] = 999;//every element init to 999
	}
	return H;
}
/*从下标 0 开始存储：
• 父节点：(i - 1) / 2
• 左孩子：2 * i + 1
• 右孩子：2 * i + 2
*/
void insert(struct heap* heap, int num) {//上浮
	// -1/2==0
	if (heap->size == heap->capacity) {
		int* new_arr = (int*)realloc(heap->array, sizeof(int) * (heap->capacity * 2));
		if (new_arr == NULL) {
			printf("realloc fail.\n");
			return;
		}
		heap->array = new_arr;
		heap->capacity *= 2;
		printf("the heap has been expanded to capacity %d\n", heap->capacity);
	}
	int i;
	int* arr = heap->array;
	arr[heap->size] = num;
	for (i = heap->size; i > 0; i = (i - 1) / 2) {//最小堆，堆顶最小，以下标0为开始
		if (arr[(i - 1) / 2] <= num) {
			break;
		}
		else if (arr[(i - 1) / 2] > num) {
			arr[i] = arr[(i - 1) / 2];
			arr[(i - 1) / 2] = num;
		}
	}
	heap->size++;
	return;
}
void delete_top(struct heap* heap) {
	if (heap == NULL || heap->size == 0) {
		return;
	}
	int* arr = heap->array;
	int end = arr[heap->size - 1];
	heap->size--;
	if (heap->size == 0) {
		return;
	}
	arr[0] = end;
	int idx = 0;
	while (1) {
		int left_idx = 2 * idx + 1;
		int right_idx = 2 * idx + 2;

		// 没有左孩子 → 没有孩子 → 结束
		if (left_idx >= heap->size) {
			break;
		}
		// 先假设左孩子是较小孩子
		int min_idx = left_idx;
		// 只有右孩子存在时才能读 arr[right_idx]
		if (right_idx < heap->size && arr[right_idx] < arr[left_idx]) {
			min_idx = right_idx;
		}
		// 已满足最小堆性质
		if (arr[idx] <= arr[min_idx]) {
			break;
		}
		// 交换当前节点和较小孩子
		int temp = arr[idx];
		arr[idx] = arr[min_idx];
		arr[min_idx] = temp;
		// 继续下沉到被交换的孩子
		idx = min_idx;
	}
}
int check_heap_sequence(struct heap* heap) {
	if (heap == NULL || heap->size == 0) {
		printf("the heap is null.\n");
		return 0;
	}
	for (int i = 1; i < heap->size; i++) {
		int parent = (i - 1) / 2;
		if (heap->array[parent] > heap->array[i]) {
			printf("the heap is not proper. i=%d, parent=%d\n", i, parent);
			return 0;
		}
	}
	return 1;
}
void sink(struct heap* heap, int curr_idx) {//下沉
	if (heap == NULL||heap->size==0) {
		printf("the heap is NULL or empty.\n");
		return;
	}
	int* arr = heap->array;
	while (1) {
		if (curr_idx * 2 + 1 >= heap->size) {
			printf("the current idx's node is leave.no child.\n");//无孩子
			break;
		}
		int left = curr_idx * 2 + 1;
		int right = curr_idx * 2 + 2;
		int min_idx = left;
		if (right < heap->size && arr[right] < arr[left]) {
			min_idx = right;
		}
		if (arr[min_idx] >= arr[curr_idx]) {
			break;
		}
		int temp = arr[min_idx];
		arr[min_idx] = arr[curr_idx];
		arr[curr_idx] = temp;
		curr_idx = min_idx;
	}
	
}
void delete_root(struct heap* heap) {
	if (heap == NULL || heap->size == 0) {
		printf("the heap is empty.\n");
		return;
	}
	int* arr = heap->array;
	int end = arr[heap->size - 1];
	heap->size--;
	if (heap->size == 0) {
		return;  // 原来只有一个元素，删完为空，不需要下沉
	}
	arr[0] = end;
	sink(heap, 0);
}
void print_heap(struct heap* heap) {
	int* arr = heap->array;
	printf("size = %d, capacity = %d\n", heap->size, heap->capacity);
	printf("heap is [");
	for (int i = 0; i < heap->size; i++) {
		printf("%d,",arr[i]);
	}
	printf("]");
}
/*
d-堆：
从下标 0 开始存储：
父节点：(i - 1) / d
1孩子：d * i + 1
2孩子：d * i + 2
3孩子：d*i+3
...
d孩子：d*i+d
*/