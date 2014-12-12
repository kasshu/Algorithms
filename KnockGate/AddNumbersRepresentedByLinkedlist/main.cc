/*Add numbers represented by linked list problem:
*Numbers are represented by linked list, e.g.
*6789 = 6->7->8->9->null
*Add two numbers represented by linked list
*e.g. given:
*			6789 = 6->7->8->9->null
*		  	  +
*			4321 = 4->3->2->1->null
*             =
*  return: 11110 = 1->1->1->1->0->null
*/

#include "stdio.h"

struct Node {
	Node *next;
	int val;
};

void print_list (Node *head) {
	while (head != NULL) {
		printf("%d->",head->val);
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

Node *generate_list(int *arr, unsigned int len) {
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
*1.Reverse given linked list
*2.Add them 
*3.Reverse given linked list and result linked list
*Why not convert linked list into int or long?
*Because numbers represented by linked list are infinit, 
*if you convert them, they would overflow.
*Cost: Time-O(max(m,n)), Space:O(max(m,n))
*e.g. given:
*			6789 = 6->7->8->9->null        reverse->     9->8->7->6->null
*		  	  +                                              +
*			4321 = 4->3->2->1->null        reverse->     1->2->3->4->null
*             =                                              =
*  return: 11110 = 1->1->1->1->0->null   <-reverse       0->1->1->1->1->null
*/
Node *Reverse(Node *head) {
	if (head == NULL || head->next == NULL) {
		return head;
	}
	Node *cur = head->next;
	Node *newHead = head;
	newHead->next = NULL;
	while (cur != NULL) {
		Node *temp = cur->next;
		cur->next = newHead;
		newHead = cur;
		cur = temp;
	}
	return newHead;
}

Node * AddNumbers(Node *head_a, Node *head_b) {
	if(head_a == NULL || head_b == NULL) {
		return NULL;
	}
	Node *reverse_a = Reverse(head_a);
	Node *reverse_b = Reverse(head_b);
	Node *cur_a = reverse_a;
	Node *cur_b = reverse_b;
	Node *newHead = NULL;
	Node *tail = NULL;
	int carry = 0;
	while (cur_a != NULL && cur_b != NULL) {
		Node *cur = new Node;
		cur->next = NULL;
		cur->val = cur_a->val + cur_b->val + carry;
		if (cur->val >= 10) {
			cur->val %= 10;
			carry = 1;
		} else {
			carry = 0;
		}
		if (newHead == NULL) {
			newHead = cur;
		}
		if (tail == NULL) {
			tail = cur;
		} else {
			tail->next = cur;
			tail = cur;
		}
		cur_a = cur_a->next;
		cur_b = cur_b->next;
	}
	Node *remains = NULL;
	if (cur_a != NULL) {
		remains = cur_a;
	}
	if (cur_b != NULL) {
		remains = cur_b;
	}
	while (remains != NULL) {
		Node *cur = new Node;
		cur->next = NULL;
		cur->val = remains->val + carry;
		carry = 0;
		tail->next = cur;
		tail = cur;
		remains = remains->next;
	}
	if (carry != 0) { //cur_a == NULL && cur_b == NULL
		Node *cur = new Node;
		cur->next = NULL;
		cur->val = carry;
		tail->next = cur;
		tail = cur;
	}
	Reverse(reverse_a);
	Reverse(reverse_b);
	Node *ret = Reverse(newHead);
	return ret;
}

int main(int argc, char *argv[]) {
	{
	int a[] = {6,7,8,9};
	Node *head_a = generate_list(a, sizeof(a)/sizeof(int));
	print_list(head_a);
	int b[] = {4,3,2,1};
	Node *head_b = generate_list(b, sizeof(b)/sizeof(int));
	print_list(head_b);
	Node *head_sum = AddNumbers(head_a, head_b);
	print_list(head_sum);
	release_list(head_a);
	release_list(head_b);
	release_list(head_sum);
	}
	{
	int a[] = {6,7,8,9};
	Node *head_a = generate_list(a, sizeof(a)/sizeof(int));
	print_list(head_a);
	int b[] = {1};
	Node *head_b = generate_list(b, sizeof(b)/sizeof(int));
	print_list(head_b);
	Node *head_sum = AddNumbers(head_a, head_b);
	print_list(head_sum);
	release_list(head_a);
	release_list(head_b);
	release_list(head_sum);
	}
	{
	int a[] = {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9};
	Node *head_a = generate_list(a, sizeof(a)/sizeof(int));
	print_list(head_a);
	int b[] = {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9};
	Node *head_b = generate_list(b, sizeof(b)/sizeof(int));
	print_list(head_b);
	Node *head_sum = AddNumbers(head_a, head_b);
	print_list(head_sum);
	release_list(head_a);
	release_list(head_b);
	release_list(head_sum);
	}
}
