#include <stdio.h>
/*
ALGORITHM X(A[0..n − 1])
// Input: A contains n real numbers
for i   0 to n − 2 do
  for j   i + 1 to n − 1 do
    if A[j] > A[i]
      swap A[i] and A[j]


*/


void al1(int * array, int n){
	int i;
	for (i=0; i<n-1;i++){
		for (int j=i+1; j<n; ++j){
			if (array[j]>array[i]){
				int hold = array[i];
				array[i] = array[j];
				array[j] = hold;
			}
		}
	}

	for (i=0;i<n;i++){
		printf("%d\n", array[i]);
	}
}


int main(int argc, char * argv[]){

	int array[10] = {0,1,7,3,4,5,6,2,8,9};

	al1(array, 10);
	return 0;
}
