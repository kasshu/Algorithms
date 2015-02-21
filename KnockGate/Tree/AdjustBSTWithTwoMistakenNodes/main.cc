/*Adjust bst problem:
*There are 2 wrongly placed nodes in given bst.
*Find them and check if this bst can be repaired by
*swapping them.
*Note:
*1.If there are more than 2 nodes wrong, just give up.
*2.If there are less than 2 nodes wrong, just give up.
*3.Swap the 2 nodes may not repair the bst.
*e.g.
*             4           
*           /   \         swap 2 and 6 will repair this bst
*         6      2        
*       /   \   /  \       \
*     1      3 5    7  
*
*/

#include "stdio.h"
#include <queue>
#include <vector>
using namespace std;

struct Node {
	Node (int value):left(NULL),right(NULL),val(value) {}
	Node *left;
	Node *right;
	int val;
};

void print_tree_inorder (Node *root) {
	if (root == NULL) {
		return;
	}
	print_tree_inorder(root->left);
	printf("%d ",root->val);
	print_tree_inorder(root->right);
}

void print_tree(Node *root) {
	print_tree_inorder(root);
	printf("\n");
}

void release_tree (Node *root) {
	if (root == NULL) {
		return;
	}
	release_tree(root->left);
	release_tree(root->right);
	delete root;
}

Node *build_tree(int *arr, int len) {
	if (arr == NULL || len == 0) {
		return NULL;
	}
	Node *root = new Node(arr[0]);
	for (int i = 1; i < len; i++) {
		Node *node = new Node(arr[i]);
		Node *cur = root;
		Node **insert = NULL;
		while (cur != NULL) {
			if (cur->val > node->val) {
				insert = &(cur->left);
				cur = cur->left;
			} else {
				insert = &(cur->right);
				cur = cur->right;
			}
		}
		*insert = node;
	}
	return root;
}

void PrintByLevel (Node *root) {
	if (root == NULL) {
		return;
	}
	queue<Node *> q;
	q.push(root);
	while (!q.empty()) {
		Node *temp = q.front();
		if (temp->left != NULL) {
			q.push(temp->left);
		}
		if (temp->right != NULL) {
			q.push(temp->right);
		}
		printf("%d ", temp->val);
		q.pop();
	}
	printf("\n");
}

/*
*Solution:
*1.First, we have to find how many nodes are wrongly placed.
*2.Second, find the first mistake node and the second.
*3.Swap them.
*Cost: Time-O(n), Space:O(h)
*/

/*
*Sub-Solution: How to count?
*We can use morris-in-order traverse to visit all the nodes in given
*tree non-recursively and use local variables to check the order of
*sequence. If we find a inverse-order pair, we will count one.
*e.g.
*             4           
*           /   \         swap 2 and 6 will repair this bst
*         6      2        
*       /   \   /  \      6 and 2 break rule 2 times 
*     1      3 5    7  
*
*             5           
*           /   \         swap 4 and 5 will repair this bst
*         2      6        
*       /   \   /  \      5 break rule 1 time 
*     1      3 4    7  
*
*             3           
*           /   \         swap 4 and 2 will not repair this bst
*         4      6        
*       /   \   /  \      4 break rule 1 time 
*     1      2 5    7  
*
*As you can see, 1 or 2 inverse-pair may be repaired by swap 2 mistaken nodes.
*If there are more than 2 inverse-pair, you can never repair this bst by swap 
*2 nodes.
*Cost: Time-O(n), Space:O(1)
*/

int CountMistakenNodes(Node *root) {
	Node *cur = root;
	Node *pre = NULL;
	int counter = 0;
	while (cur != NULL) {
		if (cur->left != NULL) {
			Node *temp = cur->left;
			while (temp->right != NULL && temp->right != cur) {
				temp = temp->right;
			}
			if (temp->right == NULL) {
				//first time visit
				temp->right = cur;
				cur = cur->left;
			} else {
				//second time visit
				temp->right = NULL;
				if (pre != NULL && pre->val > cur->val) {
					counter++;
				}
				pre = cur;
				cur = cur->right;
			}
		} else {
			if (pre != NULL && pre->val > cur->val) {
				counter++;
			}
			pre = cur;
			cur = cur->right;
		}
	}
	return counter;
}

