#ifndef SORT_H
#define SORT_H
void insertion_sort(int* num, int size);
void bubble_sort(int* num, int size);
void insert_sort(int* num, int size);
void selection_sort(int* num, int size);
void merge(int* arr, int* temp, int left, int mid, int right);
void merge_sort_1(int* arr, int* temp, int left, int right);
void merge_sort(int* num, int size);
void merge_sort_iteration(int* num, int size);
#endif 
