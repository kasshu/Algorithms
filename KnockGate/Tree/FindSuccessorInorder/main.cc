/*Find successor in-order problem:
*Given a BST with parent pointer, find the successor of in-order traverse of a specific node
*e.g.
*             4          
*           /   \        The successor of 3 is 4
*         2      6       The successor of 2 is 3
*       /   \   /  \     The successor of 4 is 5
*     1      3 5    7    
*/

#include "stdio.h"

struct Node {
	Node (int value):left(NULL),right(NULL),parent(NULL),val(value) {}
	Node *left;
	Node *right;
	Node *parent;
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

void print_parents(Node *root) {
	if (root == NULL) {
		return;
	}
	print_parents(root->left);
	print_parents(root->right);
	if (root->parent != NULL) {
		printf("%d parent is %d\n", root->val, root->parent->val);
	} else {
		printf("%d is root\n", root->val);
	}
}

void release_tree (Node *root) {
	if (root == NULL) {
		return;
	}
	release_tree(root->left);
	release_tree(root->right);
	delete root;
}

Node * find_in_bst(Node *root, int val) {
	while (root != NULL) {
		if (root->val > val) {
			root = root->left;
		} else if (root->val < val) {
			root = root->right;
		} else {
			return root;
		}
	}
	return root;
}

Node *build_tree(int *arr, int len) {
	if (arr == NULL || len == 0) {
		return NULL;
	}
	Node *root = new Node(arr[0]);
	for (int i = 1; i < len; i++) {
		Node *node = new Node(arr[i]);
		Node *parent = root;
		Node *cur = root;
		Node **insert = NULL;
		while (cur != NULL) {
			if (cur->val > node->val) {
				insert = &(cur->left);
				parent = cur;
				cur = cur->left;
			} else {
				insert = &(cur->right);
				parent = cur;
				cur = cur->right;
			}
		}
		*insert = node;
		node->parent = parent;
	}
	return root;
}

/*
*Solution:
*The successor of current node in in-order traverse:
*1.If current node has right child, the successor is 
*the most left child in the right subtree.
*e.g.
*             cur
*                \
*                /
*               /
*             suc
*
*2.If current node does not have right child, current
*node is the most right child in its successor's left
*subtree, we go up and find the successor.
*e.g.
*             suc
*            /
*            \
*             \
*             cur
*
*Cost: Time-O(lgn), Space:O(1)
*/

Node * SuccessorOf (Node *node) {
	if (node == NULL) {
		return NULL;
	}
	Node *ret = NULL;
	if (node->right != NULL) {
		ret = node->right;
		while (ret->left != NULL) {
			ret = ret->left;
		}
	} else {
		ret = node->parent;
		Node *pre = node;
		while (ret != NULL && pre == ret->right) {
			pre = ret;
			ret = ret->parent;
		}
	}
	return ret;
}

int main(int argc, char *argv[]) {
	{
	int a[] = {4,2,6,1,3,5,7};
	Node *root = build_tree(a, sizeof(a)/sizeof(int));
	print_tree(root);
	print_parents(root);
	int val = 4;
	Node *node = find_in_bst(root, val);
	Node *successor = SuccessorOf(node);
	printf("Successor of %d is %d\n", val, successor->val);
	val = 3;
	node = find_in_bst(root, val);
	successor = SuccessorOf(node);
	printf("Successor of %d is %d\n", val, successor->val);
	val = 7;
	node = find_in_bst(root, val);
	successor = SuccessorOf(node);
	printf("Successor of %d is %d\n", val, successor == NULL ? -1 : successor->val);
	release_tree(root);
	}
	{
	int a[] = {4};
	Node *root = build_tree(a, sizeof(a)/sizeof(int));
	print_tree(root);
	print_parents(root);
	int val = 4;
	Node *node = find_in_bst(root, val);
	Node *successor = SuccessorOf(node);
	printf("Successor of %d is %d\n", val, successor == NULL ? -1 : successor->val);
	release_tree(root);
	}
	{
	int a[] = {4, 2, 1};
	Node *root = build_tree(a, sizeof(a)/sizeof(int));
	print_tree(root);
	print_parents(root);
	int val = 4;
	Node *node = find_in_bst(root, val);
	Node *successor = SuccessorOf(node);
	printf("Successor of %d is %d\n", val, successor == NULL ? -1 : successor->val);
	release_tree(root);
	}
}
