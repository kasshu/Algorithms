/*SortWithStack problem:
*Sort a stack with a helper stack
*/

#include "stdio.h"
#include <stack>

/*
*Solution:
*Simulate insertion sort, keep helper stack in sorted order
*Cost: Time-O(n^2), Space:O(n)
*/

void insertion_sort(std::stack<int> &data) {
	if (data.empty() || data.size() == 1) {
		return;
	}
	std::stack<int> helper;
	int val = data.top();
	data.pop();
	helper.push(val);
	while (!data.empty()) {
		val = data.top();
		data.pop();
		if (val >= helper.top()) {
			helper.push(val);
		} else {
			while (helper.top() >val) {
				int temp = helper.top();
				helper.pop();
				data.push(temp);
			}
			helper.push(val);
		}
	}
	while (!helper.empty()) {
		val = helper.top();
		helper.pop();
		data.push(val);
	}
}

/*
*Alternative solution: more computation less space
*Simulate selection sort, select min in stack and push it into helper stack
*Cost: Time-O(n^2), Space:O(n)
*/

void selection_sort(std::stack<int> &data) {
	if (data.empty() || data.size() == 1) {
		return;
	}
	std::stack<int> helper;
	int sentinel = 0;
	int len = data.size();
	while (sentinel < len) {
		int min = data.top();
		data.pop();
		while (!data.empty()) {
			int val = data.top();
			data.pop();
			if (val < min) {
				helper.push(min);
				min = val;
			} else {
				helper.push(val);
			}
		}
		while (helper.size() > sentinel) {
			int val = helper.top();
			helper.pop();
			data.push(val);
		}
		helper.push(min);
		sentinel++;
	}
	while (!helper.empty()) {
		int val = helper.top();
		helper.pop();
		data.push(val);
	}
}

int main(int argc, char *argv[]) {
	//Test of insertion sort
	std::stack<int> s;
	s.push(3);
	s.push(4);
	s.push(5);
	s.push(3);
	s.push(2);
	s.push(1);
	insertion_sort(s);
	printf("After sort:\n");
	while (!s.empty()) {
		printf("%d\n",s.top());
		s.pop();
	}
	//Test of insertion sort
	s.push(3);
	s.push(4);
	s.push(5);
	s.push(3);
	s.push(2);
	s.push(1);
	selection_sort(s);
	printf("After sort:\n");
	while (!s.empty()) {
		printf("%d\n",s.top());
		s.pop();
	}
	return 0;
}
