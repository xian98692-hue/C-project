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