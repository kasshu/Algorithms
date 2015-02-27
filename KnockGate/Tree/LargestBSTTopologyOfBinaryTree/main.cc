/*Largest BST topology of binary tree problem:
*Given a binary tree, find the largest BST topology in it.(return the max size)
*e.g.
*              Binary Tree:
*            _______6_______
*           /               \
*        __1__          ____12____
*       /     \        /          \
*      0       3    __10__        _13_
*                  /      \      /    \
*                 _4_    _14_   20    16
*                /   \  /    \
*               2    5 11    15
*
*        The largest BST topology is:
*            _______6_______
*           /               \
*        __1__          ____12____
*       /     \        /          \
*      0       3      10          13_
*                                    \
*                                    16
*
*And you should return 8.
*/

#include "stdio.h"
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <stack>
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
*Solution 1:
*We can check each node that: if we use this node as root, the size of largest BST.
*How to calc the size of largest BST rooted at given node?
*For each node below given node:
*1.If current->val is not in the give range, return 0.
*2.If current->val is in the give range:
*2.1.Check left subtree with lower bound and current->val.
*2.2.Check right subtree with current->val and higher bound.
*3.return left + right + 1
*Cost: Time-O(n^2), Space:O(h)
*/

int GetLargestBSTAtNode(Node *root, int lower, int higher) {
	if (root == NULL || higher < lower) {
		return 0;
	}
	if (root->val > higher || root->val < lower) {
		return 0;
	}
	int left_cnt = GetLargestBSTAtNode(root->left, lower, root->val);
	int right_cnt = GetLargestBSTAtNode(root->right, root->val, higher);
	return left_cnt + right_cnt + 1;
}

void GetLargestBST(Node *root, int *size) {
	if (root == NULL) {
		if (*size < 0) {
			*size = 0;
		}
		return;
	}
	int max = GetLargestBSTAtNode(root, numeric_limits<int>::min(), numeric_limits<int>::max());
	if (max > *size) {
		*size = max;
	}
	GetLargestBST(root->left, size);
	GetLargestBST(root->right, size);
}

/*
*Solution 2:
*Solution 1 compute subtree too many times, we can use a hashtable to store
*some temporary results during the computation to save time.
*The hashtable stores: Node * : left_available_nodes_num, right_available_nodes_num
*When you want to calc the size of largest BST rooted at given node:
*1.Fill the hashtable in the left-child
*2.Fill the hashtable in the right-child
*3.Check left-child:
*3.1.If left-child is less than current, all the available nodes in left subtree of
*    left-child can be added to the result, and we continue with the right child
*    of the left-child if it's available num is not 0 until NULL(All the way right-down).
*3.2.If left-child is larger than current, the whole left subtree should be removed,
*    we will not count these nodes in. And we will update the hashtable when we remove
*    subtrees all the way up. Why? Because if any node above given node want to count 
*    given node and it's subtrees in the BST, the subtrees of given node should count 
*    given node in, thus, the removed subtrees below will be remove again, we update
*    hashtable to save the time of doing this.
*4.Check right-child vice-versa.
*5.At last, compare largest BST size with largest BST size from left subtree and right
*  subtree.(The largest BST may rooted at current node or come from left or right subtree)
*Proof of running time O(n):
*As you can see, for the left child we check all the way right down to NULL, that's O(h).
*And for right child we will get the same thing, O(h). Let's assume there are n nodes in
*the tree, for level h of the tree there are n/2^h nodes, and for each node the running time
*is O(h) + O(h) = O(h). Thus, the whole running time is:
*SigmaOf(h*n/2^h) = n * SigmaOf(h/2^h) < n * limit(h/2^h) = 2n
*So, the whole running time is O(n)
*Cost: Time-O(n), Space:O(n)
*
*e.g. computing for node 12
*
*              Binary Tree:
*            _______6___________
*           /                   \
*        __1__            ______12______
*       /     \          /              \
*      0       3     ___10___          __13__
*                   /  (3,3) \        / (0,1)\
*                __4__      __14__   20      16
*               /(1,1)\    / (1,1)\ (0,0)   (0,0)
*              2      5   11      15
*             (0,0) (0,0)(0,0)   (0,0)
*
*10 is less than 12, we count left-subtree of 10 in.
*14 is larger than 12, we remove right-sbutree of 10.
*left-child done!
*13 is larger than 12, we count right-subtree of 13 in.
*left subtree of 13 has already removed, we stop here.
*right-child done!
*After calc:
*              Binary Tree:
*            _______6___________
*           /                   \
*        __1__            ______12______
*       /     \          /     (4,2)    \
*      0       3     ___10___          __13__
*                   /  (3,0) \        / (0,1)\
*                __4__      __14__   20      16
*               /(1,1)\    / (1,1)\ (0,0)   (0,0)
*              2      5   11      15
*             (0,0) (0,0)(0,0)   (0,0)
*
*10 is less than 12, we count left-subtree of 10 in.
*/

