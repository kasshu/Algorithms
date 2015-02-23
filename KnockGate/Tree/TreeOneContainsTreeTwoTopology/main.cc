/*Tree one contains tree two topology problem:
*Given two binary trees, check out whether tree one contains tree two's topology.
*e.g.
*         Tree One                Tree Two
*             1                       2
*           /   \                   /   \
*         2      3                 4     5
*       /  \    /  \              /
*     4     5  6    7            8
*   /  \   /
*  8    9 10
*Tree one contains tree two's topology.                    
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
*1.Find all the nodes has the same value with root of tree two in tree one
*2.Traverse tree two and the sub-tree of tree one at the same time to check
*Cost: Time-O(n*m), Space:O(h)
*/

bool CheckTopology(Node *root1, Node *root2) {
	if (root2 == NULL) {
		return true;
	} else if (root1 == NULL) {
		return false;
	}
	if (!CheckTopology(root1->left, root2->left)) {
		return false;
	}
	if (!CheckTopology(root1->right, root2->right)) {
		return false;
	}
	if (root1->val != root2->val) {
		return false;
	} else {
		return true;
	}
}

bool ContainsTopology(Node *root1, Node *root2) {
	if (root2 == NULL) {
		return true;
	} else if (root1 == NULL) {
		return false;
	}
	if (root1->val == root2->val && CheckTopology(root1, root2)) {
		return true;
	} else {
		return ContainsTopology(root1->left, root2) || ContainsTopology(root1->right, root2);
	}
}

int main(int argc, char *argv[]) {
	Node *root1 = new Node(1);
	root1->left = new Node(2);
	root1->left->left = new Node(4);
	root1->left->left->left = new Node(8);
	root1->left->left->right = new Node(9);
	root1->left->right = new Node(5);
	root1->left->right->left = new Node(10);
	root1->right = new Node(3);
	root1->right->left = new Node(6);
	root1->right->right = new Node(7);
	printf("Tree 1:");
	PrintByLevel(root1);
	Node *root2 = new Node(2);
	root2->left = new Node(4);
	root2->left->left = new Node(8);
	root2->right = new Node(5);
	printf("Tree 2:");
	PrintByLevel(root2);
	printf("Does tree 1 contains tree 2 topology? %s\n", ContainsTopology(root1, root2) ? "Yes" : "No");
	Node *root3 = new Node(2);
	root3->left = new Node(4);
	root3->left->left = new Node(8);
	root3->right = new Node(5);
	root3->right->right = new Node(11);
	printf("Tree 3:");
	PrintByLevel(root3);
	printf("Does tree 1 contains tree 3 topology? %s\n", ContainsTopology(root1, root3) ? "Yes" : "No");
	Node *root4 = new Node(2);
	root4->left = new Node(2);
	root4->left->left = new Node(4);
	root4->left->left->left = new Node(8);
	root4->left->left->right = new Node(9);
	root4->left->right = new Node(5);
	root4->left->right->left = new Node(10);
	root4->right = new Node(2);
	root4->right->left = new Node(6);
	root4->right->right = new Node(7);
	printf("Tree 4:");
	PrintByLevel(root4);
	printf("Does tree 4 contains tree 2 topology? %s\n", ContainsTopology(root4, root2) ? "Yes" : "No");
	printf("Does tree 4 contains tree 3 topology? %s\n", ContainsTopology(root4, root3) ? "Yes" : "No");
	release_tree(root1);
	release_tree(root2);
	release_tree(root3);
	release_tree(root4);
}
