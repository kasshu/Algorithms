/*ReverseStackByRecursiveFunction problem:
*Reverse a stack with recursive functions only, no other data structures
*/

#include "stdio.h"
#include <stack>

/*
*Solution:
*With a recursive function which gets the last element in a stack, we build our function.
*1.Get the last element
*2.Recursive call
*3.Push the last element
*Cost: Time-O(n^2), Space:O(n)
*/

int GetLastElement(std::stack<int> &s) {
	int val = s.top();
	s.pop();
	if (s.empty()) {
		return val;
	} 
	int last = GetLastElement(s);
	s.push(val);
	return last;
}

void ReverseStack(std::stack<int> &s) {
	if (s.empty()) {
		return;
	}
	int last = GetLastElement(s);
	ReverseStack(s);
	s.push(last);
}

int main(int argc, char *argv[]) {
	std::stack<int> s;
	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);
	s.push(5);
	s.push(6);
	ReverseStack(s);
	printf("After reverse:\n");
	while (!s.empty()) {
		printf("%d\n",s.top());
		s.pop();
	}
	return 0;
}
