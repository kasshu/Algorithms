/*Reverse linked list every k nodes problem:
*Reverse given linked list every k nodes, if the nodes left is less than k your work is done.
*e.g. k = 3
*    a->b->c->d->e->f->g->h->null
*              becomes: 
*    c->b->a->f->e->d->g->h->null
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
*Use a counter of nodes, if counter equals k, then reverse 
*the linked list part before.
*Cost: Time-O(n), Space:O(1)
*e.g. k = 3, cnt == 3
*     c->b->a->d->e->f->g->h->null
*           ^  ^     ^  ^
*           |  |     |  |
*         pre head tail cur
*               \   /
*              reverse
*/
Node * ReverseLinkedlistEveryKNodes(Node *head, size_t k) {
	if(head == NULL || head->next == NULL || k <= 1) {
		return head;
	}
	size_t cnt = 0;
	Node *cur = head;
	Node *part_head = head;
	Node *part_tail = head;
	Node *pre = NULL;
	Node *newHead = head;
	while (cur != NULL) {
		cnt++;
		part_tail = cur;
		cur = cur->next;
		if (cnt == k) {
			//reverse part
			Node *part_cur = part_head;
			while (part_cur != part_tail) {
				Node *temp = part_cur->next;
				part_cur->next = part_tail->next;
				part_tail->next = part_cur;
				part_cur = temp;
			}
			//link
			if (pre == NULL) {
				newHead = part_tail;
			} else {
				pre->next = part_tail;
			}
			//adjust pointers and counter
			pre = part_head;
			part_head = pre->next;
			cnt = 0;
		}
	}
	return newHead;
}

int main(int argc, char *argv[]) {
	{
	char a[] = {'a','b','c','d','e','f','g','h'};
	Node *head = generate_list(a, sizeof(a)/sizeof(char));
	print_list(head);
	head = ReverseLinkedlistEveryKNodes(head, 3);
	print_list(head);
	release_list(head);
	}
	{
	char a[] = {'a','b','c','d','e','f','g','h'};
	Node *head = generate_list(a, sizeof(a)/sizeof(char));
	print_list(head);
	head = ReverseLinkedlistEveryKNodes(head, 2);
	print_list(head);
	release_list(head);
	}
	{
	char a[] = {'a','b','c','d','e','f','g','h'};
	Node *head = generate_list(a, sizeof(a)/sizeof(char));
	print_list(head);
	head = ReverseLinkedlistEveryKNodes(head, 8);
	print_list(head);
	release_list(head);
	}
	{
	char a[] = {'a','b','c','d','e','f','g','h'};
	Node *head = generate_list(a, sizeof(a)/sizeof(char));
	print_list(head);
	head = ReverseLinkedlistEveryKNodes(head, 9);
	print_list(head);
	release_list(head);
	}
}
