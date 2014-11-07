/*ImplementQueueWithStack problem:
*Implement a queue with stacks
*/

#include "stdio.h"
#include <stack>

/*
*Solution:
*To implement a queue with stacks, you have to use at least 2 stack to simulate the FIFO rule.
*An input stack and an output stack, here are some principals that you must follow:
*1.All input go to input stack
*2.All output come from output stack
*3.You should flush the data from input stack into output stack when the output stack is empty and there is a pop_front request
*4.You can't flush the data from input stack into output stack when the output stack is not empty, this will violate the FIFO rule.
*Cost: Time-O(n), Space:O(n)
*/

class ImplementedQueue {
private:
	std::stack<int> input;
	std::stack<int> output;
	void flush(std::stack<int> &from, std::stack<int> &to) {
		while (!from.empty()) {
			int val = from.top();
			from.pop();
			to.push(val);
		}
	}
public:
	int back() {
		if (input.empty()) {
			flush(output, input);
		}
		return input.top();
	}
	int front() {
		if (output.empty()) {
			flush(input, output);
		}
		return output.top();
	}
	bool empty() {
		return input.empty() && output.empty();
	}
	void push(int val) {
		input.push(val);
	}
	void pop() {
		if (output.empty()) {
			flush(input, output);
		}
		output.pop();
	}
};

int main(int argc, char *argv[]) {
	//Test of insertion sort
	ImplementedQueue iq;
	printf("Queue is empty:%s\n",iq.empty()?"True":"False");
	iq.push(3);
	iq.push(4);
	iq.push(5);
	iq.push(3);
	iq.push(2);
	iq.push(1);
	printf("Queue is empty:%s\n",iq.empty()?"True":"False");
	printf("Queue front:%d\n",iq.front());
	printf("Queue back:%d\n",iq.back());
	while (!iq.empty()) {
		printf("%d\n",iq.front());
		iq.pop();
	}
	return 0;
}
