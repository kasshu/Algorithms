/*Morris traverse problem:
*Given a bst, traverse it time cost O(n), space cost O(1)
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
*Solution: in-order
*The key method is: to find a way to lead us back
*when we reach the leaf node. And we will use the
*successor/predecessor relationship. In in-order
*the successor of current node is the most right
*node in the left subtree.
*e.g.
*              4           
*           /  |   \         1's right points back to it's successor 2
*         2    |    6        3's right points back to it's successor 4
*       / | \  |  / | \      5's right points back to it's successor 6
*      1--   3-  5--   7     7's right points to nothing because it is the last node in in-order
*
*1.If current node does not have left subtree, then
*  print current node and go to the right child of 
*  current node.
*2.If current node has left subtree, then link the
*  most right node in left subtree back.
*3.If the right most node in left subtree has already
*  been linked back, this means all the left subtree has
*  been visited, then print current node and point the right 
*  point back to NULL and go to the right child.
*Time cost: O(n), space cost:O(1)
*Proof:
*For each node, we must find its predecessor and link it back.
*Assume node at height h, it has to go down for h level to
*find the predecessor. For height h, there are n/2^h nodes. Thus,
*the running time will be big O of segma of n/2^h * h for h between 
*0 to log(n), and it is smaller than big O of segma of n/2^h * h
*for h between 0 and inifinte, which is O(n).
*Done!
*/

void MorrisInOrder (Node *root) {
	if (root == NULL) {
		return;
	}
	Node *cur = root;
	while (cur != NULL) {
		if (cur->left == NULL) {
			printf("%d ", cur->val);
			cur = cur->right;
		} else {
			Node *tmp = cur->left;
			while (tmp->right != NULL && tmp->right != cur) {
				tmp = tmp->right;
			}
			if (tmp->right == NULL) {
				tmp->right = cur;
				cur = cur->left;
			} else {
				tmp->right = NULL;
				printf("%d ", cur->val);
				cur = cur->right;
			}
		}
	}
	printf("\n");
}

/*
*Solution: pre-order
*We can use the method of in-order morris traverse.
*1.If current node does not have left subtree, then
*  print current node and go to the right child of 
*  current node.
*2.If current node has left subtree, then link the
*  most right node in left subtree back and print
*  current node.
*3.If the right most node in left subtree has already
*  been linked back, this means all the left subtree has
*  been visited, then point the right point back to NULL 
*  and go to the right child.
*Time cost: O(n), space cost:O(1)
*/

void MorrisPreOrder (Node *root) {
	if (root == NULL) {
		return;
	}
	Node *cur = root;
	while (cur != NULL) {
		if (cur->left == NULL) {
			printf("%d ", cur->val);
			cur = cur->right;
		} else {
			Node *tmp = cur->left;
			while (tmp->right != NULL && tmp->right != cur) {
				tmp = tmp->right;
			}
			if (tmp->right == NULL) {
				printf("%d ", cur->val);
				tmp->right = cur;
				cur = cur->left;
			} else {
				tmp->right = NULL;
				cur = cur->right;
			}
		}
	}
	printf("\n");
}

/*
*Solution: post-order
*We can not use the method of in-order morris traverse 
*directly. Because morris traverse connect left subtree
*to root, thus, we have to visit left subtree and root
*together. Yes, we can use part of morris traverse to
*get back to the root and follow the rules below:
*1.If a node has left subtree, link the predecessor back,
*  go to its left child.
*2.If a node does not have left subtree, go to its right
*  child.
*3.Every leaf node should have a link back, in order to
*  accomplish this, we will make a fake root, and put 
*  current tree to its left.
*4.When returned back to a node, print its left child all
*  the way right down reservely.
*Time cost: O(n), space cost:O(1)
*/

void reverse_print(Node *from, Node *to) {
	if (from == NULL || to == NULL) {
		printf("reverse_print: input wrong\n");
		return;
	}
	//reverse
	Node *newHead = from;
	Node *cur = from->right;
	from->right = to;
	while (cur != to) {
		Node *tmp = cur->right;
		cur->right = newHead;
		newHead = cur;
		cur = tmp;
	}
	//print
	cur = newHead;
	while (cur != to) {
		printf("%d ", cur->val);
		cur = cur->right;
	}
	//reverse back
	from = newHead;
	cur = from->right;
	from->right = to;
	while (cur != to) {
		Node *tmp = cur->right;
		cur->right = newHead;
		newHead = cur;
		cur = tmp;
	}
}

void MorrisPostOrder (Node *root) {
	if (root == NULL) {
		return;
	}
	Node *fake = new Node(0);
	fake->left = root;
	Node *cur = fake;
	while (cur != NULL) {
		if (cur->left == NULL) {
			cur = cur->right;
		} else {
			Node *tmp = cur->left;
			while (tmp->right != NULL && tmp->right != cur) {
				tmp = tmp->right;
			}
			if (tmp->right == NULL) {
				tmp->right = cur;
				cur = cur->left;
			} else {
				reverse_print(cur->left, tmp->right);
				tmp->right = NULL;
				cur = cur->right;
			}
		}
	}
	delete fake;
	printf("\n");
}

int main(int argc, char *argv[]) {
	{
	int a[] = {4,2,6,1,3,5,7};
	Node *root = build_tree(a, sizeof(a)/sizeof(int));
	MorrisInOrder(root);
	MorrisPreOrder(root);
	MorrisPostOrder(root);
	release_tree(root);
	}
	{
	int a[] = {4,2,1};
	Node *root = build_tree(a, sizeof(a)/sizeof(int));
	MorrisInOrder(root);
	MorrisPreOrder(root);
	MorrisPostOrder(root);
	release_tree(root);
	}
	{
	int a[] = {4};
	Node *root = build_tree(a, sizeof(a)/sizeof(int));
	MorrisInOrder(root);
	MorrisPreOrder(root);
	MorrisPostOrder(root);
	release_tree(root);
	}
}

