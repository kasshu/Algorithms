/*Valid parentheses string problem(basic):
*Given a string, check if it is a valid parentheses string.
*e.g.
*"(())" is valid.
*"(())(" is invalid.
*"(a)" is invalid because there is a 'a' in the string.
*/

#include "stdio.h"
#include <string>
#include <stack>
#include <random>
using namespace std;

/*
*Solution 1:
*We use stack to solve this problem:
*1.If current charactor is '(', push it into the stack.
*2.If current charactor is ')', if stack is empty, return invalid; else pop stack.
*3.If current charactor is not '(' or ')', return invalid.
*4.At the end of the string, if stack is not empty, return invalid; else return valid.
*Cost: Time-O(n), Space:O(n)
*/

bool IsValid1(const string &s) {
	if (s.length() == 0) {
		return true;
	}
	stack<char> sc;
	for (size_t i = 0; i < s.length(); i++) {
		if (s[i] == '(') {
			sc.push(s[i]);
		} else if (s[i] == ')') {
			if (sc.empty()) {
				return false;
			}
			sc.pop();
		} else {
			return false;
		}
	}
	if (!sc.empty()) {
		return false;
	}
	return true;
}

/*
*Solution 2:
*As you can see in solution 1, we don't have to remember every '('. What we need is a
*counter of '('.
*1.If current charactor is '(', counter++.
*2.If current charactor is ')', if counter == 0 , return invalid; else counter--.
*3.If current charactor is not '(' or ')', return invalid.
*4.At the end of the string, if counter is 0, return invalid; else return valid.
*Cost: Time-O(n), Space:O(1)
*/

bool IsValid2(const string &s) {
	if (s.length() == 0) {
		return true;
	}
	int counter = 0;
	for (size_t i = 0; i < s.length(); i++) {
		if (s[i] == '(') {
			counter++;
		} else if (s[i] == ')') {
			if (counter == 0) {
				return false;
			}
			counter--;
		} else {
			return false;
		}
	}
	if (counter != 0) {
		return false;
	}
	return true;
}

/*Advanced problem:
*Get the size of longest valid parentheses subtring in given string.
*e.g.
*"()()()(" is invalid, the size of longest valid parentheses subtring "()()()" is 6.
*/

/*
*Solution 1:
*We check every substring of the given string and find the longest one.
*Cost: Time-O(n^3), Space:O(1)
*/

int GetLengthOfLongestValidParenthesesSubstring1(const string &s) {
	if (s.length() == 0 || s.length() == 1) {
		return 0;
	}
	int max = 0;
	for (size_t i = 0; i < s.length(); i++) {
		for (size_t j = i; j < s.length(); j++) {
			string temp = s.substr(i, j - i + 1);
			if (IsValid2(temp) && temp.length() > max) {
				max = temp.length();
			}
		}
	}
	return max;
}

/*
*Solution 2:
*We modify from solution 2 of basic problem. When counter of '(' becomes to 0, we find 
*a valid parentheses substring, how to make it as long as possible? We set the start 
*point at the beginning or the first '(' after the nearest invalid substring whose counter 
*is less than zero. Why throw the invalid substring away? Because you can't repair them.
*We will use a counter of '(' and a pointer of start, and:
*1.pointer start with 0 and counter start with 0
*2.1.If current charactor is '(', counter++
*2.2.If current charactor is ')', counter--
*2.2.1.If counter is less than 0, set counter to 0 and move pointer to the next element
*2.2.2.If counter is 0, check if i - start + 1 is larger than max 
*2.3.If current charactor is not '(' or ')', set counter to 0 and move pointer to the next element
*Since this algorithm only works when there are more ')'  than '(', we have do it backward and exchange
*'(' and ')'.
*3.do 1~2 backward and exchange '(' and ')'
*Cost: Time-O(n), Space:O(1)
*/

int GetLengthOfLongestValidParenthesesSubstring2(const string &s) {
	if (s.length() == 0 || s.length() == 1) {
		return 0;
	}
	int max = 0;
	//do it forward
	int start = 0;
	int counter = 0;
	for (size_t i = 0; i < s.length(); i++) {
		if (s[i] == '(') {
			counter++;
		} else if (s[i] == ')') {
			counter--;
			if (counter == 0) {
				int len = i - start + 1;
				if (len > max) {
					max = len;
				}
			} else if (counter < 0) {
				counter = 0;
				start = i + 1;
			}
		} else {
			counter = 0;
			start = i + 1;
		}
	}
	//do it backward
	start = s.length() - 1;
	counter = 0;
	for (int i = s.length() -1 ; i >= 0; i--) {
		if (s[i] == ')') {
			counter++;
		} else if (s[i] == '(') {
			counter--;
			if (counter == 0) {
				int len = start - i + 1;
				if (len > max) {
					max = len;
				}
			} else if (counter < 0) {
				counter = 0;
				start = i - 1;
			}
		} else {
			counter = 0;
			start = i - 1;
		}
	}
	return max;
}

