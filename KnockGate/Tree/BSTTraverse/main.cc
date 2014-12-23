/*BST traverse problem:
*Given a BST, traverse it in pre-order, in-order and post-order
*e.g.
*             4
*           /   \       pre-order-->    4213657
*         2      6      in-order--->    1234567
*       /   \   /  \    post-order->    1325764
*     1      3 5    7
*/

#include "stdio.h"
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

/*
*Solution:
*Traverse recursively: in-order for example
*1.Recursive call on left child
*2.Print current node
*3.Recursive call on left child
*Cost: Time-O(n), Space:O(lg(n))
*/

void preorder_recursive (Node *root) {
	if (root == NULL) {
		return;
	}
	printf("%d ",root->val);
	preorder_recursive(root->left);
	preorder_recursive(root->right);
}

void inorder_recursive (Node *root) {
	if (root == NULL) {
		return;
	}
	inorder_recursive(root->left);
	printf("%d ",root->val);
	inorder_recursive(root->right);
}

void postorder_recursive (Node *root) {
	if (root == NULL) {
		return;
	}
	postorder_recursive(root->left);
	postorder_recursive(root->right);
	printf("%d ",root->val);
}

/*
*Solution:
*Traverse pre&in-order non-recursively: pre-order for example
*We use stack to simulate the recursive calls. The 
*top of stack is the node of pre recursive calls.
*1.Print current node
*2.Go left
*3.If current node is NULL then pop node from the
*  stack and process the right child
*Cost: Time-O(n), Space:O(lg(n))
*/

void preorder_nonrecursive (Node *root) {
	stack<Node *> s;
	Node *cur = root;
	while (cur != NULL || !s.empty()) {
		if (cur != NULL) {
			printf("%d ", cur->val);
			s.push(cur);
			cur = cur->left;
		} else {
			Node *parent = s.top();
			s.pop();
			cur = parent->right;
		}
	}
}

void inorder_nonrecursive (Node *root) {
	stack<Node *> s;
	Node *cur = root;
	while (cur != NULL || !s.empty()) {
		if (cur != NULL) {
			s.push(cur);
			cur = cur->left;
		} else {
			Node *parent = s.top();
			printf("%d ", parent->val);
			s.pop();
			cur = parent->right;
		}
	}
}

/*
*Solution:
*Traverse post-order non-recursively:
*We use stack to simulate the recursive calls, and another
*stack to remember current node is the left child or the
*right child of its parent.
*1.Go all the way left down
*2.If current node is empty, then:
*2.1 If current node is the left child of parent node,
*    then try parent's right child
*2.2 If current node is the right child of parent node,
*    then the right sub-tree of parent has been visited
*    we go "right child" up: if the top of stack is the
*    right child of next one, pop it.
*Cost: Time-O(n), Space:O(lg(n))
*/

void postorder_nonrecursive (Node *root) {
	stack<Node *> sn;
	stack<bool> sl;
	Node *cur = root;
	while (true) {
		if (cur != NULL) {
			sn.push(cur);
			sl.push(true);
			cur = cur->left;
		} else {
			if (sl.top()) {
				sl.pop();
				sl.push(false);
				cur = sn.top()->right;
			} else {
				while (!sl.empty() && !sl.top()) {
					sl.pop();
					printf("%d ", sn.top()->val);
					sn.pop();
				}
				if (sn.empty()) {
					break;
				} else {
					sl.pop();
					cur = sn.top()->right;
					sl.push(false);
				}
			}
		}
	}
}

/*
*Solution:
*Traverse post-order non-recursively:
*We use the algorithm before and opimize the relation
*stack out.
*Cost: Time-O(n), Space:O(lg(n))
*/

void postorder_nonrecursive_better (Node *root) {
	Node *fake_root = new Node(0);
	fake_root->left = root;
	stack<Node **> s;
	Node **cur = &(fake_root->left);
	while (true) {
		if (*cur != NULL) {
			s.push(cur);
			cur = &((*cur)->left);
		} else {
			if (cur == &((*s.top())->left)) {
				cur = &((*s.top())->right);
			} else {
				while (!s.empty() && cur == &((*s.top())->right)) {
					cur = s.top();
					printf("%d ", (*cur)->val);
					s.pop();
				}
				if (s.empty()) {
					break;
				} else {
					cur = &((*(s.top()))->right);
				}
			}
		}
	}
	delete fake_root;
}

int main(int argc, char *argv[]) {
	{
	int a[] = {4,2,6,1,3,5,7};
	Node *root = build_tree(a, sizeof(a)/sizeof(int));
	printf("Pre-order recursive:\n");
	preorder_recursive(root);
	printf("\n");
	printf("In-order recursive:\n");
	inorder_recursive(root);
	printf("\n");
	printf("Post-order recursive:\n");
	postorder_recursive(root);
	printf("\n");
	printf("Pre-order non-recursive:\n");
	preorder_nonrecursive(root);
	printf("\n");
	printf("In-order non-recursive:\n");
	inorder_nonrecursive(root);
	printf("\n");
	printf("Post-order non-recursive:\n");
	postorder_nonrecursive(root);
	printf("\n");
	printf("Post-order non-recursive better:\n");
	postorder_nonrecursive_better(root);
	printf("\n");
	release_tree(root);
	}
}

