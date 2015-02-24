/*Reconstruct bst from pre-order sequence problem:
*Given a sequence of unique integer produced by pre-order traverse, reconstruct the bst from it.
*e.g.
*array = {8, 6, 5, 7, 10, 9, 11}, reconstruct bst below: 
*               8
*             /   \
*            6    10
*          /  \  /  \
*         5   7  9   11
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
*For each node in BST, it is larger than all the nodes in its left subtree
*and smaller than all the nodes in its right subtree. In pre-order traverse,
*we traverse a BST like this:
*1.current node
*2.left subtree
*3.right subtree
*The sequence produced by post-order traverse will be:
*(current)(left-subtree)(right-subtree)
*Thus, the solution will be recursive:
*1.Make root from the first element of array
*2.Split the array into left part(less than root) and right part(larger than root)
*3.Recursive call on left/right part
*4.Link them
*Cost: Time-O(n*h), Space:O(h)
*/

Node * ReconstructFromPreOrder(int *arr, int begin, int end) {
	if (arr == NULL || begin < 0 || end < 0 || begin > end) {
		return NULL;
	}
	int current = arr[begin];
	int split = end + 1;
	//find split point
	for (int i = begin + 1; i <= end; i++) {
		if (arr[i] > current) {
			split = i;
			break;
		}
	}
	Node *cur = new Node(current);
	cur->left = ReconstructFromPreOrder(arr, begin + 1, split - 1);
	cur->right = ReconstructFromPreOrder(arr, split, end);
	return cur;
}

int main(int argc, char *argv[]) {
	{
		int arr[] = {8, 6, 5, 7, 10, 9, 11};
		printf("Sequence:");
		for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++) {
			printf("%d ", arr[i]);
		}
		printf("\n");
		Node *root = ReconstructFromPreOrder(arr, 0, sizeof(arr) / sizeof(int) - 1);
		PrintByLevel(root);
		release_tree(root);
	}
	{
		int arr[] = {1, 2, 3, 4, 5, 6, 7};
		printf("Sequence:");
		for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++) {
			printf("%d ", arr[i]);
		}
		printf("\n");
		Node *root = ReconstructFromPreOrder(arr, 0, sizeof(arr) / sizeof(int) - 1);
		PrintByLevel(root);
		release_tree(root);
	}
	{
		int arr[] = {7, 6, 5, 4, 3, 2, 1};
		printf("Sequence:");
		for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++) {
			printf("%d ", arr[i]);
		}
		printf("\n");
		Node *root = ReconstructFromPreOrder(arr, 0, sizeof(arr) / sizeof(int) - 1);
		PrintByLevel(root);
		release_tree(root);
	}
	{
		int arr[] = {8};
		printf("Sequence:");
		for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++) {
			printf("%d ", arr[i]);
		}
		printf("\n");
		Node *root = ReconstructFromPreOrder(arr, 0, sizeof(arr) / sizeof(int) - 1);
		PrintByLevel(root);
		release_tree(root);
	}
}
