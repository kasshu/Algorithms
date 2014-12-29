/*Print bst by level problem:
*Given a bst, print it by level
*e.g.
*             4           
*           /   \          the result is: 4261357
*         2      6        
*       /   \   /  \       \
*     1      3 5    7  
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
*The print by level is the BFS(Breadth First Search) of BST.
*We use a queue to implement the BFS in BST.
*Cost: Time-O(n), Space:O(n)
*/

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

int main(int argc, char *argv[]) {
	{
	int a[] = {4,2,6,1,3,5,7};
	Node *root = build_tree(a, sizeof(a)/sizeof(int));
	print_tree(root);
	PrintByLevel(root);
	release_tree(root);
	}
	{
	int a[] = {4,2,1};
	Node *root = build_tree(a, sizeof(a)/sizeof(int));
	print_tree(root);
	PrintByLevel(root);
	release_tree(root);
	}
	{
	int a[] = {4};
	Node *root = build_tree(a, sizeof(a)/sizeof(int));
	print_tree(root);
	PrintByLevel(root);
	release_tree(root);
	}
}

