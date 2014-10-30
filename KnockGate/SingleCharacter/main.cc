/*Judge if all characters in a string is unique:
*
*/

#include "stdio.h"
#include "inttypes.h"
#include <unordered_set>

/*solution 1: using hash map, running time is O(n)*/
bool isSingle(const char *buf, uint32_t len) {
	if(buf == NULL || len == 0) {
		return true;
	}
	std::unordered_set<char> set;
	for(uint32_t i=0; i<len; i++) {
		if(set.count(buf[i]) != 0) {
			return false;
		}
		set.insert(buf[i]);
	}
	return true;
}

/*solution 2: using heapsort, running space O(1)*/
void swap(char *a, char *b) {
	char temp = *a;
	*a = *b;
	*b = temp;
}

void buildMinHeap(char *buf, uint32_t len) {
	if(buf == NULL || len == 0) {
		return;
	}
	uint32_t offset = 1;
	//pos = i + offset, odd pos is right child, even pos is left child
	//parent = pos, left = 2*pos, right = 2*pos+1
	uint32_t parent = len/2;
	while(parent != 0) {
		uint32_t left = 2*parent;
		uint32_t right = 2*parent+1;
		if(buf[left-offset] < buf[parent-offset]) {
			swap(buf+left-offset, buf+parent-offset);
		}
		if(right<=len && buf[right-offset] < buf[parent-offset]) {
			swap(buf+right-offset, buf+parent-offset);
		}
		parent--;
	}
}

void minHeapify(char *buf, uint32_t len) {
	if(buf == NULL || len == 0) {
		return;
	}
	uint32_t offset = 1;
	//pos = i + offset, odd pos is right child, even pos is left child
	//parent = pos, left = 2*pos, right = 2*pos+1
	uint32_t parent = 1;
	while(parent <= len/2) {
		uint32_t left = 2*parent;
		uint32_t right = 2*parent+1;
		uint32_t min;
		if(right <= len) {
			min = buf[left-offset] > buf[right-offset] ? right : left;
		} else {
			min = left;
		}
		if(buf[parent-offset] > buf[min-offset]) {
			swap(buf+parent-offset, buf+min-offset);
			parent = min;
		} else {
			break;
		}
	}
}

void heapSort(char *buf, uint32_t len) {
	buildMinHeap(buf,len);
	uint32_t heap_size = len;
	while(heap_size > 1) {
		uint32_t last_pos = heap_size - 1;
		swap(buf, buf+last_pos);
		minHeapify(buf, --heap_size);
	}
}

bool judgeAfterSort(char *buf, uint32_t len) {
	for(uint32_t i=0; i<len-1; i++) {
		if(buf[i] == buf[i+1]) {
			return false;
		}
	}
	return true;
}

int main(int argc, char *argv[]) {
	char *dup = "abcda";
	char *single = "abcde";
	bool r1 = isSingle(dup, 5);
	bool r2 = isSingle(single, 5);
	printf("r1:%s\n", r1?"True":"False");
	printf("r2:%s\n", r2?"True":"False");
	char dupp[7] = {'a','b','c','d','a','b','\0'};
	heapSort(dupp,6);
	printf("str:%s\n",dupp );
	bool r3 = judgeAfterSort(dupp, 6);
	printf("r3:%s\n", r3?"True":"False");
	char singlee[7] = {'a','b','c','d','e','f','\0'};
	heapSort(singlee,6);
	printf("str:%s\n",singlee );
	bool r4 = judgeAfterSort(singlee, 6);
	printf("r3:%s\n", r4?"True":"False");
	return 0;
}
