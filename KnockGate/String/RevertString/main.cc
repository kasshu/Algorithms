/*Revert string problem:
*Revert the given string in place.
*/

#include "stdio.h"
#include <string>
using namespace std;

/*
*Solution:
*We use 2 pointer, one starts at beginning and another starts at the end.
*Swap them and pointer1 go forward, pointer2 go backward until pointer2 is less than pointer1.
*Cost: Time-O(n), Space:O(1)
*/

void RevertString(string &s) {
	if (s.length() == 0 || s.length() == 1) {
		return;
	}
	size_t begin = 0;
	size_t end = s.length() - 1;
	while (end > begin) {
		char temp = s[begin];
		s[begin] = s[end];
		s[end] = temp;
		begin++;
		end--;
	}
}

int main(int argc, char *argv[]) {
	{
		string s = "abcd";
		printf("original %s\n", s.c_str());
		RevertString(s);
		printf("reverse %s\n", s.c_str());
	}
	{
		string s = "a";
		printf("original %s\n", s.c_str());
		RevertString(s);
		printf("reverse %s\n", s.c_str());
	}
	{
		string s = "";
		printf("original %s\n", s.c_str());
		RevertString(s);
		printf("reverse %s\n", s.c_str());
	}
}