/*
*Sub-Solution: How to find and check if it can be repaired by swapping?
*We can modify the count algorithm:
*1.If there is only one reverse-order pair, them may be the mistaken nodes.
*2.If there are two reverse-order pairs, the first node in first pair and 
*the second node in second pair may be the mistaken nodes.
*Cost: Time-O(n), Space:O(1)
*/

void FindMistakenNodes(Node *root, int mistaken, int *first, int *second) {
	Node *cur = root;
	Node *pre = NULL;
	int counter = 0;
	while (cur != NULL) {
		if (cur->left != NULL) {
			Node *temp = cur->left;
			while (temp->right != NULL && temp->right != cur) {
				temp = temp->right;
			}
			if (temp->right == NULL) {
				//first time visit
				temp->right = cur;
				cur = cur->left;
			} else {
				//second time visit
				temp->right = NULL;
				if (pre != NULL) {
					if (pre->val > cur->val) {
						if (mistaken == 1) {
							*first = pre->val;
							*second = cur->val;
						} else {
							//should be 2
							if (counter == 0) {
								*first = pre->val;
							} else {
								//should be 1
								*second = cur->val;
							}
						}
						counter++;
					}
				}
				pre = cur;
				cur = cur->right;
			}
		} else {
			if (pre != NULL) {
				if (pre->val > cur->val) {
					if (mistaken == 1) {
						*first = pre->val;
						*second = cur->val;
					} else {
						//should be 2
						if (counter == 0) {
							*first = pre->val;
						} else {
							//should be 1
							*second = cur->val;
						}
					}
					counter++;
				}
			}
			pre = cur;
			cur = cur->right;
		}
	}
}

void GetPreAndSucc(Node *root, int first, int second, vector<Node *> &v) {
	Node *cur = root;
	Node *pre = NULL;
	while (cur != NULL) {
		if (cur->left != NULL) {
			Node *temp = cur->left;
			while (temp->right != NULL && temp->right != cur) {
				temp = temp->right;
			}
			if (temp->right == NULL) {
				//first time visit
				temp->right = cur;
				cur = cur->left;
			} else {
				//second time visit
				temp->right = NULL;
				if (cur->val == first) {
					v[0] = pre;
				} else if (pre != NULL && pre->val == first) {
					v[1] = cur;
				}
				if (cur->val == second) {
					v[2] = pre;
				} else if (pre != NULL && pre->val == second) {
					v[3] = cur;
				}
				pre = cur;
				cur = cur->right;
			}
		} else {
			if (cur->val == first) {
				v[0] = pre;
			} else if (pre != NULL && pre->val == first) {
				v[1] = cur;
			}
			if (cur->val == second) {
				v[2] = pre;
			} else if (pre != NULL && pre->val == second) {
				v[3] = cur;
			}
			pre = cur;
			cur = cur->right;
		}
	}
}

bool Check(int first, int second, const vector<Node *> &v) {
	if (second == v[1]->val) {
		bool result = true;
		if (v[0] != NULL) {
			result &= v[0]->val < second;
		}
		if (v[3] != NULL) {
			result &= v[3]->val > first;
		}
		return result && first > second;
	} else {
		bool result = true;
		if (v[0] != NULL) {
			result &= v[0]->val < second;
		}
		result &= second < v[1]->val;
		if (v[3] != NULL) {
			result &= v[3]->val > first;
		}
		result &= first > v[2]->val;
		return result;
	}
}

