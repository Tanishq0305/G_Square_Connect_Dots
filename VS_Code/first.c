// C program to print elements of Three-Dimensional Array

#include <stdio.h>
int correctPathLength = 8;
int x[3][7][2];
int x1[3][7][2];
int check( int x[3][7][2], int x1[3][7][2]){
for(int k=0;k<3;k++){
    for(int j = 0; j<7;j++){
    for (int i = 0; i < 2; i++) {
        if (x1[k][j][i] != x[k][j][i] || x1[k-1][j-1][i-1] != x[k][j][i]) {
        return 0;
        }
    }
    }
     return 1;
}
}

void main(void)
{
	// initializing the 3-dimensional array
	int x[3][7][2] = { { { 0, 1 }, { 3, 4 }, { 5, 6 }, { 6, 7 }, { 8, 9 }, { 10, 11 },{ 12, 13 } },
					{ { 14, 15 }, { 16, 17 }, { 18, 19 }, { 20, 21 }, { 22, 23 },{ 24, 25 }, { 26, 27 }} ,
                     {  { 28, 29 }, { 30, 31 }, { 32, 33 }, { 34, 35 },{36,37} ,{38,39}, {40,41}} };

    int x1[3][7][2] = { { { 0, 2 }, { 3, 4 }, { 5, 6 }, { 6, 7 }, { 8, 9 }, { 10, 11 },{ 12, 13 } },
					 { { 0, 1 }, { 3, 4 }, { 5, 6 }, { 6, 7 }, { 8, 9 }, { 10, 11 },{ 12, 13 } }};

	// output each element's value
	// for (int i = 0; i < 3; ++i) {
	// 	for (int j = 0; j < 7; ++j) {
	// 		for (int k = 0; k < 2; ++k) {
	// 			printf("Element at x[%i][%i][%i] = %d\n", i,
	// 				j, k, x[i][j][k]);
	// 		}
	// 	}
	// }

    if(check(x,x1)==1){
        printf("matched");
    }else{
        printf("Not matched");
    }
    

}


