/*Sorted array to minimum height BST problem:
*Given a sorted array, convert it into a BST with minimum height
*e.g.
*             3           
*           /   \         converted from 123456 
*         1      5        
*          \    /  \       \
*           2  4    6   
*
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

/*
*Solution:
*BST with minimum height is fully balanced BST. We can convert
*it as following:
*1.find the median of current array
*2.make it root
*3.recursive call left sub-array and right sub-array
*4.link them
*Cost: Time-O(n), Space:O(n)
*/

Node * BuildMinimumHeightBST (const int *array, size_t start, size_t end) {
	if (array == NULL || start > end) {
		return NULL;
	}
	size_t median = (start + end) / 2;
	Node *root = new Node(array[median]);
	if (start == end) {
		return root;
	}
	Node *left = NULL;
	if (median > start) {
		left = BuildMinimumHeightBST(array, start, median - 1);
	}
	Node *right = NULL;
	if (median < end) {
		right = BuildMinimumHeightBST(array, median + 1, end);
	}
	root->left = left;
	root->right = right;
	return root;
}

int main(int argc, char *argv[]) {
	{
	int a[] = {1,2,3,4,5,6};
	Node *root = BuildMinimumHeightBST(a, 0, 5);
	PrintByLevel(root);
	release_tree(root);
	}
	{
	int a[] = {1,2,3,4,5,6,7};
	Node *root = BuildMinimumHeightBST(a, 0, 6);
	PrintByLevel(root);
	release_tree(root);
	}
}

