/*Largest BST subtree of binary tree problem:
*Given a binary tree, find the largest BST subtree in it.(return the root node)
*e.g.
*              Binary Tree:
*            _______6_______
*           /               \
*        __1__          ____12____
*       /     \        /          \
*      0       3    __10__        _13_
*                  /      \      /    \
*                 _4_    _14_   20    16
*                /   \  /    \
*               2    5 11    15
*
*        The largest BST subtee is:
*                   __10__       
*                  /      \
*                 _4_    _14_ 
*                /   \  /    \
*               2    5 11    15
*
*And you should return the node of 10.
*/

#include "stdio.h"
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <stack>
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
*We modify the post-order traverse.
*1.Recursive call on left subtree.
*2.Recursive call on right subtree.
*3.If not both left/right subtree are BST, return left/right result with max size.
*4.If both left/right subtree are BST, compare current val with max value
*  in left subtree and the min value in right subtree.
*4.1.If current is a BST, return current Node and the size.
*4.2.If current is not a BST, return left/right result with max size.
*Cost: Time-O(n), Space:O(h)
*/

Node *GetLargestBSTRecursive(Node *root, int *max, int *min, int *size) {
	if (root->left == NULL && root->right == NULL) { //leaf
		*max = root->val;
		*min = root->val;
		*size = 1;
		return root;
	}
	int left_min = 0;
	int left_max = 0;
	int left_size = 0;
	Node *left_max_node = NULL;
	int right_min = 0;
	int right_max = 0;
	int right_size = 0;
	Node *right_max_node = NULL;
	if (root->left != NULL) {
		left_max_node = GetLargestBSTRecursive(root->left, &left_max, &left_min, &left_size);
	}
	if (root->right != NULL) {
		right_max_node = GetLargestBSTRecursive(root->right, &right_max, &right_min, &right_size);
	}
	if (left_max_node != NULL && right_max_node == NULL) {
		if (left_max_node == root->left && root->val > left_max) {
			*min = left_min;
			*max = root->val;
			*size = left_size + 1;
			return root;
		} else {
			*size = left_size;
			return left_max_node;
		}
	} else if (left_max_node == NULL && right_max_node != NULL) {
		if (right_max_node == root->right && root->val < right_max) {
			*min = root->val;
			*max = right_max;
			*size = right_size + 1;
			return root;
		} else {
			*size = right_size;
			return right_max_node;
		}
	} else {
		if (left_max_node == root->left && 
			right_max_node == root->right &&
			root->val > left_max && root->val < right_min) {
			*min = left_min;
			*max = right_max;
			*size = left_size + right_size + 1;
			return root;
		} else {
			if (left_size >= right_size) {
				*size = left_size;
				return left_max_node;
			} else {
				*size = right_size;
				return right_max_node;
			}
		}
	}
}

Node *GetLargestBST(Node *root, int *size) {
	if (root == NULL) {
		return NULL;
	}
	int min = 0;
	int max = 0;
	return GetLargestBSTRecursive(root, &max, &min, size);
}

int main(int argc, char *argv[]) {
	Node *root = new Node(6);
	root->left = new Node(1);
	root->left->left = new Node(0);
	root->left->right = new Node(3);
	root->right = new Node(12);
	root->right->left = new Node(10);
	root->right->left->left = new Node(4);
	root->right->left->left->left = new Node(2);
	root->right->left->left->right = new Node(5);
	root->right->left->right = new Node(14);
	root->right->left->right->left = new Node(11);
	root->right->left->right->right = new Node(15);
	root->right->right = new Node(13);
	root->right->right->left = new Node(20);
	root->right->right->right = new Node(16);
	printf("Tree:");
	PrintByLevel(root);
	int size = -1;
	Node *max_node = GetLargestBST(root, &size);
	printf("The size of largest BST subtree is %d\n", size);
	print_tree(max_node);
	release_tree(root);
}
