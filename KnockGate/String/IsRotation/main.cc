/*Is rotation problem:
*Given str1 and str2, check if str2 is a rotation of str1.
*e.g.
*str1 = "abcdef"
*str2 = "efabcd"
*str2 is a rotation of str1.
*/

#include "stdio.h"
#include <string>
using namespace std;

/*
*Solution:
*We repeat str1 twice to make str1'. All the rotations of str1 are enumerated as 
*sub-strings in str1'. We check if str2 is a sub-string of str1'.
*Cost: Time-O(n), Space:O(n)
*/

void GenerateNextArray(const string &s, int *next) {
	if (s.length() == 0) {
		return;
	}
	next[0] = -1;
	if (s.length() == 1) {
		return;
	}
	next[1] = 0;
	if (s.length() == 2) {
		return;
	}
	for (int i = 2; i < s.length(); i++) {
		next[i] = 0;
		int j = i - 1;
		int k = next[j];
		if (s[k] == s[i]) {
			next[i] = next[j] + 1;
		} else {
			while (k > 0) {
				j = k;
				k = next[j];
				if (s[k] == s[i]) {
					next[i] = next[j] + 1;
					break;
				}
			}
		}
	}
}

int KMPMatch(const string &s, const string &p) {
	if (p.length() > s.length()) {
		return -1;
	}
	int i = 0;
	int j = 0;
	int *next = new int[p.length()];
	GenerateNextArray(p, next);
	while (i < s.length()) {
		if (s[i] != p[j]) {
			j = next[j];
			if (j < 0) {
				j = 0;
				i++;
			}
		} else {
			i++;
			j++;
			if (j == p.length()) {
				//found
				return i - p.length();
			}
		}
	}
	delete [] next;
	return -1;
}

bool IsRotation(const string &str1, const string &str2) {
	if (str1.length() != str2.length()) {
		return false;
	}
	string temp = str1 + str1;
	return KMPMatch(temp, str2) == -1 ? false : true;
}

int main(int argc, char *argv[]) {
	{
		string s1 = "abcdef";
		string s2 = "efabcd";
		printf("%s is the rotation of %s?%s\n", s2.c_str(), s1.c_str(), IsRotation(s1, s2) ? "Yes" : "No");
	}
}
