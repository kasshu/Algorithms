/*Anagram problem:
*Given 2 word, check if they are anagrams.
*/

#include "stdio.h"
#include <string>
using namespace std;

/*
*Solution:
*We use hashtable to store the occurence of charactors in one word,
*then parse the other string and decrease the occurence of each 
*charactor. If the all the element in hashtable is 0, they are anagrams.
*Since the range of char is 0~127, we can use array instead of hashtable.
*Cost: Time-O(n), Space:O(128)
*/

bool IsAnagrams(const string &str1, const string &str2) {
	if (str1.length() != str2.length()) {
		return false;
	}
	int hash_array[128] = {0};
	for (size_t i = 0; i < str1.length(); i++) {
		hash_array[str1[i]]++;
	}
	for (size_t i = 0; i < str2.length(); i++) {
		hash_array[str2[i]]--;
	}
	for (size_t i = 0; i < 128; i++) {
		if (hash_array[i] != 0) {
			return false;
		}
	}
	return true;
}

int main(int argc, char *argv[]) {
	{
		string s1 = "abcd";
		string s2 = "dcba";
		printf("%s and %s are anagrams?%s\n", s1.c_str(), s2.c_str(), IsAnagrams(s1, s2) ? "Yes" : "No");
	}
	{
		string s1 = "abcd";
		string s2 = "ddba";
		printf("%s and %s are anagrams?%s\n", s1.c_str(), s2.c_str(), IsAnagrams(s1, s2) ? "Yes" : "No");
	}
	{
		string s1 = "abcd";
		string s2 = "a";
		printf("%s and %s are anagrams?%s\n", s1.c_str(), s2.c_str(), IsAnagrams(s1, s2) ? "Yes" : "No");
	}
}
