/*Reconstruct binary tree from pre-order and in-order sequence problem:
*Given two sequences of unique integer produced by pre-order and in-order traverse, reconstruct binary tree from it.
*e.g.
*in-order = {8, 4, 9, 2, 10, 5, 1, 6, 3, 7}
*pre-order = {1, 2, 4, 8, 9, 5, 10, 3, 6, 7}
*reconstruct bst below: 
*
*               1
*             /   \
*            2     3
*          /  \  /  \
*         4   5  6   7
*       /  \ /
*      8   9 10
*/

#include "stdio.h"
#include <queue>
using namespace std;

struct Node {
	Node (int value):left(NULL),right(NULL),val(value) {}
	Node *left;
	Node *right;
	int val;
};

void print_tree_inorder (Node *root) {
	if (root == NULL) {
		return;
	}
	print_tree_inorder(root->left);
	printf("%d ",root->val);
	print_tree_inorder(root->right);
}

void print_tree(Node *root) {
	print_tree_inorder(root);
	printf("\n");
}

void release_tree (Node *root) {
	if (root == NULL) {
		return;
	}
	release_tree(root->left);
	release_tree(root->right);
	delete root;
}

Node *build_tree(int *arr, int len) {
	if (arr == NULL || len == 0) {
		return NULL;
	}
	Node *root = new Node(arr[0]);
	for (int i = 1; i < len; i++) {
		Node *node = new Node(arr[i]);
		Node *cur = root;
		Node **insert = NULL;
		while (cur != NULL) {
			if (cur->val > node->val) {
				insert = &(cur->left);
				cur = cur->left;
			} else {
				insert = &(cur->right);
				cur = cur->right;
			}
		}
		*insert = node;
	}
	return root;
}

void PrintByLevel (Node *root) {
	if (root == NULL) {
		return;
	}
	queue<Node *> q;
	q.push(root);
	while (!q.empty()) {
		Node *temp = q.front();
		if (temp->left != NULL) {
			q.push(temp->left);
		}
		if (temp->right != NULL) {
			q.push(temp->right);
		}
		printf("%d ", temp->val);
		q.pop();
	}
	printf("\n");
}

/*
*Solution:
*The solution will be recursive:
*1.Make root from the first element of pre-sequence
*2.Find the root element in in-order sequence and split it into left part and right part
*3.Split the pre-order sequence into left and right part(They should have the same length)
*4.Recursive call on left/right part
*5.Link them
*Cost: Time-O(n*h), Space:O(h)
*/

Node * ReconstructFromPreOrderInOrder(int *pre_arr, int pre_begin, int pre_end, int *in_arr, int in_begin, int in_end) {
	if (pre_arr == NULL || pre_begin < 0 || pre_end < 0 || pre_begin > pre_end) {
		return NULL;
	}
	if (in_arr == NULL || in_begin < 0 || in_end < 0 || in_begin > in_end) {
		return NULL;
	}
	int root = pre_arr[pre_begin];
	int pos = in_begin;
	//find root in in-order and split
	for (int i = in_begin; i <= in_end; i++) {
		if (in_arr[i] == root) {
			pos = i;
			break;
		}
	}
	int left_len = pos - in_begin;
	int right_len = in_end - pos;
	Node *cur = new Node(root);
	cur->left = ReconstructFromPreOrderInOrder(pre_arr, pre_begin + 1, pre_begin + left_len, in_arr, in_begin, pos - 1);
	cur->right = ReconstructFromPreOrderInOrder(pre_arr, pre_end - right_len + 1, pre_end, in_arr, pos + 1, in_end);
	return cur;
}

int main(int argc, char *argv[]) {
	{
		int in_arr[] = {8, 4, 9, 2, 10, 5, 1, 6, 3, 7};
		int pre_arr[] = {1, 2, 4, 8, 9, 5, 10, 3, 6, 7};
		printf("In-Order Sequence:");
		for (size_t i = 0; i < sizeof(in_arr) / sizeof(int); i++) {
			printf("%d ", in_arr[i]);
		}
		printf("\n");
		printf("Pre-Order Sequence:");
		for (size_t i = 0; i < sizeof(pre_arr) / sizeof(int); i++) {
			printf("%d ", pre_arr[i]);
		}
		printf("\n");
		Node *root = ReconstructFromPreOrderInOrder(pre_arr, 0, sizeof(pre_arr) / sizeof(int) - 1, in_arr, 0, sizeof(in_arr) / sizeof(int) - 1);
		PrintByLevel(root);
		release_tree(root);
	}
	{
		int in_arr[] = {1, 2, 3, 4, 5, 6, 7};
		int pre_arr[] = {7, 6, 5, 4, 3, 2, 1};
		printf("In-Order Sequence:");
		for (size_t i = 0; i < sizeof(in_arr) / sizeof(int); i++) {
			printf("%d ", in_arr[i]);
		}
		printf("\n");
		printf("Pre-Order Sequence:");
		for (size_t i = 0; i < sizeof(pre_arr) / sizeof(int); i++) {
			printf("%d ", pre_arr[i]);
		}
		printf("\n");
		Node *root = ReconstructFromPreOrderInOrder(pre_arr, 0, sizeof(pre_arr) / sizeof(int) - 1, in_arr, 0, sizeof(in_arr) / sizeof(int) - 1);
		PrintByLevel(root);
		release_tree(root);
	}
	{
		int in_arr[] = {1, 2, 3, 4, 5, 6, 7};
		int pre_arr[] = {1, 2, 3, 4, 5, 6, 7};
		printf("In-Order Sequence:");
		for (size_t i = 0; i < sizeof(in_arr) / sizeof(int); i++) {
			printf("%d ", in_arr[i]);
		}
		printf("\n");
		printf("Pre-Order Sequence:");
		for (size_t i = 0; i < sizeof(pre_arr) / sizeof(int); i++) {
			printf("%d ", pre_arr[i]);
		}
		printf("\n");
		Node *root = ReconstructFromPreOrderInOrder(pre_arr, 0, sizeof(pre_arr) / sizeof(int) - 1, in_arr, 0, sizeof(in_arr) / sizeof(int) - 1);
		PrintByLevel(root);
		release_tree(root);
	}
	{
		int in_arr[] = {1};
		int pre_arr[] = {1};
		printf("In-Order Sequence:");
		for (size_t i = 0; i < sizeof(in_arr) / sizeof(int); i++) {
			printf("%d ", in_arr[i]);
		}
		printf("\n");
		printf("Pre-Order Sequence:");
		for (size_t i = 0; i < sizeof(pre_arr) / sizeof(int); i++) {
			printf("%d ", pre_arr[i]);
		}
		printf("\n");
		Node *root = ReconstructFromPreOrderInOrder(pre_arr, 0, sizeof(pre_arr) / sizeof(int) - 1, in_arr, 0, sizeof(in_arr) / sizeof(int) - 1);
		PrintByLevel(root);
		release_tree(root);
	}
}
