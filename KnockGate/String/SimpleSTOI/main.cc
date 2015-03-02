/*Simple stoi problem:
*Implement simple stoi function.
*Input: String
*Output: int value or print "can not convert" if out of range or string is invalid
*/

#include "stdio.h"
#include <string>
#include <limits>
using namespace std;

/*
*Solution:
*This is a straight forward problem, but we must take care of some cases:
*1.Input string length is larger than int max or int min
*2.'-' can only occur at the beginning of string.
*3.'0' should not be the first digit in string unless there are only one charactor '0' in it.
*Cost: Time-O(n), Space:O(1)
*/

bool isValid(const string &s) {
	//case 1: empty string
	if (s.length() == 0) {
		return false;
	}
	//case 2: not all char is 0~9
	size_t pos = 0;
	if (s[0] == '-') {
		pos = 1;
	}
	for (size_t i = pos; i < s.length(); i++) {
		if (s[i] < '0' || s[i] > '9') {
			return false;
		}
	}
	//case 3: 0.+ is invalid
	if (s.length() > 1 && s[0] == '0') {
		return false;
	}
	//case 4: -0.* is invalid
	if (pos > 0 && s[pos] == '0') {
		return false;
	}
	return true;
}

int SimpleSTOI(const string &s) {
	if (!isValid(s)) {
		printf("Can not convert\n");
		return 0;
	}
	int result = 0;
	if (s[0] == '-') {
		//negative
		for (size_t i = 1; i < s.length(); i++) {
			int add = s[i] - '0';
			if (result < numeric_limits<int>::min() / 10
				|| (result == numeric_limits<int>::min() / 10 && 0 - add < numeric_limits<int>::min() % 10)) {
				printf("Can not convert\n");
				return 0;
			}
			result = result * 10 - add;
		}
	} else {
		//positive
		for (size_t i = 0; i < s.length(); i++) {
			int add = s[i] - '0';
			if (result > numeric_limits<int>::max() / 10
				|| (result == numeric_limits<int>::max() / 10 && add > numeric_limits<int>::max() % 10)) {
				printf("Can not convert\n");
				return 0;
			}
			result = result * 10 + add;
		}
	}
	return result;
}

int main(int argc, char *argv[]) {
	{
		string s = "2147483647";
		printf("%s is %d\n", s.c_str(), SimpleSTOI(s));
	}
	{
		string s = "2147483648";
		printf("%s is %d\n", s.c_str(), SimpleSTOI(s));
	}
	{
		string s = "-2147483648";
		printf("%s is %d\n", s.c_str(), SimpleSTOI(s));
	}
	{
		string s = "-2147483649";
		printf("%s is %d\n", s.c_str(), SimpleSTOI(s));
	}
}
