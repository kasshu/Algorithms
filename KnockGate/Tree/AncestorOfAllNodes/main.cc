/*Ancestor of all nodes problem:
*Given a node in binary tree, and a list of nodes. Check whether the 
*given node is the ancestor of all the nodes in list.
*e.g.
*        Binary Tree
*             1
*           /   \
*         2      3
*       /  \    /  \
*     4     5  6    7
*   /  \   /
*  8    9 10
*
*Given node 2, list {4,8,9,10}, the answer is Yes.
*Given node 2, list {4,8,9,3}, the answer is No.
*/

#include "stdio.h"
#include <queue>
#include <vector>
#include <set>
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
*We can store all the nodes in list into a hashset, and traverse the subtree rooted at given node and check.
*If we find one node in the hashset, remove it. After the traverse, check the size of hashset, if it is 0,
*then return true, else return false.
*Cost: Time-O(n), Space:O(h)
*/

void PreOrder(Node *root, set<Node *> &s) {
	if (root == NULL) {
		return;
	}
	set<Node *>::iterator it = s.find(root);
	if (it != s.end()) {
		s.erase(it);
	}
	PreOrder(root->left, s);
	PreOrder(root->right, s);
}

bool IsAncestorOf(Node *root, const vector<Node *> &v) {
	if (root == NULL) {
		return false;
	}
	if (v.size() == 0) {
		return true;
	}
	set<Node *> s;
	for (size_t i = 0; i < v.size(); i++) {
		if (v[i] != NULL) {
			s.insert(v[i]);
		}
	}
	if (s.size() == 0) {
		return true;
	}
	PreOrder(root, s);
	return s.size() == 0;
}

int main(int argc, char *argv[]) {
	Node *root = new Node(1);
	root->left = new Node(2);
	root->left->left = new Node(4);
	root->left->left->left = new Node(8);
	root->left->left->right = new Node(9);
	root->left->right = new Node(5);
	root->left->right->left = new Node(10);
	root->right = new Node(3);
	root->right->left = new Node(6);
	root->right->right = new Node(7);
	printf("Tree:");
	PrintByLevel(root);
	Node *ancestor = root->left;
	vector<Node *> v;
	v.push_back(root->left->left);
	v.push_back(root->left->left->left);
	v.push_back(root->left->left->right);
	v.push_back(root->left->right->left);
	printf("List 1:\n");
	for (size_t i = 0; i < v.size(); i++) {
		printf("%d ", v[i]->val);
	}
	printf("\n");
	printf("Is node %d the ancestor of list 1? %s\n", ancestor->val, IsAncestorOf(ancestor, v) ? "Yes" : "No");
	v.clear();
	v.push_back(root->left->left);
	v.push_back(root->left->left->left);
	v.push_back(root->left->left->right);
	v.push_back(root->right);
	printf("List 2:\n");
	for (size_t i = 0; i < v.size(); i++) {
		printf("%d ", v[i]->val);
	}
	printf("\n");
	printf("Is node %d the ancestor of list 2? %s\n", ancestor->val, IsAncestorOf(ancestor, v) ? "Yes" : "No");
	release_tree(root);
}
