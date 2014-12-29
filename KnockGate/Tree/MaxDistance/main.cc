/*Max distance in bst problem:
*Definition: distance of 2 nodes in bst.
*Given 2 nodes in the same bst, the distance of these 2 nodes is number of
*nodes in the path from 1 node to another. The path should pass a node only
*once.
*Given a bst, find the max distance between nodes.
*e.g.
*             4           
*           /   \         the distance of 1 and 7 is 5, path is 12467
*         2      6        the distance of 1 and 6 is 4, path is 1246
*       /   \   /  \      the distance of 2 and 5 is 4, path is 2465
*     1      3 5    7  
*
*                max distance is 1 to 7, path is 12467
*
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
*At each node, the max distance comes from 3 ways:
*1.From its left subtree
*2.From its right subtree
*3.The path go through this node
*e.g.
*
*           1           At node 1, the max distance comes from its right subtree.
*            \
*            100        At node 100, the max distance comes from its left subtree.
*             /
*           50          At node 50, the path with max distance goes through it.
*          /  \
*        25    75       The max distance is between 27 and 77, path is 27,30,25,50,75,80,77 
*         \     \
*         30    80
*         /     /
*        27    77
*
*So, we modify post-order traverse:
*1.Get the max distance and max depth in left subtree
*2.Get the max distance and max depth in right subtree
*3.Compare max distance of left subtree, right subtree and
*  sum of max depth in left and right subtree to find the 
*  new max distance. 
*4.Return the new max distance and the max depth of current tree.
*Cost: Time-O(n), Space:O(lg(n))
*/

void FindMaxDistanceRecur (Node *root, int *max_depth, int *max_distance) {
	if (root == NULL) {
		*max_depth = 0;
		*max_distance = 0;
		return;
	}
	int left_depth = 0, right_depth = 0;
	int left_distance = 0, right_distance = 0;
	FindMaxDistanceRecur(root->left, &left_depth, &left_distance);
	FindMaxDistanceRecur(root->right, &right_depth, &right_distance);
	*max_depth = (left_depth > right_depth ? left_depth : right_depth) + 1;
	*max_distance = left_depth + right_depth + 1;
	if (left_distance > *max_distance) {
		*max_distance = left_distance;
	}
	if (right_distance > *max_distance) {
		*max_distance = right_distance;
	}
}

int FindMaxDistance (Node *root) {
	if (root == NULL) {
		return 0;
	}
	int max_depth = 0;
	int max_distance = 0;
	FindMaxDistanceRecur(root, &max_depth, &max_distance);
	return max_distance;
}

int main(int argc, char *argv[]) {
	{
	int a[] = {4,2,6,1,3,5,7};
	Node *root = build_tree(a, sizeof(a)/sizeof(int));
	print_tree(root);
	printf("The max distance in tree is %d\n", FindMaxDistance(root));
	print_tree(root);
	release_tree(root);
	}
	{
	int a[] = {4,2,1};
	Node *root = build_tree(a, sizeof(a)/sizeof(int));
	print_tree(root);
	printf("The max distance in tree is %d\n", FindMaxDistance(root));
	print_tree(root);
	release_tree(root);
	}
	{
	int a[] = {4};
	Node *root = build_tree(a, sizeof(a)/sizeof(int));
	print_tree(root);
	printf("The max distance in tree is %d\n", FindMaxDistance(root));
	print_tree(root);
	release_tree(root);
	}
	{
	int a[] = {1,100,50,25,75,30,80,27,77};
	Node *root = build_tree(a, sizeof(a)/sizeof(int));
	print_tree(root);
	printf("The max distance in tree is %d\n", FindMaxDistance(root));
	print_tree(root);
	release_tree(root);
	}
}

