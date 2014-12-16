/*Linkedlist is palindrome problem:
*Given a linkedlist with char value, check it whether a palindrome or not  
*e.g. a->b->c->d->c->b->a is palindrome and a->b->c->d is not palindrome
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
*1.Find the middle of given linkedlist
*2.Reverse the second half
*3.Compare the first half and the reversed second half
*4.Reverse the second half again
*5.Connection them
*Cost: Time-O(n), Space:O(1)
*/
Node * ReverseList(Node *head) {
	if(head == NULL || head->next == NULL) {
		return head;
	}
	Node *newHead = head;
	Node *cur = head->next;
	newHead->next = NULL;
	while (cur != NULL) {
		Node *temp = cur->next;
		cur->next = newHead;
		newHead = cur;
		cur = temp;
	}
	return newHead;
}

//Return middle node if number of elements in the list is odd
//Return last node of first half if number of elements in the list is even
Node * FindMiddle(Node *head) {
	if(head == NULL || head->next == NULL) {
		return head;
	}
	Node *slow = head;
	Node *fast = head->next;
	while (fast != NULL && fast->next != NULL) {
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

bool IsPalindrome(Node *head) {
	if(head == NULL || head->next == NULL) {
		return true;
	}
	Node *middle = FindMiddle(head);
	Node *head_2nd = middle->next;
	middle->next = NULL;
	head_2nd = ReverseList(head_2nd);
	Node *left = head;
	Node *right = head_2nd;
	bool ret = true;
	while (left != NULL && right != NULL) {
		if (left->val != right->val) {
			ret = false;
			break;
		}
		left = left->next;
		right = right->next;
	}
	middle->next = ReverseList(head_2nd);
	return ret;
}

int main(int argc, char *argv[]) {
	{
	char a[] = {'a','b','c','b','a'};
	Node *head = generate_list(a, sizeof(a)/sizeof(char));
	print_list(head);
	printf("Is palindrom:%s\n", IsPalindrome(head) ? "True" : "False");
	print_list(head);
	release_list(head);
	}
	{
	char a[] = {'a','b','b','a'};
	Node *head = generate_list(a, sizeof(a)/sizeof(char));
	print_list(head);
	printf("Is palindrom:%s\n", IsPalindrome(head) ? "True" : "False");
	print_list(head);
	release_list(head);
	}
	{
	char a[] = {'a','a'};
	Node *head = generate_list(a, sizeof(a)/sizeof(char));
	print_list(head);
	printf("Is palindrom:%s\n", IsPalindrome(head) ? "True" : "False");
	print_list(head);
	release_list(head);
	}
	{
	char a[] = {'a','b','c','d','e'};
	Node *head = generate_list(a, sizeof(a)/sizeof(char));
	print_list(head);
	printf("Is palindrom:%s\n", IsPalindrome(head) ? "True" : "False");
	print_list(head);
	release_list(head);
	}
	{
	char a[] = {'a','b','c','d'};
	Node *head = generate_list(a, sizeof(a)/sizeof(char));
	print_list(head);
	printf("Is palindrom:%s\n", IsPalindrome(head) ? "True" : "False");
	print_list(head);
	release_list(head);
	}
	{
	char a[] = {'a','b'};
	Node *head = generate_list(a, sizeof(a)/sizeof(char));
	print_list(head);
	printf("Is palindrom:%s\n", IsPalindrome(head) ? "True" : "False");
	print_list(head);
	release_list(head);
	}
}
