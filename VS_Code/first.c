// C program to print elements of Three-Dimensional Array

#include <stdio.h>

int main(void)
{
	// initializing the 3-dimensional array
	int x[3][7][2] = { { { 0, 1 }, { 0, 2 }, { 0, 3 }, { 0, 4 }, { 0, 5 }, { 0, 6 } },
					{ { 1, 0 }, { 2, 0 }, { 3, 0 }, { 4, 88 }, { 5, 0 }, { 6, 0 } } ,
                     { { 1, 0 }, { 2, 0 }, { 3, 0 }, { 4, 0 }, { 5, 0 }, { 6, 0 } } };

	// output each element's value
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 7; ++j) {
			for (int k = 0; k < 2; ++k) {
				printf("Element at x[%i][%i][%i] = %d\n", i,
					j, k, x[i][j][k]);
			}
		}
	}
	return (0);
}
