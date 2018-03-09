#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Function to swap values at two pointers */
void swap(char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
 
/* For finding all the permutations of the first string
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

/*  Finds all of the anagrams via brute force
	Inputs: 
	  first - the users string
	  second - the string from data_4.txt that we are checking if its and anagram
 */
int bruteForceDetection(char * first, char ** dict) {
	int i = 0;
	int l = 0;
	int r = strlen(first) - 1;
	int count = 0;
	for (i=0;i<30000;i++){
		int check = permute(first, l, r, dict[i]);
		if (check == 1)
			count ++;
	}
}

char ** readFile(char * fileName){
	FILE * fp = fopen(fileName, "r");
	if (fp == NULL){
		printf("Invalid file.\n");
		exit(0);
	}

	char ** dict = malloc(sizeof(char *)*30000);
	char hold[12];
	int i = 0;
	int j = 0;

	char c;
	fscanf(fp, "%c",&c);

	while (c != EOF){
		printf("%c\n", c);
		if (c == ' ' || c == '\n'){
			hold[i] = '\0';
			dict[j] = malloc(sizeof(char)*(i+1));
			strcpy(dict[j],hold);
			j++;
			i = 0;
		
		} else {
			printf("%d\n",i);

			hold[i] = c;
			i++;
		}
		//char a = getchar();
		fscanf(fp, "%c",&c);

	}
}


int main(int argc, char const *argv[])
{
	char first[11] = "1131176292";
	char fileName[20] = "data_4.txt";
	char ** dict = readFile(fileName);

	return 0;
}