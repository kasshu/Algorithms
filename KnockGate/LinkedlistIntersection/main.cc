/*Linked list intersection problem:
*Given two linked list, check if they intersect with each other.
*/

#include "stdio.h"
#include <set>
#include <cstdlib>
using namespace std;

struct Node {
	Node *next;
	int val;
};

//Print linked list that may have a loop
void print_list (Node *head) {
	set<Node *> node_set;
	while (head != NULL && node_set.count(head) == 0) {
		printf("%d->",head->val);
		node_set.insert(head);
		head = head->next;
	}
	printf("null\n");
}

//Delete linked list that may have a loop
void release_list (Node *head, set<Node *> &node_set) {
	while (head != NULL && node_set.count(head) == 0) {
		Node *p = head->next;
		delete head;
		node_set.insert(head);
		head = p;
	}
}

//Different nodes have different value
Node *generate_list(int *arr, unsigned int len, map<int, Node *> &node_map) {
	if (arr == NULL || len == 0) {
		return NULL;
	}
	map<int, Node *>::iterator it = node_map.find(arr[0]);
	if (it != node_map.end()) {
		return iter->second;
	}
	Node *head = new Node;
	head->val = arr[0];
	node_map[head->val] = head;
	Node *tail = head;
	for (int i=1; i<len; i++) {
		it = node_map.find(arr[i]);
		if (it != node_map.end()) {
			//loop or intersect with other linked list
			Node *node = it->second;
			tail->next = node;
			return head;
		} else {
			Node *node = new Node;
			node->val = arr[i];
			node_map[node->val] = node;
			tail->next = node;
			tail = node;
		}
	}
	//pure linked list
	tail->next = NULL;
	return head;
}

/*
*Solution:
*Whether each linked list has a loop, affect the intersection results.
* 
*1.None of linked list have loop, they may intersect or not, do it in normal way.
*        intersect1              intersect2               not intersect
*          h1 h2                     h1                     h1   h2
*          |  |                      |                      |    |
*          |  |                      | h2                   |    |
*          \ /                       |                      |    |
*           |                        |                      |    |
*           |                        |                      |    |
* 
* 2.One linked list has a loop and the other doesn't, they will never intersect.
* Why? Because, if they intersect, they should share the same loop.
*                not intersect               not intersect
*                   |      |                  |        | 
*                  _|      |                  |       _|
*                /   \     |                  |     /   \
*               |    |     |                  |    |    |
*               \___/      |                  |    \___/
* 
* 3.Both of the linked list have loop, they may intersect or not.
*        intersect1              intersect2              not intersect
*          h1  h2                 h1     h2               h1       h2
*          |   |                  |      |                |        |   
*          \  /                   |      |                |        |
*          _|                     \_____/                _|       _|
*        /   \                   /      \              /   \    /   \
*       |    |                  |       |             |    |   |    |
*       \___/                   \______/              \___/    \___/
* 
* Conclusion:
* 1.Check how many linked lists have loop.
* 2.If none, then goto case 1
* 3.If one has loop and the other doesn't goto case 2
* 4.If both of them have loop, goto case 3
*/

/*
*SubProblem: How to check there is a loop in linked list and return the first node in loop?
*Solution:
* 1.To check loop, we use a slow pointer which goes one node per step and a fast pointer which
*   goes two nodes per step, if:
*    1.1.Fast pointer goes to the tail of the linked list, there is no loop
*    1.2.Fast pointer meets slow pointer, there is a loop
* 2.To get the first node in loop, we start at case 1.2. When fast pointer meets slow pointer, we
*   abandon the fast pointer, make another slow pointer start at head. when the old slow pointer
*   meets the new slow pointer, the node is the first node of loop.
*   Proof: 
*   Assume there are k nodes outside of loop, and m nodes in the loop.
* 
*              ---k----   ---m---
*             |       |  |  o-o |
*             |       |  |/    \|
*             o-o-...-o-o       o 
*                        \     /
*                         o...o
* 
*   When the slow pointer enters the loop, slow point has passed k nodes, and fast pointer has 
*   passed 2*k nodes in the linked list. This means fast pointer has entered the loop and passed 
*   k nodes in the loop. Thus, if we note the first node in the loop as position 0, the fast pointer 
*   is at position k%m. The distance between slow pointer and fast pointer is m-k%m, means that 
*   the fast pointer has to go m-k%m steps to meet the slow pointer.
* 
*              slow at 0    o-o 
*                      \  /    \
*             o-o-...-o-o       o 
*                       |\     /
*                       | o...o <- fast at k%m
*                       |     | 
*                       |-----|
*                          ^
*                          |
*                       distance is m-k%m
* 
*   When they meet each other, the slow pointer is at position m-k%m.
* 
*                           o-o 
*                         /    \
*             o-o-...-o-o       o <- fast meets slow at m-k%m
*                        \     /
*                         o...o
*  
*   Then we abandon the fast pointer and make another slow pointer start at the head.
* 
*        slow'              o-o 
*            \            /    \
*             o-o-...-o-o       o <- slow at m-k%m
*                        \     /
*                         o...o
*   
*   It will take the new slow pointer to pass k nodes to enter the loop, meanwhile the 
*   old slow pointer will also pass k nodes and be at the position (k+m-k%m)%m == 0.
* 
*                  slow'    o-o 
*                      \  /    \
*             o-o-...-o-o       o
*                      / \     /
*                    /    o...o
*            slow at (k+m-k%m)%m == 0 
* 
*   Proof done!
* 3.Algorithm of step 2 doesn't work for circular linked list. To fix it, we have to compare
*   the new slow pointer with head everytime to avoid infinite looping. Because the new slow
*   pointer will never catch up with the old slow pointer in circular linked list. Thus, if 
*   the new slow pointer equals to head, which means this is a circular linked list, return 
*   any node in the linked list is ok.
*/

