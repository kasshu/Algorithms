/*Post order sequence problem:
*Given an array(sequence) of integer, check out whether this sequence is produced by a pos-order traverse of a bst.
*e.g.
*array = {5, 7, 6, 9, 11, 10, 8}, this sequence is produced by the post-order traverse of bst:
*               8
*             /   \
*            6    10
*          /  \  /  \
*         5   7  9   11
*/

#include "stdio.h"

/*
*Solution:
*For each node in BST, it is larger than all the nodes in its left subtree
*and smaller than all the nodes in its right subtree. In post-order traverse,
*we traverse a BST like this:
*1.left subtree
*2.right subtree
*3.current node
*The sequence produced by post-order traverse will be:
*(left-subtree)(right-subtree)(current)
*for every node in BST. As you can see, the solution will be recursive:
*1.Get the last val in sequence as current node
*2.Split the sequence before last val into left-subsequence and right subsequence
*3.Recursive call on left and right
*If the sequence can be split this way until the end, this sequence is produced by
*post-order traverse.
*e.g.
*array = {5, 7, 6, 9, 11, 10, 8}
*current is 8, left is {5, 7, 6} and right is {9, 11, 10}
*current is 6, left is {5} and right is {7}
*current is 10, left is {9} and right is {11}
*return true
*Cost: Time-O(n*h), Space:O(h)
*/

bool IsPostOrderSequence(int *arr, int begin, int end) {
	if (arr == NULL || begin >= end) {
		return true;
	}
	int current = arr[end];
	int split = end - 1;
	//find split point
	for (int i = begin; i < end; i++) {
		if (arr[i] > current) {
			split = i - 1;
			break;
		}
	}
	//check split point
	for (int i = split + 1; i < end; i++) {
		if (arr[i] < current) {
			return false;
		}
	}
	return IsPostOrderSequence(arr,begin, split) && IsPostOrderSequence(arr, split + 1, end - 1);
}

int main(int argc, char *argv[]) {
	{
		int arr[] = {5, 7, 6, 9, 11, 10, 8};
		printf("Sequence:");
		for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++) {
			printf("%d ", arr[i]);
		}
		printf("\n");
		printf("Sequence is produceed by post-order traverse? %s\n", IsPostOrderSequence(arr, 0, sizeof(arr) / sizeof(int) - 1) ? "Yes" : "No");
	}
	{
		int arr[] = {1, 2, 3, 4, 5, 6, 7};
		printf("Sequence:");
		for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++) {
			printf("%d ", arr[i]);
		}
		printf("\n");
		printf("Sequence is produceed by post-order traverse? %s\n", IsPostOrderSequence(arr, 0, sizeof(arr) / sizeof(int) - 1) ? "Yes" : "No");
	}
	{
		int arr[] = {7, 6, 5, 4, 3, 2, 1};
		printf("Sequence:");
		for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++) {
			printf("%d ", arr[i]);
		}
		printf("\n");
		printf("Sequence is produceed by post-order traverse? %s\n", IsPostOrderSequence(arr, 0, sizeof(arr) / sizeof(int) - 1) ? "Yes" : "No");
	}
	{
		int arr[] = {4, 2, 1, 3, 6, 5, 7};
		printf("Sequence:");
		for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++) {
			printf("%d ", arr[i]);
		}
		printf("\n");
		printf("Sequence is produceed by post-order traverse? %s\n", IsPostOrderSequence(arr, 0, sizeof(arr) / sizeof(int) - 1) ? "Yes" : "No");
	}
}
