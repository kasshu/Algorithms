/*Count Inversion problem:
*Count all the inversions in the given array.
*Definition of Inversion:
*In array A, if i < j and A[i] > A[j], A[i] and A[j] is an inversion.
*e.g.
*Given array of {2,3,8,6,1}.
*Inversions are: (2,1) (3,1) (8,1) (6,1) (8,6), we will count 5.
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

/*
*Solution:
*We will count inversions by modifying the merge sort.
*In merge sort, we will merge the sorted left sub-array and right sub-array.
*Inversion appears when element from left sub-array is larger than element in
*right sub-array. And inversions in left sub-array and right sub-array are counted
*by recursive calls.
*/
int count(int *array, size_t left, size_t middle, size_t right) {
	if (array == NULL || middle < left || right < middle || right < left) {
		return 0;
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
	int cnt = 0;
	size_t i = 0, j = 0, k = left;
	while (i < left_len && j < right_len) {
		if (left_temp[i] <= right_temp[j]) {
			array[k++] = left_temp[i++];
		} else {
			//if right_temp[j] is smaller than left_temp[i], then it is smaller
			//than all the elements in left_temp from i to left_len - 1. They 
			//are all inversion that we should count
			cnt += left_len - i;
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
	return cnt;
}

/*Merge sort, running time O(nlog(n))*/
int CountInversions(int *array, size_t left, size_t right) {
	if(array == NULL || left >= right) {
		return 0;
	}
	size_t middle = (left + right) / 2;
	int left_inversions = CountInversions(array, left, middle);
	int right_inversions = CountInversions(array, middle + 1, right);
	int between_inversions = count(array, left, middle, right);
	return left_inversions + right_inversions + between_inversions;
}

int main(int argc, char *argv[]) {
	{
		int array[] = {2,3,8,6,1};
		print_array(array, 5);
		printf("There are %d inversions in array\n", CountInversions(array, 0, 5));
	}
	{
		int array[] = {8,7,6,5,4,3,2,1};
		print_array(array, 8);
		printf("There are %d inversions in array\n", CountInversions(array, 0, 7));
	}
	{
		int array[] = {1,2,3,4,5,6,7,8};
		print_array(array, 8);
		printf("There are %d inversions in array\n", CountInversions(array, 0, 7));
	}
}
