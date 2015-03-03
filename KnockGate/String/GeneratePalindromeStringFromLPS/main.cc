/*Generate palindrome string from LPS problem:
*Given a string and it's Longest Palindrome Subsquence, add as few charactors as
*you can to make this string a Palindrome.
*e.g.
*string: "B1G2TY34I3OPX2S1"
*LPS: "123I321"
*The answer is "B1SG2XPOTY34I43YTOPX2GS1B"
*/

#include "stdio.h"
#include <string>
using namespace std;

/*
*Solution:
*We treat the charactors in LPS as brackets, charactors before pivot are left-brackets,
*charactors after pivot are right-brackets, We process them pair by pair.
*e.g.
*string: "B1G2TY34I3OPX2S1"    length = N
*LPS: "123I321"                length = M
*Outside-FirstPair(1,1):         B to the right, we will get "B1........1B"
*FirstPair(1,1)-SecondPair(2,2): S to the left, G to right, we will get "B1SG2....2GS1B"
*SecondPair(2,2)-ThridPair(3,3): XPO to the left, YT to right, we will get "B1SG2XPOTY3....3YTOPX2GS1B"
*ThridPair(3,3)-Pivot(I):        4 to right, we will get "B1SG2XPOTY34I43YTOPX2GS1B"
*As you can see, the total length of palindrom is 2*N - M, because we have to add N - M charactors into it.
*Cost: Time-O(n), Space:O(1)
*/

void GeneratePalindrome(const string &s, const string &lps, string &result) {
	if (s.length() == 0 || lps.length() == 0 || lps.length() > s.length()) {
		return;
	} else if (s.length() == lps.length()) {
		if (s.compare(lps) == 0) {
			result = lps;
		}
		return;
	}
	result.resize(2 * s.length() - lps.length());
	int lps_begin = -1;
	int lps_end = lps.length();
	int s_begin = 0;
	int s_end = s.length() - 1;
	int r_begin = 0;
	int r_end = result.length() - 1;
	while (lps_end > lps_begin + 1) {
		//copy left part
		size_t bpos = s.find(lps[lps_begin + 1], s_begin);
		while (s_begin < bpos) {
			result[r_begin++] = s[s_begin];
			result[r_end--] = s[s_begin];
			s_begin++;
		}
		//copy right part
		size_t epos = s.rfind(lps[lps_end - 1], s_end);
		while (s_end > epos) {
			result[r_begin++] = s[s_end];
			result[r_end--] = s[s_end];
			s_end--;
		}
		//It's ok if there are only 1 charactor left in lps, we will do the same assignment twice here.
		result[r_begin++] = lps[++lps_begin];
		result[r_end--] = lps[--lps_end];
		s_begin++;
		s_end--;
	}
}

int main(int argc, char *argv[]) {
	{
		string s = "1b2a3b4";
		string lps = "bab";
		string result;
		GeneratePalindrome(s, lps, result);
		printf("%s's palindrome is %s\n", s.c_str(), result.c_str());
	}
	{
		string s = "B1G2TY34I3OPX2S1";
		string lps = "123I321";
		string result;
		GeneratePalindrome(s, lps, result);
		printf("%s's palindrome is %s\n", s.c_str(), result.c_str());
	}
	{
		string s = "1bb4";
		string lps = "bb";
		string result;
		GeneratePalindrome(s, lps, result);
		printf("%s's palindrome is %s\n", s.c_str(), result.c_str());
	}
	{
		string s = "abcd";
		string lps = "b";
		string result;
		GeneratePalindrome(s, lps, result);
		printf("%s's palindrome is %s\n", s.c_str(), result.c_str());
	}
}
