// C program to print elements of Three-Dimensional Array

#include <stdio.h>

int main(void)
{
	// initializing the 3-dimensional array
	int x[3][7][2] = { { { 0, 1 }, { 3, 4 }, { 5, 6 }, { 6, 7 }, { 8, 9 }, { 10, 11 },{ 12, 13 } },
					{ { 14, 15 }, { 16, 17 }, { 18, 19 }, { 20, 21 }, { 22, 23 },{ 24, 25 }, { 26, 27 }} ,
                     {  { 28, 29 }, { 30, 31 }, { 32, 33 }, { 34, 35 },{36,37} ,{38,39}, {40,41}} };

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