/*
*Sub-Solution: How to swap?
*For swap operations, we must remember the parent and children of them.
*In swapping, we must consider these conditions:
*1.One of them is root?
*2.One is the parent of the other
*3.Them are the left or right child of their parent
*In conclusion:
* 1.First node is root and second node is its left child(*This is not going to happen in in-order traverse)
* 2.First node is root and second node is its right child
* 3.Second node is root and first node is its left child
* 4.Second node is root and first node is its right child(*This is not going to happen in in-order traverse)
* 5.No one is root, first node is the left child of its parent and second node is the left child of first(*This is not going to happen in in-order traverse)
* 6.No one is root, first node is the left child of its parent and second node is the right child of first
* 7.No one is root, first node is the right child of its parent and second node is the left child of first(*This is not going to happen in in-order traverse)
* 8.No one is root, first node is the right child of its parent and second node is the right child of first
* 9.No one is root, second node is the left child of its parent and first node is the left child of second
*10.No one is root, second node is the left child of its parent and first node is the right child of second(*This is not going to happen in in-order traverse)
*11.No one is root, second node is the right child of its parent and first node is the left child of second
*12.No one is root, second node is the right child of its parent and first node is the right child of second(*This is not going to happen in in-order traverse)
*13.First node is root, they are not parent-child, second node is the left child of its parent.
*14.First node is root, they are not parent-child, second node is the right child of its parent.
*15.Second node is root, they are not parent-child, first node is the left child of its parent.
*16.Second node is root, they are not parent-child, first node is the right child of its parent.
*17.No one is root, first node is the left child of its parent, second node is the left child of its parent
*18.No one is root, first node is the left child of its parent, second node is the right child of its parent
*19.No one is root, first node is the right child of its parent, second node is the left child of its parent
*20.No one is root, first node is the right child of its parent, second node is the right child of its parent
*Cost: Time-O(n), Space:O(h)
*/

Node * GetParent(Node *root, int val) {
	if (root == NULL) {
		return NULL;
	}
	if (root->left != NULL && root->left->val == val) {
		return root;
	}
	if (root->right != NULL && root->right->val == val) {
		return root;
	}
	Node *parent = GetParent(root->left, val);
	if (parent != NULL) {
		return parent;
	}
	parent = GetParent(root->right, val);
	if (parent != NULL) {
		return parent;
	}
	return NULL;
}

