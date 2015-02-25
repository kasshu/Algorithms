/*The lowest common ancestor problem:
*Given a binary tree and 2 nodes in it, find the lowest common ancestor of them.
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
*The lowest common ancestor of 9 and 10 is 2.
*The lowest common ancestor of 6 and 10 is 1.
*The lowest common ancestor of 4 and 6 is 1.
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
*Assume that we have found the lowest common ancestor of given nodes. We will see:
*1.One node is in left subtree and the other one in the right subtree.
*2.Two nodes are in the same subtree of nodes which is higher than the lowest common ancestor.
*3.You can only find one node in the subtree of nodes which is lower than the lowest common ancestor.
*The solution will be recursive: (Note: If one node is the other's ancestor, this algorithm won't work)
*1.If current node is one of the givne node, return it.
*2.If one node is found in one subtree, return it.
*3.If given nodes are found in left/right subtree, we find the LCA return current node.
*4.If given nodes are found in one subtree, return it. (The tricky point is we never distinguish case 2 and 4)
*Cost: Time-O(n), Space:O(h)
*/

bool ContainsNode(Node *root, Node *target) {
	if (root == NULL && target == NULL) {
		return true;
	} else if (root == NULL) {
		return false;
	} else if (target == NULL) {
		return true;
	}
	Node *cur = root;
	bool ret = false;
	while (cur != NULL) {
		if (cur->left != NULL) {
			Node *temp = cur->left;
			while (temp->right != NULL && temp->right != cur) {
				temp = temp->right;
			}
			if (temp->right == NULL) {
				temp->right = cur;
			} else {
				if (cur == target) {
					ret = true;
				}
				temp->right = NULL;
				cur = cur->right;
			}
		} else {
				if (cur == target) {
					ret = true;
				}
				cur = cur->right;
		}
	}
	return ret;
}

Node * GetLCARecursive(Node *root, Node *one, Node *two) {
	if (root == NULL) {
		return NULL;
	}
	if (root == one || root == two) {
		return root;
	}
	Node *left_ret = GetLCARecursive(root->left, one, two);
	Node *right_ret = GetLCARecursive(root->right, one, two);
	if (left_ret != NULL && right_ret != NULL) {
		return root;
	} else if (left_ret != NULL) {
		return left_ret;
	} else if (right_ret != NULL) {
		return right_ret;
	} else {
		return NULL;
	}
}

Node * GetLowestCommonAncestor(Node *root, Node * one, Node * two) {
	if (root == NULL) {
		return NULL;
	}
	if (one == NULL && two == NULL) {
		return NULL;
	} else if (one == NULL) {
		return two;
	} else if (two == NULL) {
		return one;
	}
	if (ContainsNode(one, two)) {
		return one;
	}
	if (ContainsNode(two, one)) {
		return two;
	}
	return GetLCARecursive(root, one, two);
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
	{
	Node *one = root->left->left->right;
	Node *two = root->left->right->left;
	Node *result = GetLowestCommonAncestor(root, one, two);
	printf("The lowest common ancestor of %d and %d is %d\n", one->val, two->val, result->val);
	}
	{
	Node *one = root->left->left->left;
	Node *two = root->left;
	Node *result = GetLowestCommonAncestor(root, one, two);
	printf("The lowest common ancestor of %d and %d is %d\n", one->val, two->val, result->val);
	}
	{
	Node *one = root->left;
	Node *two = root->left->right->left;
	Node *result = GetLowestCommonAncestor(root, one, two);
	printf("The lowest common ancestor of %d and %d is %d\n", one->val, two->val, result->val);
	}
	release_tree(root);
}