struct MapElement {
	MapElement():left(0),right(0){}
	int left;
	int right;
};

int GetLargestBST2(Node *root, unordered_map<Node *, MapElement> &hash_map) {
	if (root == NULL) {
		return 0;
	}
	int left_max = GetLargestBST2(root->left, hash_map);
	int right_max = GetLargestBST2(root->right, hash_map);
	unordered_map<Node *, MapElement>::iterator it;
	stack<Node *> parent_stack;
	MapElement me;
	if (root->left != NULL && root->left->val < root->val) {
		it = hash_map.find(root->left);
		me.left += (it->second).left + 1;
		parent_stack.push(root->left);
		Node *temp = root->left->right;
		while (temp != NULL && (it->second).right != 0) {
			if (temp->val > root->val) {
				it = hash_map.find(temp);
				int removed = (it->second).left + (it->second).right + 1;
				while (!parent_stack.empty()) {
					Node *parent = parent_stack.top();
					it = hash_map.find(parent);
					(it->second).right -= removed;
					parent_stack.pop();
				}
				break;
			}
			it = hash_map.find(temp);
			me.left += (it->second).left + 1;
			parent_stack.push(temp);
			temp = temp->right;
		}
	}
	while (!parent_stack.empty()) {
		parent_stack.pop();
	}
	if (root->right != NULL && root->right->val > root->val) {
		it = hash_map.find(root->right);
		me.right += (it->second).right + 1;
		parent_stack.push(root->right);
		Node *temp = root->right->left;
		while (temp != NULL && (it->second).left > 0) {
			if (temp->val < root->val) {
				it = hash_map.find(temp);
				int removed = (it->second).left + (it->second).right + 1;
				while (!parent_stack.empty()) {
					Node *parent = parent_stack.top();
					it = hash_map.find(parent);
					(it->second).left -= removed;
					parent_stack.pop();
				}
				break;
			}
			it = hash_map.find(temp);
			me.right += (it->second).right + 1;
			parent_stack.push(temp);
			temp = temp->left;
		}
	}
	hash_map.insert(make_pair(root, me));
	int current_max = me.left + me.right + 1;
	return max(current_max, max(left_max, right_max));
}

int main(int argc, char *argv[]) {
	Node *root = new Node(6);
	root->left = new Node(1);
	root->left->left = new Node(0);
	root->left->right = new Node(3);
	root->right = new Node(12);
	root->right->left = new Node(10);
	root->right->left->left = new Node(4);
	root->right->left->left->left = new Node(2);
	root->right->left->left->right = new Node(5);
	root->right->left->right = new Node(14);
	root->right->left->right->left = new Node(11);
	root->right->left->right->right = new Node(15);
	root->right->right = new Node(13);
	root->right->right->left = new Node(20);
	root->right->right->right = new Node(16);
	printf("Tree:");
	PrintByLevel(root);
	int size = -1;
	GetLargestBST(root, &size);
	printf("The largest BST topology is %d\n", size);
	unordered_map<Node *, MapElement> hash_map;
	int size2 = GetLargestBST2(root, hash_map);
	printf("The largest BST topology is %d\n", size2);
	Node *new_root = new Node(-1);
	new_root->left = root;
	size = -1;
	GetLargestBST(new_root, &size);
	printf("The largest BST topology is %d\n", size);
	hash_map.clear();
	size2 = GetLargestBST2(new_root, hash_map);
	printf("The largest BST topology is %d\n", size2);
	release_tree(root);
	delete new_root;
}
