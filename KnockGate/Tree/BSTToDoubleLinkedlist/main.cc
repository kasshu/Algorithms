/*BST to double linked list problem:
*Given a BST, convert it to a sorted double linked list (left as prev, right as next)  
*e.g.
*             4
*           /   \
*         3      6      --->    1<->2<->3<->4<->5<->6<->7
*       /   \   /  \
*     1      2 5    7
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

void print_list (Node *head) {
	Node *cur = head;
	Node *tail = NULL;
	printf("Forward order: ");
	while (cur != NULL) {
		printf("%d->",cur->val);
		tail = cur;
		cur = cur->right;
	} 
	printf("null\n");
	printf("Inverse order: ");
	cur = tail;
	while (cur != NULL) {
		printf("%d->",cur->val);
		cur = cur->left;
	}
	printf("null\n");
}

void release_list (Node *head) {
	Node *cur = head;
	while (cur != NULL) {
		Node *p = cur->right;
		delete cur;
		cur = p;
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
*A recursive solution. For a node in tree:
*1.convert its left subtree into double linked list
*2.convert its right subtree into double linked list
*3.link them
*Cost: Time-O(n), Space:O(lg(n))
*e.g.
*     left-linked-list <-> cur-node <-> right-linked-list
*/

void bst_to_dlinked_recursive (Node *root, Node **phead, Node **ptail) {
	Node *left_head = NULL;
	Node *left_tail = NULL;
	Node *right_head = NULL;
	Node *right_tail = NULL;
	//convert left subtree
	if (root->left != NULL) {
		bst_to_dlinked_recursive(root->left, &left_head, &left_tail);
	}
	//convert right subtree
	if (root->right != NULL) {
		bst_to_dlinked_recursive(root->right, &right_head, &right_tail);
	}
	//link them
	if (left_tail != NULL) {
		left_tail->right = root;
		root->left = left_tail;
		*phead = left_head;
	} else {
		*phead = root;
		root->left = NULL;
	}
	if (right_head != NULL) {
		right_head->left = root;
		root->right = right_head;
		*ptail = right_tail;
	} else {
		*ptail = root;
		root->right = NULL;
	}
}

Node *bst_to_dlinked (Node *root) {
	if (root == NULL) {
		return NULL;
	}
	Node *head = NULL;
	Node *tail = NULL;
	bst_to_dlinked_recursive(root, &head, &tail);
	return head;
}

int main(int argc, char *argv[]) {
	{
	int a[] = {4,2,6,1,3,5,7};
	Node *root = build_tree(a, sizeof(a)/sizeof(int));
	print_tree(root);
	Node *head = bst_to_dlinked(root);
	print_list(head);
	release_list(head);
	}
	{
	int a[] = {1,2,3,4,5,6,7};
	Node *root = build_tree(a, sizeof(a)/sizeof(int));
	print_tree(root);
	Node *head = bst_to_dlinked(root);
	print_list(head);
	release_list(head);
	}
	{
	int a[] = {1};
	Node *root = build_tree(a, sizeof(a)/sizeof(int));
	print_tree(root);
	Node *head = bst_to_dlinked(root);
	print_list(head);
	release_list(head);
	}
}