Node *GetFirstNodeInLoop(Node *head) {
	if (head == NULL) {
		return NULL;
	}
	Node *slow = head;
	Node *fast = head->next;
	while (slow != fast) {
		if (fast == NULL || fast->next == NULL) {
			//A regular linked list
			return NULL;
		}
		slow = slow->next;
		fast = fast->next->next;
	}
	//OK, we got a loop
	Node *cur = head;
	//avoid infinite loop in circular linked list
	while (cur != slow && cur != head) { 
		cur = cur->next;
		slow = slow->next;
	}
	return cur;
}

/*
*Subproblem: How to check two regular linked list intersect? How to find the first node in
*intersection?
*/
/*
*Solution: If two regular linked list intersect, they will share the same last node. Assume
*Linkedlist1's length is n, Linkedlist's length is m, and n > m. Set one pointer start at the
*(n-m)th node of Linkedlist1 and another pointer start at the head of Linkedlist2. Two pointers
*go down together and check if they equal to each other, then we will find the first node in
*intersection.
*/

Node * GetFirstNodeInRegularIntersection(Node *head_a, Node *head_b) {
	return GetFirstNodeInIntersectionNoLoop(head_a, head_b, NULL);
}

Node * GetFirstNodeInIntersectionNoLoop(Node *head_a, Node *head_b, Node *tail) {
	if(head_a == NULL || head_b == NULL) {
		return NULL;
	}
	//Calculate length and find the last node of head_a
	Node *cur_a = head_a;
	Node *pre_a = NULL;
	size_t len_a = 0;
	while (cur_a != tail) {
		len_a++;
		pre_a = cur_a;
		cur_a = cur_a->next;
	}
	//Calculate length and find the last node of head_b
	Node *cur_b = head_b;
	Node *pre_b = NULL;
	size_t len_b = 0;
	while (cur_b != tail) {
		len_b++;
		pre_b = cur_b;
		cur_b = cur_b->next;
	}
	//not intersect
	if (pre_a != pre_b) { 
		return NULL;
	}
	//intersect
	Node *cur_a = head_a;
	Node *cur_b = head_b;
	size_t diff = abs(len_a - len_b);
	Node **temp = len_a >= len_b ? &cur_a : &cur_b;
	for (size_t i = 0; i < diff; i++) {
		(*temp) = (*temp)->next;
	}
	while (cur_a != cur_b) {
		cur_a = cur_a->next;
		cur_b = cur_b->next;
	}
	return cur_a;
}

/*
* Subproblem: How to check two linked list with loop intersect? How to find the first node in
* intersection?
*/
/*
* Solution: If two linked list with loop intersect, they will share the same loop. We compare
* the first node in loop. If they are the same, that's intersect1, we can reuse the algorithm 
* of finding the first nodes in intersection of two regular linked list. If they are not the
* same node, that's intersect2 or not intersect. We can start at one first node, see if we can
* reach another node. If we can, that is intersect2, return either first node is ok. If we can't
* that is not intersect.
*/

Node * GetFirstNodeInLoopIntersection(Node *head_a, Node *first_a, Node *head_b, Node *first_b) {
	Node *ret = NULL;
	if (first_a == first_b) { //intersect1
		ret = GetFirstNodeInIntersectionNoLoop(head_a, head_b, first_a);
		if (ret == NULL) {
			return first_a;
		} else {
			return ret;
		}
	} else {
		Node *cur = first_a;
		do {
			cur = cur->next;
		} while (cur != first_a && cur != first_b);
		if (cur == first_a) { //not intersect
			return NULL;
		} else { //intersect2
			return first_a;
		}
	}
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
