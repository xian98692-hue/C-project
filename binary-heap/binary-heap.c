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
void delete_top(struct heap* heap) {//下沉
	int* arr = heap->array;
	int end = arr[heap->size - 1];
	arr[heap->size - 1] = 0;
	arr[0] = end;
	for (int i = 0; i < (heap->size - 3) / 2;) {
		int left = arr[2 * i + 1];
		int right = arr[2 * i + 2];
		if (end < left && end < right) {
			return;
		}
		if (left > right) {
			arr[(i - 1) / 2] = right;
			arr[2 * i + 2] = end;
			i = 2 * i + 2;
		}
		else if (left <= right) {
			arr[(i - 1) / 2] = left;
			arr[2 * i + 1] = end;
			i = 2 * i + 1;
		}
	}
	heap->size--;
	return;
}
void sink(struct heap* heap, int curr_idx) {//下沉
	if (curr_idx * 2 + 1 >= heap->size) {
		printf("the current idx's node is leave.no child.\n");
		return;
	}
	int* arr = heap->array;
	if (curr_idx * 2 + 2 >= heap->size && curr_idx * 2 + 1 < heap->size) {//单左叶子情形
		printf("the current idx's node only has left child.\n");
		if (arr[curr_idx * 2 + 1] < arr[curr_idx]) {
			int temp = arr[curr_idx * 2 + 1];
			arr[curr_idx * 2 + 1] = arr[curr_idx];
			arr[curr_idx] = temp;
			return;
		}
	}
	while (curr_idx != (heap->size - 1) && curr_idx != (heap->size - 2)) {
		if (arr[curr_idx * 2 + 1] < arr[curr_idx] && arr[curr_idx * 2 + 2] < arr[curr_idx]) {//双叶子均小于
			if (arr[curr_idx * 2 + 1] < arr[curr_idx * 2 + 2]) {
				int temp = arr[curr_idx * 2 + 1];
				arr[curr_idx * 2 + 1] = arr[curr_idx];
				arr[curr_idx] = temp;
				curr_idx = curr_idx * 2 + 1;
			}
			else {
				int temp = arr[curr_idx * 2 + 2];
				arr[curr_idx * 2 + 2] = arr[curr_idx];
				arr[curr_idx] = temp;
				curr_idx = curr_idx * 2 + 2;
			}
		}
		else if (arr[curr_idx * 2 + 1] < arr[curr_idx]) {//只有左叶子小于
			int temp = arr[curr_idx * 2 + 1];
			arr[curr_idx * 2 + 1] = arr[curr_idx];
			arr[curr_idx] = temp;
			curr_idx = curr_idx * 2 + 1;
		}
		else {//只有右叶子小于
			int temp = arr[curr_idx * 2 + 2];
			arr[curr_idx * 2 + 2] = arr[curr_idx];
			arr[curr_idx] = temp;
			curr_idx = curr_idx * 2 + 2;
		}
		if (arr[curr_idx * 2 + 1] >= arr[curr_idx] && arr[curr_idx * 2 + 2] >= arr[curr_idx]) {
			break;
		}
	}
	return;
}