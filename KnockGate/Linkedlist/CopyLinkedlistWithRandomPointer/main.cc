/*Copy linked list with random pointer problem:
*Given a linkedlist with an extra random pointer, copy it
*e.g. 
*        ------<---
*        |        |
*     a->b->c->d->e->null
*     |     |  |
*     ---->--  ^
*    a->random points to c
*    b->random points to nothing
*    c->random points to nothing
*    d->random points to itself
*    e->random points to b
*/

#include "stdio.h"
#include <map>
using namespace std;

struct Node {
	Node *next;
	Node *random;
	int val;
};

void print_random_list (Node *head) {
	while (head != NULL) {
		printf("%d",head->val);
		if (head->random != NULL) {
			printf("->%d", head->random->val);
		}
		printf("\n");
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

Node *generate_random_list(size_t len, const map<int, int> &m) {
	if (len == 0) {
		return NULL;
	}
	map<int, Node*> node_map;
	Node *head = new Node;
	head->random = NULL;
	head->val = 0;
	node_map[0] = head;
	Node *tail = head;
	for (int i=1; i<len; i++) {
		Node *node = new Node;
		node->val = i;
		node->random = NULL;
		node_map[i] = node;
		tail->next = node;
		tail = node;
	}
	tail->next = NULL;
	map<int, int>::const_iterator citer = m.begin();
	while (citer != m.end()) {
		if (citer->first < len && citer->second < len) {
			(node_map[citer->first])->random = (node_map[citer->second]);
		}
		citer++;
	}
	return head;
}

/*
*Solution normal:
*Use a hashtable to remember original and copy relation
*1.Copy the linked list through next point and fill the hashtable
*2.Pass the orginal linked list again, use the hashtable to init 
*  the random pointer in the copied linked list
*Cost: Time-O(n), Space:O(n)
*/
Node * CopyRandomLinkedlistNormal(Node *head) {
	if(head == NULL) {
		return NULL;
	}
	map<Node *, Node *> copy_map;
	Node *newHead = new Node;
	newHead->val = head->val;
	newHead->random = NULL;
	newHead->next = NULL;
	copy_map[head] = newHead;
	Node *tail = newHead;
	Node *cur = head->next;
	while (cur != NULL) {
		Node *node = new Node; 
		node->val = cur->val;
		node->next = NULL;
		node->random = NULL;
		copy_map[cur] = node;
		tail->next = node;
		tail = node;
		cur = cur->next;
	}
	cur = head;
	while (cur != NULL) {
		Node *pointed = cur->random;
		if (pointed != NULL) {
			(copy_map[cur])->random = copy_map[pointed];
		}
		cur = cur->next;
	}
	return newHead;
}

/*
*Solution better:
*1.Copy nodes and insert the new node after the orginal one
*2.Init the random pointer of new node according to orginal node
*3.Break the linked list into 2 linked list
*Cost: Time-O(n), Space:O(1)
*e.g. 
*               ---------<------------
*            ---|--<---------------  |
*            |  |                 |  |
*     a->a`->b->b`->c->c`->d->d`->e->e`->null
*     |  |          |  |   |  |
*     ---|--->-------  |   ^  |
*        -------->------      ^
*/
Node * CopyRandomLinkedlistBetter(Node *head) {
	if(head == NULL) {
		return NULL;
	}
	//copy node and insert
	Node *cur = head;
	while (cur != NULL) {
		Node *temp = cur->next;
		Node *node = new Node;
		node->val = cur->val;
		node->random = NULL;
		node->next = temp;
		cur->next = node;
		cur = temp;
	}
	//init random pointer
	cur = head;
	while (cur != NULL) {
		Node *copy = cur->next;
		if (cur->random != NULL) {
			copy->random = cur->random->next;
		}
		cur = copy->next;
	}
	//split linked list
	cur = head->next->next;
	Node *newHead = head->next;
	Node *tail = head;
	tail->next = NULL;
	Node *newTail = newHead;
	newTail->next = NULL;
	bool toOld = true;
	while (cur != NULL) {
		Node *temp = cur->next;
		cur->next = NULL;
		if (toOld) {
			tail->next = cur;
			tail = cur;
		} else {
			newTail->next = cur;
			newTail = cur;
		}
		toOld = !toOld;
		cur = temp;
	}
	return newHead;
}

int main(int argc, char *argv[]) {
	{
	map<int, int> random_point;
	random_point[0] = 2;
	random_point[3] = 3;
	random_point[4] = 1;
	Node *head = generate_random_list(5, random_point);
	print_random_list(head);
	Node *copy=  CopyRandomLinkedlistNormal(head);
	print_random_list(copy);
	release_list(head);
	release_list(copy);
	}
	{
	map<int, int> random_point;
	random_point[0] = 2;
	random_point[3] = 3;
	random_point[4] = 1;
	Node *head = generate_random_list(5, random_point);
	Node *copy=  CopyRandomLinkedlistBetter(head);
	print_random_list(head);
	print_random_list(copy);
	release_list(head);
	release_list(copy);
	}
}
