#include<stdio.h>
#include<windows.h>
#include<stdlib.h>

/*
不相交集：一个数组存储相应位置的元素指向的根节点。\n
*/
typedef struct k{
	struct k* parent;
	int value;
} node;

node** initialize(unsigned size) {
	node** array = malloc(sizeof(node*) * size);
	if (!array) {
		printf("分配数组内存失败。\n");
		return NULL;
	}

	for (int i = 0;i < size;i++) {
		array[i] = malloc(sizeof(node));

		if (!array[i]) {
			printf("第%d个数组分配空间失败\n", i);
			for (int j = 0;j < i;j++) {
				free(array[j]);
			}
			free(array);
			return NULL;
		}

		array[i]->parent = NULL;
		array[i]->value = i;
	}

	return array;
}

void set_union(node** arr,unsigned a,unsigned b,unsigned size) {
	if (a >= size || b >= size) {
		printf("数组越界访问\n");
		return;
	}
	/*建立关系：把下标对应的节点联系起来，后一个节点的父指针指向前一个节点\n*/
	if (arr[b]->parent == arr[a]||arr[a]->parent==arr[b]) {
		printf("这对节点 %u~%u 已经有联系  ", a, b);
		return;
	}

	arr[b]->parent = arr[a];
	
}

void print_array(node** arr,unsigned size) {
	for (unsigned index = 0;index < size;index++) {
		printf("下标%u的节点指向的下标是：%d\n",index,(arr[index]->parent==NULL)?-1:arr[index]->parent->value);
	}
}

unsigned find(node** arr, unsigned target, unsigned size) {
	/*根据给定的目标下标值，寻找它的最终父节点的下标\n*/
	unsigned temp = target;

	while (arr[target]->parent) {
		target = arr[target]->parent->value;
	}
	printf("寻找目标 %d 位置指向的最终位置下标：%d\n",temp, target);
	return target;
}
int main(void) {
	SetConsoleOutputCP(CP_UTF8);

	unsigned size = 10;
	node** arr = initialize(size);
	set_union(arr, 5, 4, size);
	set_union(arr, 4, 9, size);
	set_union(arr, 4, 1, size);
	set_union(arr, 9, 6, size);
	set_union(arr, 1, 4,size);
	find(arr, 1, size);
	print_array(arr, size);
	return 0;
}