/*Mirror BST problem:
*Given a BST, mirror it 
*e.g.
*             4                            4
*           /   \                        /   \
*         2      6        mirror->     6       2
*       /   \   /  \                 /   \   /   \
*     1      3 5    7               7     5 3     1
*/

#include "stdio.h"

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
*Modify post-order traverse:
*1.Mirror left subtree
*2.Mirror right subtree
*3.Link left mirror to right pointer and 
*link right mirror to left pointer
*Cost: Time-O(n), Space:O(lg(n))
*/

void MirrorBST (Node *root) {
	if (root == NULL) {
		return;
	}
	MirrorBST(root->left);
	MirrorBST(root->right);
	Node *temp = root->left;
	root->left = root->right;
	root->right = temp;
}

int main(int argc, char *argv[]) {
	{
	int a[] = {4,2,6,1,3,5,7};
	Node *root = build_tree(a, sizeof(a)/sizeof(int));
	print_tree(root);
	MirrorBST(root);
	print_tree(root);
	release_tree(root);
	}
	{
	int a[] = {4,2,1};
	Node *root = build_tree(a, sizeof(a)/sizeof(int));
	print_tree(root);
	MirrorBST(root);
	print_tree(root);
	release_tree(root);
	}
}

