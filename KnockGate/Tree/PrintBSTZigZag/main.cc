/*Print bst zig zag problem:
*Given a bst, print it zig zag
*e.g.
*             4           
*           /   \          the result is: 4621357
*         2      6        
*       /   \   /  \       \
*     1      3 5    7  
*
*/

#include "stdio.h"
#include <queue>
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

/*
*Solution 1:
*We can modify print by level algorithm. Add a stack
*to reverse the odd level.
*Cost: Time-O(n), Space:O(n)
*/

void PrintZigZag (Node *root) {
	if (root == NULL) {
		return;
	}
	Node *delimiter = new Node(0);
	int level = 0;
	queue<Node *> q;
	stack<Node *> s;
	q.push(root);
	q.push(delimiter);
	while (q.size() != 1) {
		Node *temp = q.front();
		if (temp == delimiter) {
			q.push(delimiter);
			while (!s.empty()) {
				Node *stemp = s.top();
				printf("%d ", stemp->val);
				s.pop();
			}
			q.pop();
			level++;
			continue;
		}
		if (temp->left != NULL) {
			q.push(temp->left);
		}
		if (temp->right != NULL) {
			q.push(temp->right);
		}
		if (level % 2 == 0) {
			printf("%d ", temp->val);
		} else {
			s.push(temp);
		}
		q.pop();
	}
	printf("\n");
}

/*
*Solution 2:
*We can learn from print by level algorithm. Set 2 stacks,
*even stack remember nodes in even level, odd stack remember
*nodes in odd level. When the next node comes from even stack,
*the childrens are pushed from left to right. When the next
*node comes from odd stack, the childrens are pushed from right
*to left.
*Cost: Time-O(n), Space:O(n)
*/

void PrintZigZag2 (Node *root) {
	if (root == NULL) {
		return;
	}
	stack<Node *> odd_stack;
	stack<Node *> even_stack;
	even_stack.push(root);
	while (!odd_stack.empty() || !even_stack.empty()) {
		if (!even_stack.empty()) {
			while (!even_stack.empty()) {
				Node *temp = even_stack.top();
				printf("%d ", temp->val);
				if (temp->left != NULL) {
					odd_stack.push(temp->left);
				}
				if (temp->right != NULL) {
					odd_stack.push(temp->right);
				}
				even_stack.pop();
			}
			continue;
		}
		if (!odd_stack.empty()) {
			while (!odd_stack.empty()) {
				Node *temp = odd_stack.top();
				printf("%d ", temp->val);
				if (temp->right != NULL) {
					even_stack.push(temp->right);
				}
				if (temp->left != NULL) {
					even_stack.push(temp->left);
				}
				odd_stack.pop();
			}
		}
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	{
	int a[] = {4,2,6,1,3,5,7};
	Node *root = build_tree(a, sizeof(a)/sizeof(int));
	print_tree(root);
	PrintZigZag(root);
	PrintZigZag2(root);
	release_tree(root);
	}
	{
	int a[] = {4,2,1};
	Node *root = build_tree(a, sizeof(a)/sizeof(int));
	print_tree(root);
	PrintZigZag(root);
	PrintZigZag2(root);
	release_tree(root);
	}
	{
	int a[] = {4};
	Node *root = build_tree(a, sizeof(a)/sizeof(int));
	print_tree(root);
	PrintZigZag(root);
	PrintZigZag2(root);
	release_tree(root);
	}
}

