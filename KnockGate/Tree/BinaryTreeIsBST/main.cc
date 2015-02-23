/*Tree two is subtree of tree one problem:
*Given a binary tree, check out whether it is a BST.
*1.Time cost: O(n), Space cost: O(n)
*2.Time cost: O(n), Space cost: O(h)
*3.Time cost: O(n), Space cost: O(1)
*e.g.
*        Binary Tree is not a BST
*             1
*           /   \
*         2      3
*       /  \    /  \
*     4     5  6    7
*   /  \   /
*  8    9 10
*
*        Binary Tree is a BST
*             4
*           /   \
*         2      6
*       /   \  /   \
*      1    3  5    7
*/

#include "stdio.h"
#include <queue>
#include <vector>
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
*Solution 1:
*We can in-order traverse binary tree, and store every value in a vector.
*After traverse, we check if the vector is in ascending order.
*Cost: Time-O(n), Space:O(n)
*/

void InOrder(Node *root, vector<int> &v) {
	if (root == NULL) {
		return;
	}
	InOrder(root->left, v);
	v.push_back(root->val);
	InOrder(root->right, v);
}

bool IsBST1(Node *root) {
	if (root == NULL) {
		return true;
	}
	vector<int> v;
	InOrder(root, v);
	bool result = true;
	for (size_t i = 1; i < v.size(); i++) {
		if (v[i - 1] > v[i]) {
			result = false;
			break;
		}	
	}
	return result;
}

/*
*Solution 2:
*We can modify in-order traverse to store the previous node, and check 
*whether curent is larger than previous.
*Cost: Time-O(n), Space:O(h)
*/

bool InOrderPrevious(Node *root, Node **previous) {
	if (root->left != NULL && !InOrderPrevious(root->left, previous)) {
		return false;
	}
	if (*previous != NULL && root->val < (*previous)->val) {
		return false;
	}
	*previous = root;
	if (root->right != NULL && !InOrderPrevious(root->right, previous)) {
		return false;
	}
	return true;
}

bool IsBST2(Node *root) {
	if (root == NULL) {
		return true;
	}
	Node *previous = NULL;
	bool result = InOrderPrevious(root, &previous);
	return result;
}

/*
*Solution 3:
*We can modify morris in-order traverse to store the previous node, and check 
*whether curent is larger than previous.
*Cost: Time-O(n), Space:O(1)
*/

//Note that: you can not return during morris traverse, because the pointers are modified
bool IsBST3(Node *root) {
	bool ret = true;
	Node *cur = root;
	Node *pre = NULL;
	while (cur != NULL) {
		if (cur->left != NULL) {
			Node *temp = cur->left;
			while (temp->right != NULL && temp->right != cur) {
				temp = temp->right;
			}
			if (temp->right == NULL) {
				temp->right = cur;
				cur = cur->left;
			} else {
				temp->right = NULL;
				if (pre != NULL && pre->val > cur->val) {
					ret = false;
				}
				pre = cur;
				cur = cur->right;
			}
		} else {
			if (pre != NULL && pre->val > cur->val) {
				ret = false;
			}
			pre = cur;
			cur = cur->right;
		}
	}
	return ret;
}

int main(int argc, char *argv[]) {
	Node *root1 = new Node(1);
	root1->left = new Node(2);
	root1->left->left = new Node(4);
	root1->left->left->left = new Node(8);
	root1->left->left->right = new Node(9);
	root1->left->right = new Node(5);
	root1->left->right->left = new Node(10);
	root1->right = new Node(3);
	root1->right->left = new Node(6);
	root1->right->right = new Node(7);
	printf("Tree 1:");
	PrintByLevel(root1);
	printf("By method 1, tree 1 is a BST? %s\n", IsBST1(root1) ? "Yes" : "No");
	printf("By method 2, tree 1 is a BST? %s\n", IsBST2(root1) ? "Yes" : "No");
	printf("By method 3, tree 1 is a BST? %s\n", IsBST3(root1) ? "Yes" : "No");
	Node *root2 = new Node(4);
	root2->left = new Node(2);
	root2->left->left = new Node(1);
	root2->left->right = new Node(3);
	root2->right = new Node(6);
	root2->right->left = new Node(5);
	root2->right->right = new Node(7);
	printf("Tree 2:");
	PrintByLevel(root2);
	printf("By method 1, tree 1 is a BST? %s\n", IsBST1(root2) ? "Yes" : "No");
	printf("By method 2, tree 1 is a BST? %s\n", IsBST2(root2) ? "Yes" : "No");
	printf("By method 3, tree 1 is a BST? %s\n", IsBST3(root2) ? "Yes" : "No");
	release_tree(root1);
	release_tree(root2);
}
