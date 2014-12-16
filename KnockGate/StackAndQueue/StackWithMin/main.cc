/*StackWithMin problem:
*Implement a stack with min function which cost is O(1)
*/

#include "stdio.h"
#include <stack>

/*
*Solution:
*Use a helper stack to remember min element for every push/pop
*Cost: Time-O(1), Space:O(n)
*1.Top function:return top of data stack
*2.Min function:return top of helper stack
*3.Push function:push element into data stack, compare it with the top of helper stack, push smaller one into the helper stack
*4.Pop function:pop from helper stack discard it and pop from data stack return it
*5.Empty function:return empty() of data stack
*5.Size function:return size() of data stack
*/

class StackWithMin {
private:
	std::stack<int> data_stack;
	std::stack<int> helper_stack;
public:
	int top() {
		return data_stack.top();
	}
	int min() {
		return helper_stack.top();
	}
	bool isEmpty() {
		return data_stack.empty();
	}
	size_t size() {
		return data_stack.size();
	}
	void push(int val) {
		data_stack.push(val);
		if (helper_stack.empty()) {
			helper_stack.push(val);
		} else {
			int min = helper_stack.top();
			if (val < min) {
				helper_stack.push(val);
			} else {
				helper_stack.push(min);
			}
		}
	}
	void pop() {
		data_stack.pop();
		helper_stack.pop();
	}
};

/*
*Alternative solution: more computation less space
*Use a helper stack to remember min element for every push/pop
*Cost: Time-O(1), Space:O(n)
*1.Top function:return top of data stack
*2.Min function:return top of helper stack
*3.Push function:push element into data stack, compare it with the top of helper stack, if it is equal or smaller push it
*4.Pop function:compare the top of data stack and helper stack if equal pop helper stack, then pop from data stack return it
*5.Empty function:return empty() of data stack
*5.Size function:return size() of data stack
*/

class StackWithMinAlternative {
private:
	std::stack<int> data_stack;
	std::stack<int> helper_stack;
public:
	int top() {
		return data_stack.top();
	}
	int min() {
		return helper_stack.top();
	}
	bool isEmpty() {
		return data_stack.empty();
	}
	size_t size() {
		return data_stack.size();
	}
	void push(int val) {
		data_stack.push(val);
		if (helper_stack.empty()) {
			helper_stack.push(val);
		} else {
			int min = helper_stack.top();
			if (val <= min) {
				helper_stack.push(val);
			}
		}
	}
	void pop() {
		int data = data_stack.top();
		int min = helper_stack.top();
		if (data == min) {
			helper_stack.pop();
		}
		data_stack.pop();
	}
};

int main(int argc, char *argv[]) {
	//Test of StackWithMin
	StackWithMin swm;
	printf("Stack is %s\n", swm.isEmpty()?"empty":"not empty");
	swm.push(3);
	swm.push(4);
	swm.push(5);
	swm.push(3);
	swm.push(2);
	swm.push(1);
	printf("Stack is %s\n", swm.isEmpty()?"empty":"not empty");
	while (!swm.isEmpty()) {
		int val = swm.top();
		int min = swm.min();
		printf("Top is %d, min is %d\n",val,min);
		swm.pop();
	}
	printf("Stack is %s\n", swm.isEmpty()?"empty":"not empty");
	//Test of StackWithMinAlternative
	StackWithMinAlternative swma;
	printf("Stack is %s\n", swma.isEmpty()?"empty":"not empty");
	swma.push(3);
	swma.push(4);
	swma.push(5);
	swma.push(3);
	swma.push(2);
	swma.push(1);
	printf("Stack is %s\n", swma.isEmpty()?"empty":"not empty");
	while (!swma.isEmpty()) {
		int val = swma.top();
		int min = swma.min();
		printf("Top is %d, min is %d\n",val,min);
		swma.pop();
	}
	printf("Stack is %s\n", swma.isEmpty()?"empty":"not empty");
	return 0;
}
