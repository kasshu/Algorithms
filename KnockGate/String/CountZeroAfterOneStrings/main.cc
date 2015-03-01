/*Count zero after one problem:
*Given length k, count how many strings consisted of 0 and 1 with length k
*in which if there is a '0', there will be a '1' on left of it.
*e.g.
*k = 1
*2 0-1 strings: '0' and '1', '1' fulfill the condition, return 1.
*k = 2
*4 0-1 strings: '00' '01' '10' and '11', '10' and '11' fulfill the condition, return 2.
*k = 3
*4 0-1 strings: '000' '001' '010' '011' '100' '101' '110' '111', '101' '110' and '111'
*fulfill the condition, return 3.
*/

#include "stdio.h"
#include <string>
#include <vector>
using namespace std;

/*
*Solution 1:
*We will modify the recursive function of producing permutation of 0-1 string with length k.
*1.Return number of possible string instead of print string.
*2.Prune recursive calls that are not proper.
*Cost: Time-O(2^k), Space:O(k)
*/

int CountProcess1(int k, int step, char pre) {
	if (k <= 0) {
		return 0;
	}
	if (step == k) {
		return 1;
	}
	if (pre == '1') {
		return CountProcess1(k, step + 1, '1') + CountProcess1(k, step + 1, '0');
	}
	return CountProcess1(k, step + 1, '1');
}

/*
*Solution 2:
*Draw a picture of solution 1, we will get:
*
*start:                0
*                     /
*k = 1:             __1__
*                  /     \
*k = 2:          _1_      0
*               /   \    /
*k = 3:        1     0  1
*             / \   /  / \
*k = 4:      1   0 1  1   0
*...
*
*As you can see, define k and counter0(k) and counter1(k), we will get the recursive formula:
*counter0(k+1) = counter1(k)
*counter1(k+1) = counter0(k) + counter1(k)
*And we start at counter0(0) = 1 and counter1(0) = 0
*Cost: Time-O(k), Space:O(1)
*/

int CountProcess2(int k) {
	if (k <= 0) {
		return 0;
	}
	int counter0 = 1;
	int counter1 = 0;
	for (int i = 0; i < k; i++) {
		int temp = counter0;
		counter0 = counter1;
		counter1 += temp;
	}
	return counter0 + counter1;
}

/*
*Solution 3:
*In solution 2, we have got the recursvie formula. And we can use matrix
*multiplication to represent these formula, this problem will become to a
*power of matrix problem which we can do it in O(log(k)) time.
*
*  _    _ k      _ _      _           _
* | 0  1 |   *  | 1 |  = | counter0(k) |
* | 1  1 |      | 0 |    | counter1(k) |
*  -    -        - -      -           -
*
*Cost: Time-O(log(k)), Space:O(1)
*/

void SquareMatrixMultiplication(int **matrix_left, int **matrix_right, int len, int **result) {
	if (matrix_left == NULL || matrix_right == NULL || len <= 0 || result == NULL) {
		return;
	}
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			result[i][j] = 0;
			for (int k = 0; k < len; k++) {
				result[i][j] += matrix_left[i][k] * matrix_right[k][j];
			}
		}
	}
}

void QuickPowerOfSquareMatrix(int k, int **in_matrix, int len, int **result) {
	if (k <= 0 || in_matrix == NULL || len <= 0 || result == NULL) {
		return;
	}
	//initialization
	int **temp_matrix_odd = new int *[len];
	for (int i = 0; i < len; i++) {
		temp_matrix_odd[i] = new int[len];
	}
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			temp_matrix_odd[i][j] = in_matrix[i][j];
		}
	}
	int **temp_matrix_even = new int *[len];
	for (int i = 0; i < len; i++) {
		temp_matrix_even[i] = new int[len];
	}
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			if (i != j) {
				result[i][j] = 0;
			} else {
				result[i][j] = 1;
			}
		}
	}
	int **temp_result = new int *[len];
	for (int i = 0; i < len; i++) {
		temp_result[i] = new int[len];
	}
	//power process
	int counter = 0;
	int **cur = temp_matrix_odd;
	while (k > 0) {
		if (++counter > 1) {
			if (counter % 2 == 1) {
				SquareMatrixMultiplication(temp_matrix_even, temp_matrix_even, len, temp_matrix_odd);
				cur = temp_matrix_odd;
			} else {
				SquareMatrixMultiplication(temp_matrix_odd, temp_matrix_odd, len, temp_matrix_even);
				cur = temp_matrix_even;
			}
		}
		if ((k & 1) == 1) {
			for (int i = 0; i < len; i++) {
				for (int j = 0; j < len; j++) {
					temp_result[i][j] = result[i][j];
				}
			}
			SquareMatrixMultiplication(cur, temp_result, len, result);
		} 
		k = k >> 1;
	}
	//uninitialization
	for (int i = 0; i < len; i++) {
		delete [] temp_matrix_odd[i];
	}
	delete [] temp_matrix_odd;
	for (int i = 0; i < len; i++) {
		delete [] temp_matrix_even[i];
	}
	delete [] temp_matrix_even;
	for (int i = 0; i < len; i++) {
		delete [] temp_result[i];
	}
	delete [] temp_result;
}

int CountProcess3(int k) {
	if (k <= 0) {
		return 0;
	}
	int **matrix = new int*[2];
	matrix[0] = new int[2];
	matrix[1] = new int[2];
	matrix[0][0] = 0;
	matrix[0][1] = 1;
	matrix[1][0] = 1;
	matrix[1][1] = 1;
	int **result = new int*[2];
	result[0] = new int[2];
	result[1] = new int[2];
	result[0][0] = 0;
	result[0][1] = 0;
	result[1][0] = 0;
	result[1][1] = 0;
	QuickPowerOfSquareMatrix(k, matrix, 2, result);
	int ret = result[0][0] + result[1][0];
	delete [] matrix[0];
	delete [] matrix[1];
	delete [] matrix;
	delete [] result[0];
	delete [] result[1];
	delete [] result;
	return ret;
}

int main(int argc, char *argv[]) {
	for (int i = 0; i < 10; i++) {
		printf("There are %d strings.\n", CountProcess1(i, 0, '0'));
		printf("There are %d strings.\n", CountProcess2(i));
		printf("There are %d strings.\n", CountProcess3(i));
	}
}
