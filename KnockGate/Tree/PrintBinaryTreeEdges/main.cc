/*Print binary tree edges counter clockwise problem:
*Given a binary tree, print its edges.
*Rule 1:
*Root and leaves are edges, the most left and right
*nodes are edeges.
*Rule 2:
*Root and leaves are edges, the most left and right
*branches are edeges.
*e.g.
*      ______________1_______________
*     /                              \
*    2____                        ____3
*         \                      / 
*        __4__                __5__
*       /     \              /     \
*      6       7__         _8      _9_
*     /           \       /       /   \
*   10            11     12      13   14
*     \           /     /       /
*     15         16    17      18
*               /
*              19
*                \
*                20
*
*By rule 1, the edegs counter clockwise are:
*1 2 4 6 10 15 19 20 17 18 14 9 5  3
*
*By rule 2, the edegs counter clockwise are:
*1 2 4 6 10 15 20 17 18 14 9 5  3
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

Node *build_specific_tree() {
	Node *root = new Node(1);
	root->left = new Node(2);
	root->left->right = new Node(4);
	root->left->right->left = new Node(6);
	root->left->right->left->left = new Node(10);
	root->left->right->left->left->right = new Node(15);
	root->left->right->right = new Node(7);
	root->left->right->right->right = new Node(11);
	root->left->right->right->right->left = new Node(16);
	root->left->right->right->right->left->left = new Node(19);
	root->left->right->right->right->left->left->right = new Node(20);
	root->right = new Node(3);
	root->right->left = new Node(5);
	root->right->left->left = new Node(8);
	root->right->left->left->left = new Node(12);
	root->right->left->left->left->left = new Node(17);
	root->right->left->right = new Node(9);
	root->right->left->right->left = new Node(13);
	root->right->left->right->left->left = new Node(18);
	root->right->left->right->right = new Node(14);
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
*Solution: Rule 1
*We can solve this problem by print by level, but it will take
*O(n) space which is too much. Choose tree depth algorithm instead,
*make 2 vectors to remember the first depth x node and the last. Since
*the recursive traverse will traverse all nodes from left to right, the
*vectors contains left and right most nodes.
*1.Calc depth and fill left right vector
*2.Print left vector
*3.Print leaves not in left/right vector
*4.Print right reversely
*Cost: Time-O(n), Space:O(h)
*/

int GetMaxDepth(Node *root, int depth) {
	if (root == NULL) {
		return depth - 1;
	}
	int left = GetMaxDepth(root->left, depth + 1);
	int right = GetMaxDepth(root->right, depth + 1);
	return (left > right ? left : right);
}

void GetMostLeftRightNodeEachDepth(Node *root, int depth, vector<Node *> &lv, vector<Node *> &rv) {
	if (root == NULL) {
		return;
	}
	//remember first
	if (lv[depth] == NULL) {
		lv[depth] = root;
	}
	//update last
	rv[depth] = root;
	GetMostLeftRightNodeEachDepth(root->left, depth + 1, lv, rv);
	GetMostLeftRightNodeEachDepth(root->right, depth + 1, lv, rv);
}

void PrintLeavesNotEdge(Node *root, int depth, const vector<Node *> &lv, const vector<Node *> &rv) {
	if (root->left == NULL && root->right == NULL) {
		if (lv[depth] != root && rv[depth] != root) {
			printf("%d ", root->val);
		}
		return;
	}
	if (root->left != NULL) {
		PrintLeavesNotEdge(root->left, depth + 1, lv, rv);
	}
	if (root->right != NULL) {
		PrintLeavesNotEdge(root->right, depth + 1, lv, rv);
	}
}

void PrintEdgeRule1(Node *root) {
	//Get depth
	int depth = GetMaxDepth(root, 0);
	//Push the left most and right most node into vector
	vector<Node *> lv;
	lv.resize(depth + 1, NULL);
	vector<Node *> rv;
	rv.resize(depth + 1, NULL);
	GetMostLeftRightNodeEachDepth(root, 0, lv, rv);
	//Print the triangle
	//1.Print left most including root
	for (size_t i = 0; i < lv.size(); i++) {
		printf("%d ", lv[i]->val);
	}
	//2.Print leaves that are not in vector, the bottom line
	PrintLeavesNotEdge(root, 0, lv, rv);
	//3.Print right most reversely
	for (int i = static_cast<int>(rv.size()) - 1; i > 0; i--) {
		if (lv[i] != rv[i]) {
			printf("%d ", rv[i]->val);
		}
	}
	printf("\n");
}

/*
*Solution: Rule 2
*We can modify the algorithm of rule1.
*Make 2 vectors to remember the left and right edge. 
*1.Calc depth and fill left right vector
*2.Print left edge
*3.Print leaves not in left/right vector
*4.Print right edge reversely
*Cost: Time-O(n), Space:O(h)
*/

void GetLeftRightEdge(Node *root, vector<Node *> &lv, vector<Node *> &rv) {
	Node *walker = root;
	int depth = 0;
	while (true) {
		lv[depth] = walker;
		if (walker->left != NULL) {
			walker = walker->left;
			depth++;
		} else if (walker->right != NULL) {
			walker = walker->right;
			depth++;
		} else {
			break;
		}
	}
	walker = root;
	depth = 0;
	while (true) {
		rv[depth] = walker;
		if (walker->right != NULL) {
			walker = walker->right;
			depth++;
		} else if (walker->left != NULL) {
			walker = walker->left;
			depth++;
		} else {
			break;
		}
	}
}

void PrintEdgeRule2(Node *root) {
	//Get depth
	int depth = GetMaxDepth(root, 0);
	//Push the left most and right most node into vector
	vector<Node *> lv;
	lv.resize(depth + 1, NULL);
	vector<Node *> rv;
	rv.resize(depth + 1, NULL);
	GetLeftRightEdge(root, lv, rv);
	//Print the triangle
	//1.Print left most including root
	for (size_t i = 0; i < lv.size(); i++) {
		if (lv[i] != NULL) {
			printf("%d ", lv[i]->val);
		}
	}
	//2.Print leaves that are not in vector, the bottom line
	PrintLeavesNotEdge(root, 0, lv, rv);
	//3.Print right most reversely
	for (int i = static_cast<int>(rv.size()) - 1; i > 0; i--) {
		if (rv[i] != NULL && lv[i] != rv[i]) {
			printf("%d ", rv[i]->val);
		}
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	Node *root = build_specific_tree();
	PrintByLevel(root);
	PrintEdgeRule1(root);
	PrintEdgeRule2(root);
	release_tree(root);
}
