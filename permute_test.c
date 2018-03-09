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
 
/* Function to print permutations of string
   This function takes three parameters:
   Input: 
     String
   	 Starting index of the string
  	 Ending index of the string. 
  	 String to compare
*/
void permute(char * first, int l, int r, char * second){
	int i;
	if (l == r) {

		printf("%s\n", first);
	} else {
		for (i = l; i <= r; i++){
			swap((first+l), (first+i));
			permute(first, l+1, r,second);
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