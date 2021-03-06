/*
	stringSearch.c
	CIS3490 A3
	Jessica Authier
	0849720
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* Creates shift table for horspool search
   Input:
     pattern - the pattern to search for
     table - the reference table
*/
void shifttable(char * pattern, int * table){
	int i,j,m;
	m=strlen(pattern);
	for(i=0;i<500;i++){
 		table[i]=m;
	}
	for(j=0;j<m-1;j++){
 		table[pattern[j]]=m-1-j;
	}
}

/* Searches for all the instances of the pattern in the text visa horspool's algorithm
   Input:
     text - the entire text to search
     pattern - the pattern to search for
     table - the reference table
   Output:
     count - the number of matches found
*/
int horspoolSearch(char * text, char * pattern, int * table) {
	int i,j,k,m,n;
	n=strlen(text);
	m=strlen(pattern);
	int count = 0;
	shifttable(pattern, table);
	i=m-1;
	while(i<n){
 		k=0;
 		while((k<m) && (pattern[m-1-k]==text[i-k])){
  			k++;
 		}
		if(k==m)
			count ++;
  		else
			i+=table[text[i]];
	}
	return count;
}

/* Reads in then file and puts every character in an array
	Inputs: 
	  fileName - the name of the file to be read
	Output:
	  text - the array of all the characters from the file
*/
char * readFile(char * fileName) {
	FILE * fp = fopen(fileName, "r");
	if (fp == NULL){
		printf("Invalid file.\n");
		exit(0);
	}

	char * text = malloc(sizeof(char)*3300000);
	printf("here\n");
	int i = 0;
	char c;
	fscanf(fp, "%c",&c);

	while (c != EOF){
		text[i] = c;
		i++;
		int ret =  fscanf(fp, "%c",&c);
		if (ret == EOF)
			break;

	}
	text[i] = '\0';
	return text;
}

int main(int argc, char const *argv[]) {
	
	char fileName[12] = "data_5.txt";
	char * text = readFile(fileName);
	char pattern[100];
	int table[500];
	time_t t_start, t_end;
	long t_diff;

	printf("Please enter a a pattern you wish to search for: ");
	fgets(pattern,100,stdin);

	int len = strlen(pattern) - 1;
	if (pattern[len] == '\n')
		pattern[len] = '\0';

	t_start = time(NULL);
	int numFound = horspoolSearch(text,pattern,table);
	t_end = time(NULL);
	t_diff = (long) t_end - t_start;
	printf("%d matche(s) found in %ld seconds using Horspool's Algorithm.\n", numFound, t_diff);

	return 0;
}