Node * SwapNode(Node *root, int first, int second) {
	Node *first_parent = GetParent(root, first);
	Node *second_parent = GetParent(root, second);
	if (first_parent == NULL) { 
		Node *new_root = NULL;
		if (second_parent->val == first && second_parent->right->val == second) { //case 2
			Node *first_node = second_parent;
			Node *second_node = second_parent->right;
			Node *temp = first_node->left;
			first_node->left = second_node->left;
			first_node->right = second_node->right;
			second_node->right = first_node;
			second_node->left = temp;
			new_root = second_node;
		} else if (second_parent->left->val == second) { //case 13
			Node *first_node = root;
			Node *second_node = second_parent->left;
			Node *temp_left = first_node->left;
			Node *temp_right = first_node->right;
			first_node->left = second_node->left;
			first_node->right = second_node->right;
			second_parent->left = first_node;
			second_node->right = temp_right;
			second_node->left = temp_left;
			new_root = second_node;
		} else if (second_parent->right->val == second) { //case 14
			Node *first_node = root;
			Node *second_node = second_parent->right;
			Node *temp_left = first_node->left;
			Node *temp_right = first_node->right;
			first_node->left = second_node->left;
			first_node->right = second_node->right;
			second_parent->right = first_node;
			second_node->right = temp_right;
			second_node->left = temp_left;
			new_root = second_node;
		}
		//Return the new root, becase we have changed the root
		return new_root;
	} else if (second_parent == NULL) { 
		Node *new_root = NULL;
		if (first_parent->val == second && first_parent->left->val == first) { //case 3
			Node *first_node = first_parent->left;
			Node *second_node = first_parent;
			Node *temp = second_node->right;
			second_node->left = first_node->left;
			second_node->right = first_node->right;
			first_node->left = second_node;
			first_node->right = temp;
			new_root = first_node;
		} else if (first_parent->left->val == first) { //case 15
			Node *first_node = first_parent->left;
			Node *second_node = root;
			Node *temp_left = first_node->left;
			Node *temp_right = first_node->right;
			first_node->left = second_node->left;
			first_node->right = second_node->right;
			first_parent->left = second_node;
			second_node->right = temp_right;
			second_node->left = temp_left;
			new_root = first_node;
		} else if (first_parent->right->val == first) { //case 16
			Node *first_node = first_parent->right;
			Node *second_node = root;
			Node *temp_left = first_node->left;
			Node *temp_right = first_node->right;
			first_node->left = second_node->left;
			first_node->right = second_node->right;
			first_parent->right = second_node;
			second_node->right = temp_right;
			second_node->left = temp_left;
			new_root = first_node;
		}
		//Return the new root, becase we have changed the root
		return new_root;
	} else {
		if (first_parent->left->val == first) {
			if (second_parent->val == first && second_parent->right->val == second) { //case 6
				Node *first_node = first_parent->left;
				Node *second_node = second_parent->right;
				Node *temp_left = first_node->left;
				first_node->left = second_node->left;
				first_node->right = second_node->right;
				first_parent->left = second_node;
				second_node->right = first_node;
				second_node->left = temp_left;
			} else if (first_parent->val == second && second_parent->left->val == second) { //case 9
				Node *first_node = first_parent->left;
				Node *second_node = second_parent->left;
				Node *temp_right = second_node->right;
				second_node->left = first_node->left;
				second_node->right = first_node->right;
				second_parent->left = first_node;
				first_node->right = temp_right;
				first_node->left = second_node;
			} else if (first_parent->val == second && second_parent->right->val == second) { //case 11
				Node *first_node = first_parent->left;
				Node *second_node = second_parent->right;
				Node *temp_right = second_node->right;
				second_node->left = first_node->left;
				second_node->right = first_node->right;
				second_parent->right = first_node;
				first_node->right = temp_right;
				first_node->left = second_node;
			} else if (second_parent->left->val == second) { //case 17
				Node *first_node = first_parent->left;
				Node *second_node = second_parent->left;
				Node *temp_left = second_node->left;
				Node *temp_right = second_node->right;
				second_node->left = first_node->left;
				second_node->right = first_node->right;
				first_parent->left = second_node;
				first_node->left = temp_left;
				first_node->right = temp_right;
				second_parent->left = first_node;
			} else if (second_parent->right->val == second) { //case 18
				Node *first_node = first_parent->left;
				Node *second_node = second_parent->right;
				Node *temp_left = second_node->left;
				Node *temp_right = second_node->right;
				second_node->left = first_node->left;
				second_node->right = first_node->right;
				first_parent->left = second_node;
				first_node->left = temp_left;
				first_node->right = temp_right;
				second_parent->right = first_node;
			}
		} else { //first_parent->right->val == first
			Node *first_node = first_parent->right;
			if (second_parent->val == first && second_parent->right->val == second) { //case 8
				Node *second_node = second_parent->right;
				Node *temp_left = first_node->left;
				first_node->left = second_node->left;
				first_node->right = second_node->right;
				first_parent->right = second_node;
				second_node->right = first_node;
				second_node->left = temp_left;
			} else if (second_parent->left->val == second) { //case 19
				Node *second_node = second_parent->left;
				Node *temp_left = second_node->left;
				Node *temp_right = second_node->right;
				second_node->left = first_node->left;
				second_node->right = first_node->right;
				first_parent->right = second_node;
				first_node->left = temp_left;
				first_node->right = temp_right;
				second_parent->left = first_node;
			} else if (second_parent->right->val == second) { //case 20
				Node *second_node = second_parent->right;
				Node *temp_left = second_node->left;
				Node *temp_right = second_node->right;
				second_node->left = first_node->left;
				second_node->right = first_node->right;
				first_parent->right = second_node;
				first_node->left = temp_left;
				first_node->right = temp_right;
				second_parent->right = first_node;
			}
		}
		return root;
	}
}

