/*Binary tree serialization problem:
*Serialize binary tree into string, unserialize string into a binary tree.
*/

#include "stdio.h"
#include <queue>
#include <string>
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
*Usually, we serialize a binary tree into in-order string and pre-order string,
*which space is 2*n. Why use 2 strings of different traverse order? Because it
*is hard to distinguish leaf node and branch node. Now, we will use '#' to stand
*for NULL in traverse:
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
*Serialized string of pre-order: 1,2,4,8,#,#,9,#,#,5,10,#,#,#,3,6,#,#,7,#,#, 
*How to unserialize the string into binary tree?
*We use recursive calls according to the traverse order we build the string.
*Cost: Time-O(n), Space:O(n)
*/

void TreeSerialize(Node *root, string &s) {
	if (root == NULL) {
		s += "#,";
		return;
	}
	s += to_string(root->val) + ",";
	TreeSerialize(root->left ,s);
	TreeSerialize(root->right ,s);
}

Node * TreeUnserializeRecursive(const string &s, size_t *pos) {
	size_t next = s.find(",", *pos);
	string sval = s.substr(*pos, next - *pos);
	if (sval.compare("#") == 0) {
		*pos = next + 1;
		return NULL;
	}
	Node *root = new Node(stoi(sval));
	*pos = next + 1;
	root->left = TreeUnserializeRecursive(s, pos);
	root->right = TreeUnserializeRecursive(s, pos);
	return root;
}

Node * TreeUnserialize(const string &s) {
	if (s.length() == 0) {
		return NULL;
	}
	size_t pos = 0;
	return TreeUnserializeRecursive(s, &pos);
}

int main(int argc, char *argv[]) {
	{
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
	string s = "";
	TreeSerialize(root, s);
	printf("Serialization string:%s\n", s.c_str());
	Node *uroot = TreeUnserialize(s);
	printf("Tree:");
	PrintByLevel(uroot);
	release_tree(root);
	release_tree(uroot);
	}
	{
	Node *root = new Node(1);
	root->left = new Node(2);
	root->left->left = new Node(4);
	printf("Tree:");
	PrintByLevel(root);
	string s = "";
	TreeSerialize(root, s);
	printf("Serialization string:%s\n", s.c_str());
	Node *uroot = TreeUnserialize(s);
	printf("Tree:");
	PrintByLevel(uroot);
	release_tree(root);
	release_tree(uroot);
	}
}
