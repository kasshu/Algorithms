/*Joseph circle problem:
*Given a Joseph circle represented by circular linked list, delete every kth node  
*e.g.  k = 3
* 
*     head-> a->b
*          /     \
*         g       c <- delete
*         |       |
*         f       d
*         \      /
*            e
*/

#include "stdio.h"

struct Node {
	Node *next;
	char val;
};

void print_list (Node *head) {
	Node *cur = head;
	do {
		printf("%c->",cur->val);
		cur = cur->next;
	} while (cur != head);
	printf("null\n");
}

void release_list (Node *head) {
	Node *cur = head;
	do {
		Node *p = cur->next;
		delete cur;
		cur = p;
	} while (cur != head);
}

Node *generate_list(char *arr, unsigned int len) {
	if (arr == NULL || len == 0) {
		return NULL;
	}
	Node *head = new Node;
	head->val = arr[0];
	Node *tail = head;
	for (unsigned int i=1; i<len; i++) {
		Node *node = new Node;
		node->val = arr[i];
		tail->next = node;
		tail = node;
	}
	tail->next = head;
	return head;
}

/*
*Solution:
*Since node in circular linked list always has a next element, we can 
*use delete current node algorithm to solve Joseph Circle problem.
*Cost: Time-O(kn), Space:O(1)
*Proof:
*For Joseph Circle problem, we have to delete n-1 nodes, and for each
*node, we walk through k nodes. So, the time complexity is: 
*                        O(k*(n-1)) = O(kn)
*/
void DeleteCurrentNode(Node *cur) {
	if (cur == NULL || cur->next == NULL || cur->next == cur) {
		return;
	}
	cur->val = cur->next->val;
	Node *temp = cur->next;
	cur->next = cur->next->next;
	delete temp;
}

Node * SolveJosephCircleProblem(Node *head, unsigned int k) {
	if (head == NULL || k == 0) {
		return head;
	}
	Node *cur = head;
	unsigned int cnt = 0;
	while (cur != cur->next) {
		if (++cnt == k) {
			printf("Delete node %c\n", cur->val);
			DeleteCurrentNode(cur);
			print_list(cur);
			cnt = 0;
		} else {
			cur = cur->next;
		}
	}
	return cur;
}

int main(int argc, char *argv[]) {
	{
	char *a = new char[26];
	for (int i = 0; i < 26; i++) {
		a[i] = 'a' + i;
	}
	Node *head = generate_list(a, 26);
	print_list(head);
	head = SolveJosephCircleProblem(head, 3);
	print_list(head);
	release_list(head);
	delete [] a;
	}
}
