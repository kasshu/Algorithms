/*Tree two is subtree of tree one problem:
*Given two binary trees, check out whether tree two is tree one's subtree.
*Do it as quickly as possible.
*e.g.
*         Tree One                Tree Two
*             1                       2
*           /   \                   /   \
*         2      3                 4     5
*       /  \    /  \              / \   /
*     4     5  6    7            8   9 10
*   /  \   /
*  8    9 10
*Tree two is subtree of tree one.                    
*
*         Tree One                Tree Two
*             1                       2
*           /   \                   /   \
*         2      3                 4     5
*       /  \    /  \              /
*     4     5  6    7            8
*   /  \   /
*  8    9 10
*Tree two is not subtree of tree one.                    
*/

#include "stdio.h"
#include <queue>
#include <vector>
#include <string>
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
*We can modify the contains topology algoithm, which time cost in O(n*m).
*But that is not quickly enough. We can serialize tree one and tree two into
*strings. Note that a serialized subtree is a sub-string of of the whole
*serialized string. This problem becomes to a sub-string match problem,
*then we use KMP algorithm to process it within O(n+m) time.
*Note: We should use # to present the NULL pointer of leaf nodes to prevent
*wrong sub-string matches.
*e.g.
*         Tree One                Tree Two
*             1                       1
*           /   \                   /   
*         2      3                 2    
*       /  \    /  \              / 
*     4     5  6    7            4    
*   /  \   /
*  8    9 10
*Pre-Order-Serialize:(is sub-string)
*      12489510367                  124
*Tree two is not subtree of tree one, but a sub-string of serialized string
*if you don't use # to present the NULL pointer of leaf node.                
*Pre-Order-Serialize-With-#:(not sub-string)
*1248##9##510###36##7##            124####
*Cost: Time-O(n+m), Space:O(n+m)
*/

void SerializeTree(Node *root, string &s) {
	if (root == NULL) {
		s += "#";
		return;
	}
	s += to_string(root->val);
	SerializeTree(root->left, s);
	SerializeTree(root->right, s);
}

//KMP
/*
*e.g. of GenerateNextArray function
*
*                           i
*      A  B  C  D  A  B  D  E
*     -1  0  0  0  0  1  2  ?
*            k           j
*      k'    j'
*
*since s[i-1] != s[k], we will try another suffix/prefix, that's k' and j'
*and k' is less than 0, we should stop and fill next[i] with 0.
*Note:
*1.Why compare s[i-1] with s[k]?
*  Becase k is the max length of same prefix and suffix between 0 and i-2, which
*  means 0...k-1 and i-k-1...i-2 are the same, if we want to enlarge them, we 
*  should compare k and i-1.
*2.Why next try is j=k and k=next(k)?
*  Since 0...k-1 and i-k-1...i-2 is the same, if s[i-1] != s[k], then we should
*  try shorter one. Since 0...next(k)-1 and k-next(k)-1...k is the same, there
*  should be i-next(k)-1...i-2 is the same as 0...next(k)-1. That is what we want
*  to try next.
*3.Why next[0]=-1 and next[1]=0?
*  Becase next array stands for the max length of prefix and suffix before current
*  char. There is nothing before s[0] and we need a sentinel value, so next[0]=-1.
*  And there is only one char before s[1], no prefix and suffix exists, so next[1]=0.
*/
void GenerateNextArray(const string &s, vector<int> &next) { //assume arr has the same length with string s
	int len = s.length();
	if (len == 0) {
		return;
	} else if (len == 1) {
		next.resize(1, 0);
		next[0] = -1;
		return;
	}
	next.resize(len, 0);
	next[0] = -1;
	next[1] = 0;
	if (len == 2) {
		return;
	}
	for (int i = 2; i < s.length(); i++) {
		int j = i - 1;
		int k = next[j];
		while (k >= 0) {
			if (s[k] == s[i - 1]) {
				next[i] = next[j] + 1;
				break;
			}
			j = k;
			k = next[k];
		}
	}
}

int KMPMatch(const string &s, const string &p) {
	int pos = -1;
	if (p.length() <= s.length()) {
		vector<int> next;
		GenerateNextArray(p, next);
		int slen = s.length();
		int plen = p.length();
		int i = 0, j = 0;
		while (slen - i - 1 > plen - j - 1) {
			if (s[i] == p[j]) {
				++i;
				++j;
				if (j == plen) {
					pos = i - plen;
					break;
				}
			} else {
				j = next[j];
				if (j < 0) {
					++i;
					j = 0;
				}
			}
		}
	}
	return pos;
}

bool IsSubtree(Node *root1, Node *root2) {
	if (root2 == NULL) {
		return true;
	} else if (root1 == NULL) {
		return false;
	}
	string s1, s2;
	SerializeTree(root1, s1);
	SerializeTree(root2, s2);
	printf("First tree:%s\n", s1.c_str());
	printf("Second tree:%s\n", s2.c_str());
	return KMPMatch(s1, s2) != -1;
}

int main(int argc, char *argv[]) {
	Node *root1 = new Node(1);
	root1->left = new Node(2);
	root1->left->left = new Node(4);
	root1->left->left->left = new Node(8);
	root1->left->left->right = new Node(9);
	root1->left->right = new Node(5);
	root1->left->right->left = new Node(10);
	root1->right = new Node(3);
	root1->right->left = new Node(6);
	root1->right->right = new Node(7);
	printf("Tree 1:");
	PrintByLevel(root1);
	Node *root2 = new Node(2);
	root2->left = new Node(4);
	root2->left->left = new Node(8);
	root2->right = new Node(5);
	printf("Tree 2:");
	PrintByLevel(root2);
	printf("Is tree 2 subtree of tree 1? %s\n", IsSubtree(root1, root2) ? "Yes" : "No");
	Node *root3 = new Node(2);
	root3->left = new Node(4);
	root3->left->left = new Node(8);
	root3->left->right = new Node(9);
	root3->right = new Node(5);
	root3->right->left = new Node(10);
	printf("Tree 3:");
	PrintByLevel(root3);
	printf("Is tree 3 subtree of tree 1? %s\n", IsSubtree(root1, root3) ? "Yes" : "No");
	release_tree(root1);
	release_tree(root2);
	release_tree(root3);
}
