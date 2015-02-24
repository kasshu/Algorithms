/*Double linked list to BST problem:
*Given a sorted double linked list, convert it into a BST(prev as left, next as right)  
*e.g.
*                                            4
*                                          /   \
*  1<->2<->3<->4<->5<->6<->7   --->      3      6        
*                                      /   \   /  \
*                                    1      2 5    7
*/

#include "stdio.h"
#include <queue>
using namespace std;

struct Node {
	Node (int value):prev(NULL),next(NULL),val(value) {}
	Node *prev;
	Node *next;
	int val;
};

void print_tree_inorder (Node *root) {
	if (root == NULL) {
		return;
	}
	print_tree_inorder(root->prev);
	printf("%d ",root->val);
	print_tree_inorder(root->next);
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
		cur = cur->next;
	} 
	printf("null\n");
	printf("Inverse order: ");
	cur = tail;
	while (cur != NULL) {
		printf("%d->",cur->val);
		cur = cur->prev;
	}
	printf("null\n");
}

void release_tree (Node *root) {
	if (root == NULL) {
		return;
	}
	release_tree(root->prev);
	release_tree(root->next);
	delete root;
}

Node *build_list(int *arr, int len) {
	if (arr == NULL || len == 0) {
		return NULL;
	}
	Node *head = new Node(arr[0]);
	Node *tail = head;
	for (int i = 1; i < len; i++) {
		Node *temp = new Node(arr[i]);	
		tail->next = temp;
		temp->prev = tail;
		tail = temp;
	}
	return head;
}

void PrintByLevel (Node *root) {
	if (root == NULL) {
		return;
	}
	queue<Node *> q;
	q.push(root);
	while (!q.empty()) {
		Node *temp = q.front();
		if (temp->prev != NULL) {
			q.push(temp->prev);
		}
		if (temp->next != NULL) {
			q.push(temp->next);
		}
		printf("%d ", temp->val);
		q.pop();
	}
	printf("\n");
}

/*
*Solution:
*A recursive solution:
*1.Find the middle node in double linked list.
*2.Recursive call on left half and right half.
*3.Link them
*Cost: Time-O(n), Space:O(lg(n))
*e.g.
*     left-subtree <-> cur-node <-> right-subtree
*/

Node * dlinked_to_bst_recursive (Node *head) {
	if (head == NULL || head->next == NULL) {
		return head;
	}
	Node *slow = head;
	Node *fast = head->next;
	while (fast != NULL) {
		slow = slow->next;
		fast = fast->next;
		if (fast == NULL) {
			break;
		}
		fast = fast->next;
	}
	Node *left_tail = slow->prev;
	Node *right_head = slow->next;
	left_tail->next = NULL;
	slow->prev = dlinked_to_bst_recursive(head);
	if (right_head != NULL) {
		right_head->prev = NULL;
		slow->next = dlinked_to_bst_recursive(right_head);
	} else {
		slow->next = NULL;
	}
	return slow;
}

Node *dlinked_to_bst(Node *head) {
	if (head == NULL) {
		return NULL;
	}
	Node *root = dlinked_to_bst_recursive(head);
	return root;
}

int main(int argc, char *argv[]) {
	{
	int a[] = {1,2,3,4,5,6,7};
	Node *head = build_list(a, sizeof(a)/sizeof(int));
	print_list(head);
	Node *root = dlinked_to_bst(head);
	PrintByLevel(root);
	release_tree(root);
	}
	{
	int a[] = {1,2};
	Node *head = build_list(a, sizeof(a)/sizeof(int));
	print_list(head);
	Node *root = dlinked_to_bst(head);
	PrintByLevel(root);
	release_tree(root);
	}
	{
	int a[] = {1};
	Node *head = build_list(a, sizeof(a)/sizeof(int));
	print_list(head);
	Node *root = dlinked_to_bst(head);
	PrintByLevel(root);
	release_tree(root);
	}
}
