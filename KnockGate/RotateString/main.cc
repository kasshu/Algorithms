/*Rotate string problem:
*e.g. abcdefg -> defgabc 
*
*/

#include "stdio.h"
#include "inttypes.h"

/*solution 1: using reverse string*/
void reverse_string(char *begin, char *end) {
	if(begin == NULL || end == 0 || begin >= end) {
		return;
	}
	while (end > begin) {
		char temp = *begin;
		*begin = *end;
		*end = temp;
		begin++;
		end--;
	}
}

void rotate_string_by_reverse(char *str, uint32_t len, uint32_t pos) {
	if(str == NULL || len == 0 || pos >= len) {
		return;
	}
	reverse_string(str, str+pos);
	reverse_string(str+pos+1, str+len-1);
	reverse_string(str, str+len-1);
}

/*solution 2: swapping short part to the end*/
void swap(char *begin1, char *end1, char *begin2) {
	while(begin1 <= end1) {
		char temp = *begin1;
		*begin1 = *begin2;
		*begin2 = temp;
		begin1++;
		begin2++;
	}
}

void swap_short_part(char *buf, uint32_t len, uint32_t pos) {
	if(buf == NULL || len == 0 || pos >= len) {
		return;
	}
	uint32_t left = pos+1;
	uint32_t right = len-left;
	char *begin1, *end1, *begin2;
	if(left < right) {
		begin1 = buf;
		end1 = buf + pos;
		begin2 = buf + len - left;
		swap(begin1,end1,begin2);
		swap_short_part(buf, right, pos);
	} else if(left > right) {
		begin1 = buf;
		end1 = buf + right - 1;
		begin2 = buf + left;
		swap(begin1,end1,begin2);
		swap_short_part(buf+right, left, left-right-1);
	} else { //left == right
		begin1 = buf;
		end1 = buf + pos;
		begin2 = buf + left;
		swap(begin1,end1,begin2);
	}
}

int main(int argc, char *argv[]) {
	char str[8] = {'a','b','c','d','e','f','g','\0'};
	//rotate_string_by_reverse(str,7,2);
	swap_short_part(str,7,2);
	printf("after rotate:%s\n",str);
	return 0;
}
