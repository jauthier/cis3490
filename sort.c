#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int parseFile(int * A, FILE * fp);
int bruteSort (int * A, int count);
void swap(int *xp, int *yp);
int mergeSort (int * A, int count);
int merge(int * B, int b, int * C, int c, int * A);


int parseFile (int * A, FILE * fp){
  char line[50];
  int i = 0;
  //read through file and get all the points
  // printf("in parsefile\n");

  while (fgets(line, sizeof(line), fp) != NULL) {
    //parse the line
    char *token;
    token = strtok(line, " \n");
    while (token != NULL) {
      A[i] = atoi(token);
      i++;
      token = strtok(NULL, " \n");
    }
  }
  return i;
}

int bruteSort (int * A, int count){
  int i, j, min_index, c;
  c = 0;
  for (i = 0; i < count; i++) {
    min_index = i;
    for (j = 0; j < count; j++) {
      if (A[j] < A[min_index]){
        min_index = j;
        c ++;
      }
    }
    swap(&A[min_index], &A[i]);
  }
  return c;
}

void swap (int *xp, int *yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int mergeSort (int * A, int count){
  if (count < 2) {
    return 0;
  }
  int i, x1, x2, x3;
  int half = count/2;
  int B[half +1];
  int C[half +1];
  for (i = 0; i < half-1; i++){
    B[i] = A[i];
  }
  for (i = half; i < count; i++) {

    C[i] = A[i];
  }
  x1 = mergeSort(B, half);
  x2 = mergeSort(C, count-(half));
  x3 = merge(B, half, C, count-half, A);
  return x1+x2+x3;
}

int merge(int * B, int b, int * C, int c, int * A){

  int i=0;
  int j=0;
  int k=0;
  int x=0;

  while (i<b && j<c){
    if (B[i] < C[j]){
      A[k] = B[i];
      i++;
    } else {
      A[k] = C[j];
      j++;
    }
    x++;
    k++;
  }
  int l;
  int m = 0;
  if (i == b){
    for (l=k; l < (b+c-1); l++){
      A[l] = C[m];
      m++;
    }
  } else {
    for (l=k; l < (b+c-1); l++){
      A[l] = B[m];
      m++;
    }
  }
  return x;
}


int main(int argc, char const *argv[]) {
  if (argc < 2) {
    //no file as been provided
    printf("You must provide a file.\n");
    exit(0);
  }

  FILE* fp = fopen(argv[1],"r");
  if (fp == NULL){
    printf("The file was unable to be opened.\n");
    exit(0);
  }
  int A[80000];
  int count = parseFile(A, fp);

  time_t start, end;
  printf("Select Sort\n");
  start = clock();
  int bruteCount = bruteSort(A, count);
  end = clock();
  int t=(end-start)/CLOCKS_PER_SEC;
  printf("The sort contained %d swaps and completed in: %ds\n", bruteCount, t);
  printf("-----------------------------\n");
  printf("Merge Sort\n");
  start = clock();
  int mergeCount = mergeSort(A, count);
  end = clock();
  t=(end-start)/CLOCKS_PER_SEC;
  printf("The sort contained %d swaps and completed in: %ds\n", mergeCount, t);
  printf("-----------------------------\n");
  fclose(fp);
  return 0;
}
