/*Max length of path sum to k problem:
*Given a binary tree and a value k, find the max length of path that sum to k.
*Definition of path: 
*Begin at any node and stop at any node in the subtree rooted by the begin node.(The path is always going down the tree)
*e.g.
*Binary Tree:
*            -3
*           /   \
*         3      4
*       /  \    /  \
*     1     0  2    3
*          / \
*         1   6
*k = 6
*The max length is 4, the path is: {-3, 3, 0, 6}
*/

#include "stdio.h"
#include <queue>
#include <unordered_map>
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
*This is a mutation of MaxLengthOfSubarraySumToK problem. When you traverse to
*a leaf node, you get the whole array. This solution is the same, we use hashtable
*to remember sum(0...j) and the first occurrent level. If currentSum - k can be found
*in the hashtable(assume at level i), then j - i might be a answer, then we check
*whether j - i is longer than the max lengh. When we leave current level and go back,
*remove currentSum in hashtable if the first occurent level is current level. 
*Cost: Time-O(n), Space:O(h)
*/

void process(Node *root, unordered_map<int, int> &map, int level, int sum, int k, int *result) {
	if (root == NULL) {
		return;
	}
	//calc sum
	int currentSum = sum + root->val;
	//update map
	unordered_map<int, int>::iterator it = map.find(currentSum);
	if (it == map.end()) {
		map[currentSum] = level;
	} else if (it->second > level) {
		map[currentSum] = level;
	}
	//try to find a sum equal to k
	it = map.find(currentSum - k);
	if (it != map.end() && level - (it->second) > *result) {
		*result = level - (it->second);
	}
	process(root->left, map, level + 1, currentSum, k, result);
	process(root->right, map, level + 1, currentSum, k, result);
	//remove before quit
	it = map.find(currentSum);
	if (it->second == level) {
		map.erase(it);
	}
}

int GetMaxLengthOfPathSumToK(Node *root, int k) {
	if (root == NULL) {
		return -1;
	}
	unordered_map<int, int> sum_level_map;
	sum_level_map[0] = -1;//important to calc the full path from root to some node
	int result = -1;
	process(root, sum_level_map, 0, 0, k, &result);
	return result;
}

int main(int argc, char *argv[]) {
	Node *root = new Node(-3);
	root->left = new Node(3);
	root->left->left = new Node(1);
	root->left->right = new Node(0);
	root->left->right->left = new Node(1);
	root->left->right->right = new Node(6);
	root->right = new Node(4);
	root->right->left = new Node(2);
	root->right->right = new Node(3);
	printf("Tree:");
	PrintByLevel(root);
	int k = 6;
	printf("The max length of sum %d is %d\n", k, GetMaxLengthOfPathSumToK(root, k));
	k = 0;
	printf("The max length of sum %d is %d\n", k, GetMaxLengthOfPathSumToK(root, k));
	k = 10;
	printf("The max length of sum %d is %d\n", k, GetMaxLengthOfPathSumToK(root, k));
	release_tree(root);
}
