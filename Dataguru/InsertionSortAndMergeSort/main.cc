/*
*Implement insertion sort and merge sort
*/

#include "stdio.h"

void print_array(int *array, size_t len) {
	if (array == NULL || len == 0) {
		return;
	}
	printf("Array: ");
	for (size_t i = 0; i < len; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

/*Insertion sort, running time O(n^2)*/
void InsertionSort(int *array, size_t len) {
	if(array == NULL || len == 0 || len == 1) {
		return;
	}
	for (size_t i = 1; i < len; i++) {
		int key = array[i];
		size_t j = i - 1;
		while (j >= 0 && array[j] > key) {
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = key;
	}
}

void merge(int *array, size_t left, size_t middle, size_t right) {
	if (array == NULL || middle < left || right < middle || right < left) {
		return;
	}
	//copy left
	size_t left_len = middle - left + 1;
	int *left_temp = new int[left_len];
	for (size_t i = 0; i < left_len; i++) {
		left_temp[i] = array[i + left];
	}
	//copy right
	size_t right_len = right - middle;
	int *right_temp = new int[right_len];
	for (size_t i = 0; i < right_len; i++) {
		right_temp[i] = array[i + middle + 1];
	}
	//do merge
	size_t i = 0, j = 0, k = left;
	while (i < left_len && j < right_len) {
		if (left_temp[i] <= right_temp[j]) {
			array[k++] = left_temp[i++];
		} else {
			array[k++] = right_temp[j++];
		}
	}
	//copy remains
	while (i < left_len) {
		array[k++] = left_temp[i++];
	}
	while (j < right_len) {
		array[k++] = right_temp[j++];
	}
	delete [] left_temp;
	delete [] right_temp;
}

/*Merge sort, running time O(nlog(n))*/
void MergeSort(int *array, size_t left, size_t right) {
	if(array == NULL || left >= right) {
		return;
	}
	size_t middle = (left + right) / 2;
	MergeSort(array, left, middle);
	MergeSort(array, middle + 1, right);
	merge(array, left, middle, right);
}

int main(int argc, char *argv[]) {
	{
		int array[] = {4, 1, 5, 2, 8, 7, 3, 6};
		printf("Before insertion sort:\n");
		print_array(array, 8);
		InsertionSort(array, 8);
		printf("After insertion sort:\n");
		print_array(array, 8);
	}
	{
		int array[] = {4, 1, 5, 2, 8, 7, 3, 6};
		printf("Before merge sort:\n");
		print_array(array, 8);
		MergeSort(array, 0, 7);
		printf("After merge sort:\n");
		print_array(array, 8);
	}
}