void GenerateRandomParenthesesString(string &s, size_t size) {
	s.resize(size);
	random_device rd;
	for (size_t i = 0; i < size; i++) {
		s[i] = (rd() % 2) == 1 ? '(' : ')';
	}
}

/*
*Solution 3:
*We use dynamic programming to solve this problem.
*Define dp[i] is the size of longest valid parentheses substring which ends at s[i].
*1.If s[i] is '(', dp[i] = 0
*2.If s[i] is ')', since dp[i-1] is the size of longest valid parentheses substring ends
*  at s[i-1], we should see if s[i-1 - dp[i-1]] is '('.
*2.1.If it is '(', then dp[i] = dp[i-1] + 2, don't forget add dp[i-1 - dp[i-1] - 1] for 
*    cases like '()()()('.
*2.2.If it is ')', then dp[i] = 0
*Cost: Time-O(n), Space:O(n)
*/

int GetLengthOfLongestValidParenthesesSubstring3(const string &s) {
	if (s.length() == 0 || s.length() == 1) {
		return 0;
	}
	int *dp = new int[s.length()];
	dp[0] = 0;
	for (size_t i = 1; i < s.length(); i++) {
		if (s[i] == '(') {
			dp[i] = 0;
		} else if (s[i] == ')') {
			int j = i - 1 - dp[i - 1];
			if (s[j] == '(') {
				dp[i] = dp[i - 1] + 2;
				if (j - 1 > 0) {
					dp[i] += dp[j - 1];
				}
			} else {
				dp[i] = 0;
			}
		}
	}
	int max = 0;
	for (int i = 0; i < s.length(); i++) {
		if (dp[i] > max) {
			max = dp[i];
		}
	}
	delete [] dp;
	return max;
}

int main(int argc, char *argv[]) {
	{
		string s = "(())";
		printf("%s is %s\n", s.c_str(), IsValid1(s) ? "valid" : "invalid");
		printf("%s is %s\n", s.c_str(), IsValid2(s) ? "valid" : "invalid");
	}
	{
		string s = "(())(";
		printf("%s is %s\n", s.c_str(), IsValid1(s) ? "valid" : "invalid");
		printf("%s is %s\n", s.c_str(), IsValid2(s) ? "valid" : "invalid");
	}
	{
		string s = "(()))";
		printf("%s is %s\n", s.c_str(), IsValid1(s) ? "valid" : "invalid");
		printf("%s is %s\n", s.c_str(), IsValid2(s) ? "valid" : "invalid");
	}
	{
		string s = "((a))";
		printf("%s is %s\n", s.c_str(), IsValid1(s) ? "valid" : "invalid");
		printf("%s is %s\n", s.c_str(), IsValid2(s) ? "valid" : "invalid");
	}
	{
		string s = "()()()(";
		printf("The size of longest valid parentheses of %s is %d\n", s.c_str(), GetLengthOfLongestValidParenthesesSubstring1(s));
		printf("The size of longest valid parentheses of %s is %d\n", s.c_str(), GetLengthOfLongestValidParenthesesSubstring2(s));
		printf("The size of longest valid parentheses of %s is %d\n", s.c_str(), GetLengthOfLongestValidParenthesesSubstring3(s));
	}
	for (int i = 0; i < 1000; i++) {
		string s = "";
		GenerateRandomParenthesesString(s, 100);
		int len1 = GetLengthOfLongestValidParenthesesSubstring1(s);
		int len2 = GetLengthOfLongestValidParenthesesSubstring2(s);
		int len3 = GetLengthOfLongestValidParenthesesSubstring3(s);
		if (len1 != len2) {
			printf("Error:%s, len1=%d, len2=%d\n",s.c_str(), len1, len2);
		}
		if (len1 != len3) {
			printf("Error:%s, len1=%d, len3=%d\n",s.c_str(), len1, len3);
		}
	}
}
