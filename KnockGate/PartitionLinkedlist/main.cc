/*PartitionLinkedlist problem:
*Given a linkedlist with int value and an apartValue, how can you partition this linkedlist into:
*smaller->...->smaller->...->apartValue->...->larger...->larger, just like what partition in quick sort do?
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
*During the traverse of linkedlist, we split it into 3 linkedlist:
*1.Smaller linkedlist
*2.Euqal linkedlist
*3.Larger linkedlist
*At last, we link them
*Cost: Time-O(n), Space:O(1)
*/
void InsertAfter(Node *head, Node *p) {
	if(head == NULL || p == NULL) {
		return;
	}
	Node *temp = head->next;
	head->next = p;
	p->next = temp;
}

Node * PartitionLinkedlist(Node *head, int apartValue) {
	if (head == NULL || head->next == NULL) {
		return head;
	}
	//split into smaller/euqal/larger linkedlist with empty head node
	Node *smaller = new Node;
	smaller->next = NULL;
	Node *equal = new Node;
	equal->next = NULL;
	Node *larger = new Node;
	larger->next = NULL;
	while (head != NULL) {
		Node *p = head->next;
		if (head->val < apartValue) {
			InsertAfter(smaller, head);
		} else if (head->val > apartValue) {
			InsertAfter(larger, head);
		} else {
			InsertAfter(equal, head);
		}
		head = p;
	}
	//find the tail of smaller
	Node *pre = smaller;
	Node *cur = smaller->next;
	while (cur != NULL) {
		pre = cur;
		cur = cur->next;
	}
	if (equal->next != NULL) {
		pre->next = equal->next;
		cur = equal->next;
		//find the tail of euqal
		while (cur != NULL) {
			pre = cur;
			cur = cur->next;
		}
	}
	//we don't care whether larger->next is null
	pre->next = larger->next;
	//remove smaller head
	Node *newHead = smaller->next;
	delete smaller;
	delete equal;
	delete larger;
	return newHead;
}

/*Advance problem:
*Do quick sort with linkedlist
*Solution:
*Do what quick sort do, partition and recursive calls
*/

Node * partition(Node *head) {
	if (head == NULL || head->next == NULL) {
		return head;
	}
	Node *pivot = head;
	head = head->next;
	Node *smaller_or_equal = new Node;
	smaller_or_equal->next = NULL;
	Node *larger = new Node;
	larger->next = NULL;
	while (head != NULL) {
		Node *p = head->next;
		if (head->val <= pivot->val) {
			Node *temp = smaller_or_equal->next;
			smaller_or_equal->next = head;
			head->next = temp;
		} else {
			Node *temp = larger->next;
			larger->next = head;
			head->next = temp;
		}
		head = p;
	}
	Node *pre = smaller_or_equal;
	Node *cur = smaller_or_equal->next;
	while (cur != NULL) {
		pre = cur;
		cur = cur->next;
	}
	pre->next = pivot;
	pivot->next = larger->next;
	Node *newHead = smaller_or_equal->next;
	delete smaller_or_equal;
	delete larger;
	return newHead;
}

Node * quick_sort(Node *head) {
	if (head == NULL || head->next == NULL) {
		return head;
	}
	Node *newHead = partition(head);
	Node *smaller = NULL;
	Node *larger = NULL;
	if (newHead != head) {
		Node *p = newHead->next;
		Node *t = newHead;
		while (p != head) {
			t = p;
			p = p->next;
		}
		t->next = NULL;
		smaller = quick_sort(newHead);
	}
	if (head->next != NULL) {
		larger = quick_sort(head->next);
	}
	Node *temp = new Node;
	temp->next = smaller;
	Node *p = temp->next;
	Node *t = temp;
	while (p != NULL) {
		t = p;
		p = p->next;
	}
	t->next = head;
	head->next = larger;
	newHead = temp->next;
	delete temp;
	return newHead;
}

int main(int argc, char *argv[]) {
	int a[] = {1,10,3,8,5,11,7,4,9,2};
	//test of middle
	printf("Apartval:5\n");
	Node *head = generate_list(a, 10);
	print_list(head);
	head = PartitionLinkedlist(head, 5);
	print_list(head);
	release_list(head);
	//test of left head, smaller/equal is null
	printf("Apartval:0\n");
	head = generate_list(a, 10);
	print_list(head);
	head = PartitionLinkedlist(head, 0);
	print_list(head);
	release_list(head);
	//test of right head, equal/larger is null
	printf("Apartval:12\n");
	head = generate_list(a, 10);
	print_list(head);
	head = PartitionLinkedlist(head, 12);
	print_list(head);
	release_list(head);
	//test of non-exist val, equal is null
	printf("Apartval:6\n");
	head = generate_list(a, 10);
	print_list(head);
	head = PartitionLinkedlist(head, 6);
	print_list(head);
	release_list(head);
	//test quick sort
	int b[] = {5,1,3,2,4,9,6,8,7};
	head = generate_list(b, 9);
	printf("Before sort:\n");
	print_list(head);
	head = quick_sort(head);
	printf("After sort:\n");
	print_list(head);
	release_list(head);
}
