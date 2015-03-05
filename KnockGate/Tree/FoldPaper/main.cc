/*Fold paper problem:
*e.g. Folded for 3 times, the paper should be this:
*
*                    down
*                   /    \
*                 up      down
*                /  \     /    \
*              up  down   up    down
*/

#include "stdio.h"

/*print the full binary tree using function call stack to save memory*/
void print_full_binary_tree_recursively(const int depth, int level, bool is_left) {
	//reach the max depth, do nothing, just return
	if (level == depth || level < 0) {
		return;
	}
	//print them bottom-up
	//in-order traverse, right-child -> this -> left-child
	print_full_binary_tree_recursively(depth, level+1, false);
	if (is_left) {
		printf("up");
	} else {
		printf("down");
	}
	print_full_binary_tree_recursively(depth, level+1, true);
}

void print_result(const int depth) {
	return print_full_binary_tree_recursively(depth, 0, false);
}

int main(int argc, char *argv[]) {
	print_result(3);
	printf("\n");
	print_result(4);
	printf("\n");
	return 0;
}
