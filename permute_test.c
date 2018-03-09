#include <stdio.h>
#include <string.h>

/* Function to swap values at two pointers */
void swap(char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
 
/* 
	For finding all the permutations of the first string
   	Input: 
      first - String to be permuted
   	  l - Starting index of the string
  	  r - Ending index of the string. 
  	  second - String to compare to all the permutations
*/
int permute(char * first, int l, int r, char * second){
	int i;
	if (l == r) {
		if (strcmp(first, second)==0){
			printf("%s\n", first);
			return 1;
		}
		printf(" No match: %s\n", first);
		return 0;
	} else {
		for (i = l; i <= r; i++){
			swap((first+l), (first+i));
			int ret = permute(first, l+1, r,second);
			if (ret == 1)
				return 1;
			swap((first+l), (first+i)); //backtrack
		}
	}
}


int main(int argc, char const *argv[])
{
	char str[4] = "tea";
	char second[4] = "eat";
	permute(str,0,2,second);

	return 0;
}