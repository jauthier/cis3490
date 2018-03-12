/*
	anagramDetect.c
	CIS3490 A3
	Jessica Authier
	0849720
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>  

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
int permute(char * first, int l, int r, char * second) {
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
			swap((first+l), (first+i)); //backtrack
			if (ret == 1)
				return 1;
		}
	}
}

/*  Finds all of the anagrams via brute force
	Inputs: 
	  first - the users string
	  dict - all of the strings from data_4.txt
	Output:
	  count - the number of anagrams found
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
		if (i%1000 == 0)
			printf("still going\n");
	}
	return count;
}

/* Sorts a string in alpha-numeric order
   Input:
     toSort - a string to sort
   Output:
     sort - the sorted string
*/
char * sort(char * toSort) {
	int len = strlen(toSort);
	int i = 0;
	int j = 0;
	char * sortedStr = malloc(sizeof(char)*(len+1));
	strcpy(sortedStr, toSort);
	for (i = 0; i < len-1; i++) {
      for (j = i+1; j < len; j++) {
         if (sortedStr[i] > sortedStr[j]) {
            char temp = sortedStr[i];
            sortedStr[i] = sortedStr[j];
            sortedStr[j] = temp;
         }
      }
   }
   return sortedStr;
}

/*  Finds all of the anagrams via presorting
	Inputs: 
	  first - the users string
	  dict - all of the strings from data_4.txt
	Output:
	  count - the number of anagrams found
 */
int sortingDetection(char * first, char ** dict) {
	int count = 0;
	int i = 0;
	char * sorted = sort(first);
	for (i=0;i<30000;i++){
		char * second = sort(dict[i]);
		if (strcmp(sorted, second) == 0){
			printf("%s\n",dict[i]);
			count ++;
		}
		free(second);
	}
	free(sorted);
	return count;
}

/* Reads the file and makes an array of all the strings
   Input:
     fileName - the name of the file to be read from
*/
char ** readFile(char * fileName) {
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
		if (c == ' ' || c == '\n'){
			if (c == ' '){
				hold[i] = '\0';
				dict[j] = malloc(sizeof(char)*(strlen(hold)+2));
				strcpy(dict[j],hold);
				j++;
				i = 0;
			}
		
		} else {
			hold[i] = c;
			i++;
		}
		int ret =  fscanf(fp, "%c",&c);
		if (ret == EOF)
			break;

	}
	return dict;
}

/* frees the string in the array */
void freeDict(char ** dict){
	int i=0;
	for (i=0;i<30000;i++){
		free(dict[i]);
	}
}

int main(int argc, char const *argv[])
{
	char first[20];
	char fileName[20] = "data_4.txt";
	char ** dict = readFile(fileName);
    time_t t_start, t_end;
    long t_diff;

	printf("Please enter a string that you want to find the anagrams of: ");
	fgets(first,20,stdin);

	t_start = time(NULL);
	int num = bruteForceDetection(first, dict);
	t_end = time(NULL);
	t_diff = (long) t_end - t_start;
	printf("There were %d anagrams found in %ldms.\n",num,t_diff);

	t_start = time(NULL);
	num = sortingDetection(first, dict);
	t_end = time(NULL);
	t_diff = (long) t_end - t_start;
	printf("There were %d anagrams found in %ldms.\n",num,t_diff);

	freeDict(dict);
	free(dict);


	return 0;
}
