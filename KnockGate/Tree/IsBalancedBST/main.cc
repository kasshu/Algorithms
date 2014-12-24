/*Is balanced BST problem:
*Given a BST, check it if it is a balanced BST
*Definition of balanced BST: For each node in BST, 
*the difference between the height of left substree 
*and height of right subtree is at most 1.
*e.g.      balanced         not balanced
*             4                   4
*           /   \               /   
*         2      6            2      
*       /   \   /           /   \
*     1      3 5          1      3
*/

#include "stdio.h"
#include <cstdlib>
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
*Modify post-order traverse of BST.
*1.Collect height of left subtree
*2.Collect height of right subtree
*3.If unbalanced return false, otherwise
*return max(left, right) + 1
*Cost: Time-O(n), Space:O(lg(n))
*/

bool is_balanced_bst (Node *root, int *height) {
	if (root == NULL) {
		*height = 0;
		return true;
	}
	int lheight = 0;
	bool lbalanced = is_balanced_bst(root->left, &lheight);
	int rheight = 0;
	bool rbalanced = is_balanced_bst(root->right, &rheight);
	*height = lheight > rheight ? lheight : rheight + 1;
	return lbalanced && rbalanced && abs(lheight - rheight) <= 1;
}

bool IsBalancedBST (Node *root) {
	int height = 0;
	return is_balanced_bst(root, &height);
}

int main(int argc, char *argv[]) {
	{
	int a[] = {4,2,6,1,3,5};
	Node *root = build_tree(a, sizeof(a)/sizeof(int));
	print_tree(root);
	bool balanced = IsBalancedBST(root);
	printf("Tree is %s\n",balanced ? "balanced" : "unbalanced");
	release_tree(root);
	}
	{
	int a[] = {4,2,1,3};
	Node *root = build_tree(a, sizeof(a)/sizeof(int));
	print_tree(root);
	bool balanced = IsBalancedBST(root);
	printf("Tree is %s\n",balanced ? "balanced" : "unbalanced");
	release_tree(root);
	}
}