//function
Node * FindMistakenNodesAndRepair(Node *root) {
	int mistaken = CountMistakenNodes(root);
	if (mistaken == 0) {
		printf("This is a good BST, no mistaken node.\n");
		return root;
	} else if (mistaken > 2) {
		printf("There are %d nodes mistaken in tree, can't be repaired by swap 2 mistaken nodes\n", mistaken);
		return root;
	}
	printf("There are %d nodes mistaken in tree, try to repair it\n", mistaken);
	int first, second;
	FindMistakenNodes(root, mistaken, &first, &second);
	printf("Two nodes are: %d and %d\n", first, second);
	vector<Node *> v;
	v.resize(4, NULL);
	GetPreAndSucc(root, first, second, v);
	if (!Check(first, second, v)) {
		printf("Cannot be repair be swapping 2 mistaken nodes\n");
		return root;
	}
	return SwapNode(root, first, second);
}

int main(int argc, char *argv[]) {
	{
	printf("case: no mistaken nodes\n");
	int a[] = {4,2,6,1,3,5,7};
	Node *root = build_tree(a, sizeof(a)/sizeof(int));
	print_tree(root);
	root = FindMistakenNodesAndRepair(root);
	print_tree(root);
	release_tree(root);
	}
	{
	printf("case: 2\n");
	Node *root = new Node(7);
	root->left = new Node(3);
	root->left->left = new Node(2);
	root->left->left->left = new Node(1);
	root->left->right = new Node(4);
	root->right = new Node(5);
	root->right->left = new Node(6);
	root->right->right = new Node(8);
	print_tree(root);
	root = FindMistakenNodesAndRepair(root);
	print_tree(root);
	release_tree(root);
	}
	{
	printf("case: 3\n");
	Node *root = new Node(3);
	root->left = new Node(5);
	root->left->left = new Node(2);
	root->left->left->left = new Node(1);
	root->left->right = new Node(4);
	root->right = new Node(7);
	root->right->left = new Node(6);
	root->right->right = new Node(8);
	print_tree(root);
	root = FindMistakenNodesAndRepair(root);
	print_tree(root);
	release_tree(root);
	}
	{
	printf("case: 6\n");
	Node *root = new Node(4);
	root->left = new Node(3);
	root->left->left = new Node(1);
	root->left->right = new Node(2);
	root->right = new Node(6);
	root->right->left = new Node(5);
	root->right->right = new Node(7);
	print_tree(root);
	root = FindMistakenNodesAndRepair(root);
	print_tree(root);
	release_tree(root);
	}
	{
	printf("case: 8\n");
	Node *root = new Node(4);
	root->left = new Node(2);
	root->left->left = new Node(1);
	root->left->right = new Node(3);
	root->right = new Node(7);
	root->right->left = new Node(5);
	root->right->right = new Node(6);
	print_tree(root);
	root = FindMistakenNodesAndRepair(root);
	print_tree(root);
	release_tree(root);
	}
	{
	printf("case: 9\n");
	Node *root = new Node(4);
	root->left = new Node(1);
	root->left->left = new Node(2);
	root->left->right = new Node(3);
	root->right = new Node(6);
	root->right->left = new Node(5);
	root->right->right = new Node(7);
	print_tree(root);
	root = FindMistakenNodesAndRepair(root);
	print_tree(root);
	release_tree(root);
	}
	{
	printf("case: 11\n");
	Node *root = new Node(4);
	root->left = new Node(2);
	root->left->left = new Node(1);
	root->left->right = new Node(3);
	root->right = new Node(5);
	root->right->left = new Node(6);
	root->right->right = new Node(7);
	print_tree(root);
	root = FindMistakenNodesAndRepair(root);
	print_tree(root);
	release_tree(root);
	}
	{
	printf("case: 13\n");
	Node *root = new Node(5);
	root->left = new Node(2);
	root->left->left = new Node(1);
	root->left->right = new Node(3);
	root->right = new Node(6);
	root->right->left = new Node(4);
	root->right->right = new Node(7);
	print_tree(root);
	root = FindMistakenNodesAndRepair(root);
	print_tree(root);
	release_tree(root);
	}
	{
	printf("case: 14\n");
	Node *root = new Node(7);
	root->left = new Node(2);
	root->left->left = new Node(1);
	root->left->right = new Node(3);
	root->right = new Node(6);
	root->right->left = new Node(5);
	root->right->right = new Node(4);
	print_tree(root);
	root = FindMistakenNodesAndRepair(root);
	print_tree(root);
	release_tree(root);
	}
	{
	printf("case: 15\n");
	Node *root = new Node(1);
	root->left = new Node(2);
	root->left->left = new Node(4);
	root->left->right = new Node(3);
	root->right = new Node(6);
	root->right->left = new Node(5);
	root->right->right = new Node(7);
	print_tree(root);
	root = FindMistakenNodesAndRepair(root);
	print_tree(root);
	release_tree(root);
	}
	{
	printf("case: 16\n");
	Node *root = new Node(3);
	root->left = new Node(2);
	root->left->left = new Node(1);
	root->left->right = new Node(4);
	root->right = new Node(6);
	root->right->left = new Node(5);
	root->right->right = new Node(7);
	print_tree(root);
	root = FindMistakenNodesAndRepair(root);
	print_tree(root);
	release_tree(root);
	}
	{
	printf("case: 17\n");
	Node *root = new Node(4);
	root->left = new Node(5);
	root->left->left = new Node(1);
	root->left->right = new Node(3);
	root->right = new Node(6);
	root->right->left = new Node(2);
	root->right->right = new Node(7);
	print_tree(root);
	root = FindMistakenNodesAndRepair(root);
	print_tree(root);
	release_tree(root);
	}
	{
	printf("case: 18\n");
	Node *root = new Node(4);
	root->left = new Node(7);
	root->left->left = new Node(1);
	root->left->right = new Node(3);
	root->right = new Node(6);
	root->right->left = new Node(5);
	root->right->right = new Node(2);
	print_tree(root);
	root = FindMistakenNodesAndRepair(root);
	print_tree(root);
	release_tree(root);
	}
	{
	printf("case: 19\n");
	Node *root = new Node(4);
	root->left = new Node(2);
	root->left->left = new Node(6);
	root->left->right = new Node(3);
	root->right = new Node(1);
	root->right->left = new Node(5);
	root->right->right = new Node(7);
	print_tree(root);
	root = FindMistakenNodesAndRepair(root);
	print_tree(root);
	release_tree(root);
	}
	{
	printf("case: 20\n");
	Node *root = new Node(4);
	root->left = new Node(2);
	root->left->left = new Node(1);
	root->left->right = new Node(6);
	root->right = new Node(3);
	root->right->left = new Node(5);
	root->right->right = new Node(7);
	print_tree(root);
	root = FindMistakenNodesAndRepair(root);
	print_tree(root);
	release_tree(root);
	}
	{
	printf("case: can't repair\n");
	Node *root = new Node(3);
	root->left = new Node(4);
	root->left->left = new Node(1);
	root->left->right = new Node(2);
	root->right = new Node(6);
	root->right->left = new Node(5);
	root->right->right = new Node(7);
	print_tree(root);
	root = FindMistakenNodesAndRepair(root);
	print_tree(root);
	release_tree(root);
	}
}
