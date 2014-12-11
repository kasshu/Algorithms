/*Delete nodes in linked list problem series:
*Problem 1:
*Given a linked list, delete the node at 1/2 or 1/3 or a/b(a<b and b%a==1).
*Your algorithm should pass the linked list once.
*e.g. 
*    a->b->c->d->e->f->g->h->i->null
*          ^     ^  ^
*          |     |  |
*         1/3  1/2  2/3
*/

#include "stdio.h"

struct Node {
	Node *next;
	char val;
};

void print_list (Node *head) {
	while (head != NULL) {
		printf("%c->",head->val);
		head = head->next;
	}
	printf("null\n");
}

void release_list (Node *head) {
	while (head != NULL) {
		Node *p = head->next;
		delete head;
		head = p;
	}
}

Node *generate_list(char *arr, unsigned int len) {
	if (arr == NULL || len == 0) {
		return NULL;
	}
	Node *head = new Node;
	head->val = arr[0];
	Node *tail = head;
	for (int i=1; i<len; i++) {
		Node *node = new Node;
		node->val = arr[i];
		tail->next = node;
		tail = node;
	}
	tail->next = NULL;
	return head;
}

/*
*Solution:
*We have a fast pointer and a slow pointer.
*Fast pointer passes b nodes and slow pointer passes a nodes each time.
*Cost: Time-O(n), Space:O(1)
*e.g. b = 3, a = 1
*     a->b->c->d->e->f->g->h->i->null
*        ^           ^
*        |           |
*      slow        fast
*/
Node * DeleteNodeAofB(Node *head, size_t a, size_t b) {
	if(head == NULL || head->next == NULL || a == 0 || b <= 1) {
		return head;
	}
	Node *fake = new Node;
	fake->next = head;
	Node *pre = fake;
	Node *slow = fake;
	Node *fast = fake;
	while (true) {
		for (int i = 0; i < b; i++) {
			if (fast == NULL) { 
				if (slow == fake) {
					pre->next = head->next;
					delete head;
				} else {
					pre->next = slow->next;
					delete slow;
				}
				Node *ret = fake->next;
				delete fake;
				return ret;
			}
			fast = fast->next;	
		}
		for (int i = 0; i < a - 1; i++) {
			slow = slow->next;
		}
		pre = slow;
		slow = slow->next;
	}

}

/*
*Problem 2:
*Given a linked list, delete the kth node of inverse order
*Your algorithm should pass the linked list once.
*e.g. 
*    a->b->c->d->e->f->g->h->i->null
*                   ^
*                   |
*             4th of inverse order
*/
/*
*Solution:
*We have a fast pointer and a slow pointer.
*Fast pointer and slow pointer have the same walking speed,
*and slow pointer starts at the head meanwhile fast pointer starts at (k+1)th node of order
*Cost: Time-O(n), Space:O(1)
*e.g. k = 4
*     a->b->c->d->e->f->g->h->i->null
*     ^           ^
*     |           |
*   slow        fast
*/

Node * DeleteKthInverseOrderNode(Node *head, size_t k) {
	if(head == NULL || k == 0) {
		return head;
	}
	Node *fake = new Node;
	fake->next = head;
	Node *pre = fake;
	Node *slow = head;
	Node *fast = head;
	for (int i = 0; i < k; i++) {
		if (fast == NULL) { //k is longer than the linked list
			return head;
		}
		fast = fast->next;
	}
	while (fast != NULL) {
		pre = slow;
		slow = slow->next;
		fast = fast->next;
	}
	pre->next = slow->next;
	delete slow;
	Node *newHead = fake->next;
	delete fake;
	return newHead;
}

/*
*Problem 3:
*Delete a given node in the linked list which you don't have the head
*Your algorithm should cost O(1)
*e.g. 
*    a->b->c->d->e->f->g->h->i->null
*                   ^
*                   |
*               given node 
*/
/*
*Solution:
*Copy the value of next node to current one and delete the next node
*If the given node is the last node in linked list, this algorithm does not work
*Cost: Time-O(1), Space:O(1)
*e.g. 
*     a->b->c->d->e->f->g->h->i->null
*                    ^  ^
*                    |  |
*              current  copy&delete
*/

void DeleteCurrentNode(Node *cur) {
	if(cur == NULL || cur->next == NULL) {
		return;
	}
	cur->val = cur->next->val;
	Node *temp = cur->next;
	cur->next = cur->next->next;
	delete temp;
}

int main(int argc, char *argv[]) {
	{
	char a[] = {'a','b','c','d','e','f','g','h','i'};
	Node *head = generate_list(a, sizeof(a)/sizeof(char));
	print_list(head);
	head = DeleteNodeAofB(head, 1, 2);
	print_list(head);
	release_list(head);
	}
	{
	char a[] = {'a','b','c','d','e','f','g','h','i'};
	Node *head = generate_list(a, sizeof(a)/sizeof(char));
	print_list(head);
	head = DeleteNodeAofB(head, 1, 3);
	print_list(head);
	release_list(head);
	}
	{
	char a[] = {'a','b','c','d','e','f','g','h','i'};
	Node *head = generate_list(a, sizeof(a)/sizeof(char));
	print_list(head);
	head = DeleteNodeAofB(head, 2, 3);
	print_list(head);
	release_list(head);
	}
	{
	char a[] = {'a','b','c','d','e','f','g','h','i'};
	Node *head = generate_list(a, sizeof(a)/sizeof(char));
	print_list(head);
	head = DeleteKthInverseOrderNode(head, 4);
	print_list(head);
	release_list(head);
	}
	{
	char a[] = {'a','b','c','d','e','f','g','h','i'};
	Node *head = generate_list(a, sizeof(a)/sizeof(char));
	print_list(head);
	head = DeleteKthInverseOrderNode(head, 9);
	print_list(head);
	release_list(head);
	}
	{
	char a[] = {'a','b','c','d','e','f','g','h','i'};
	Node *head = generate_list(a, sizeof(a)/sizeof(char));
	print_list(head);
	head = DeleteKthInverseOrderNode(head, 1);
	print_list(head);
	release_list(head);
	}
	{
	char a[] = {'a','b','c','d','e','f','g','h','i'};
	Node *head = generate_list(a, sizeof(a)/sizeof(char));
	print_list(head);
	head = DeleteKthInverseOrderNode(head, 10);
	print_list(head);
	release_list(head);
	}
	{
	char a[] = {'a','b','c','d','e','f','g','h','i'};
	Node *head = generate_list(a, sizeof(a)/sizeof(char));
	print_list(head);
	Node *cur = head->next->next->next->next->next;
	DeleteCurrentNode(cur);
	print_list(head);
	release_list(head);
	}
	{
	char a[] = {'a','b','c','d','e','f','g','h','i'};
	Node *head = generate_list(a, sizeof(a)/sizeof(char));
	print_list(head);
	Node *cur = head->next->next->next->next->next->next->next->next;
	DeleteCurrentNode(cur);
	print_list(head);
	release_list(head);
	}
}
