#include<stdlib.h>
void bubble_sort(int* num, int size) {
	if (size <= 0) {
		return;
	}
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (num[i] > num[j]) {
				int temp = num[i];
				num[i] = num[j];
				num[j] = temp;
			}
		}
	}
}
void insertion_sort(int* num, int size) {
	for (int idx = 1; idx < size; idx++) {
		for (int j = idx - 1; j >= 0; j--) {

			if (num[j] <= num[j + 1]) {
				break;
			}
			else if (num[j] > num[j + 1]) {
				int temp = num[j + 1];
				num[j + 1] = num[j];
				num[j] = temp;
			}

		}
	}
}
void insert_sort(int* num, int size) {
	for (int i = 1; i < size; i++) {
		int key = num[i];
		int j = i - 1;

		while (j >= 0 && num[j] > key) {
			num[j + 1] = num[j];
			j--;
		}
		num[j + 1] = key;
	}
}
void shell_sort(int* num, int size) {
	int gap = size / 2;
	while (gap > 0) {
		for (int i = gap; i < size; i++) {
			int key = num[i];
			int j = i - gap;
			while (j >= 0 && num[j] > key) {
				num[j + gap] = num[j];
				j -= gap;
			}
			num[j + gap] = key;
		}
		gap /= 2;
	}
}
void selection_sort(int* num, int size) {
	for (int i = 0; i < size; i++) {
		int curr = num[i];
		int cnt = i;
		for (int j = i + 1; j < size; j++) {
			if (num[j] < num[cnt]) {
				cnt = j;
			}
		}
		num[i] = num[cnt];
		num[cnt] = curr;
	}
}
void merge(int* arr, int* temp, int left, int mid, int right) {
	//把数组划分成[left,...,mid]和[mid+1,...,right]2部分，合并成一个有序数组
	int i = left;
	int j = mid + 1;
	int k = left;

	while (i <= mid && j <= right) {
		if (arr[i] >= arr[j]) {
			temp[k++] = arr[j++];
		}
		else {
			temp[k++] = arr[i++];
		}
	}
	while (i <= mid) {
		temp[k++] = arr[i++];
	}
	while (j <= right) {
		temp[k++] = arr[j++];
	}
	for (int cnt = left; cnt <= right; cnt++) {
		arr[cnt] = temp[cnt];
	}
}

void merge_sort_1(int* arr, int* temp, int left, int right) {
	if (left >= right)return;
	int mid = (right - left) / 2+left;

	merge_sort_1(arr, temp, left, mid);
	merge_sort_1(arr, temp, mid + 1, right);
	merge(arr, temp, left, mid, right);
}

void merge_sort(int* num, int size) {
	int* temp = malloc(sizeof(int) * size);
	if (!temp)return;
	merge_sort_1(num, temp, 0, size - 1);

	free(temp);
}
void merge_sort_iteration(int* num, int size) {
	int* temp = malloc(sizeof(int) * size);
	if (!temp)return;
	
	for (int gap = 1; gap < size; gap *= 2) {
		for (int left = 0; left < size; left += 2 * gap) {
			int mid = left + gap - 1;
			int right = mid + gap;

			if (mid >= size)break;//说明左半段大于尺寸，直接停止
			if (right >= size) {//说明右半段需要截断
				right =size-1;
			}

			merge(num, temp, left, mid, right);
		}
	}

	free(temp);
}