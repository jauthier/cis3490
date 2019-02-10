#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct Point {
  float x;
  float y;
}Point;

int parseFile(struct Point * points, FILE * fp);
int bruteHull(struct Point * points, struct Point * brutePoints, int count);
int quickHull(struct Point * points, struct Point * quickPoints, int count);
int findHull (struct Point * points, struct Point * quickPoints, struct Point p1, struct Point p2, int count, int hullCounter, int side);
int findSide (struct Point p1, struct Point p2, struct Point p);

int parseFile(struct Point * points, FILE * fp){
  char line[50];
  int i = 0;
  //read through file and get all the points
  // printf("in parsefile\n");
  while (fgets(line, sizeof(line), fp) != NULL) {
    //parse the line
    char *token;
    token = strtok(line, ", ");
    points[i].x = atof(token);
    // printf("%f\n", points[i].x);
    token = strtok(NULL, ", \n");
    points[i].y = atof(token);
    // printf("%f\n", points[i].y);
    i++;
  }
  return i;
}

int bruteHull(struct Point * points, struct Point * brutePoints, int count){
  int i;
  int chCounter = 0;
  for (i = 0; i < count; i++) {
    int j;
    int isPartOfHull = 0;
    for (j = 0; j < count; j++) {
      if (j==i){
        continue;
      }
      struct Point p1 = points[i];
      struct Point p2 = points[j];

      int pointsOnSide = 0;
      int k;
      int dupPoint = 0;
      for (k = 0; k < count; k++) {
        if (k!=i && k!=j){
          if (((points[k].y - p1.y) * (p2.x - p1.x) - (points[k].x - p1.x) * (p2.y - p1.y))<0){
            // printf("%f, %f   %f, %f\n",p1.x, p1.y, p2.x, p2.y );
            pointsOnSide ++;
          }
        } else {
          dupPoint ++;
        }
      }
      if (pointsOnSide == count-dupPoint){
        isPartOfHull = 1;
        break;
      }
    }

    if (isPartOfHull == 1){
      brutePoints[chCounter] = points[i];
      chCounter++;
    }
  }
  for (i = 0; i < chCounter; i++) {
    printf("%f, %f\n", brutePoints[i].x, brutePoints[i].y);
  }
  return i;
}

int quickHull(struct Point * points, struct Point * quickPoints, int count){
  int i;

  // find the min and max x
  int minX = 0;
  int maxX = 0;
  for (i = 1; i < count; i++) {
    if (points[i].x < points[minX].x){
      minX = i;
    }
    if (points[i].x > points[maxX].x){
      maxX = i;
    }
  }
  int hullCounter = 0;
  // Recursively find convex hull points on
   // one side of line
   hullCounter = findHull(points, quickPoints, points[minX], points[maxX], count, hullCounter, 1);
   // printf("%d\n", hullCounter);
   // Recursively find convex hull points on
   // other side of line
   hullCounter = findHull(points, quickPoints, points[minX], points[maxX], count, hullCounter, -1);
   for (int j = 0; j < hullCounter; j++) {
     /* code */
     printf("%f,%f\n", quickPoints[j].x, quickPoints[j].y);
   }
   return hullCounter;
}

int findHull (struct Point * points, struct Point * quickPoints, struct Point p1, struct Point p2, int count, int hullCounter, int side){
  int ind = -1;
  int max_dist = 0;
  for (int i=0; i<count; i++){
    int temp = abs((points[i].x - p1.x) * (p2.y - p1.y) - (points[i].y - p1.y) * (p2.x - p1.x));
    if (findSide(p1, p2, points[i]) == side && temp > max_dist){
        ind = i;
        max_dist = temp;
    }
  }
  // If no point is found, add the end points
  // of L to the convex hull.
  // printf("Count: %d\n", hullCounter);
  if (ind == -1){
    int isP1 = 0;
    int isP2 = 0;
    // printf("%d\n", hullCounter);
    if (hullCounter == 0){
      quickPoints[hullCounter] = p1;
      // printf("%d: %f,%f\n", hullCounter, p1.x, p1.y);
      hullCounter ++;

      quickPoints[hullCounter] = p2;
      // printf("%d: %f,%f\n", hullCounter, p2.x, p2.y);
      hullCounter ++;
    } else {
      int i;
      for (i = 0; i < hullCounter; i++) {
        // printf("%f : %f\n", p1.x, quickPoints[hullCounter].x);
        if (p1.x == quickPoints[i].x && p1.y == quickPoints[i].y){
          // printf("in if\n" );
          isP1 = 1;
        }
        if (p2.x == quickPoints[i].x && p2.y == quickPoints[i].y){
          isP2 = 1;
        }
      }
      if (isP1 == 0){
        quickPoints[hullCounter] = p1;
        // printf("%d: %f,%f\n", hullCounter, p1.x, p1.y);
        hullCounter ++;
      }
      if (isP2 == 0) {
        quickPoints[hullCounter] = p2;
        // printf("%d: %f,%f\n", hullCounter, p2.x, p2.y);
        hullCounter ++;
      }
    }
    return hullCounter;
  }

  // Recur for the two parts divided by a[ind]
  hullCounter = findHull(points, quickPoints, points[ind], p1, count, hullCounter, -findSide(points[ind], p1, p2));
  hullCounter = findHull(points, quickPoints, points[ind], p2, count, hullCounter, -findSide(points[ind], p2, p1));
  return hullCounter;
}

int findSide (struct Point p1, struct Point p2, struct Point p){
  int num = (p.x - p1.x) * (p2.y - p1.y) - (p.y - p1.y) * (p2.x - p1.x);
  if (num > 0){
    return 1;
  }
  if (num < 0){
    return -1;
  }
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
  struct Point points[30000];
  int count = parseFile(points, fp);

  struct Point brutePoints[count];
  struct Point quickPoints[count];

  time_t start, end;
  printf("Brute Force Convex Hull\n\n");
  start = clock();
  int bruteCount = bruteHull(points, brutePoints, count);
  end = clock();
  int t=(end-start)/CLOCKS_PER_SEC;
  printf("The Convex Hull has %d points and completed in: %ds\n", bruteCount, t);
  printf("-----------------------------\n");


  printf("QuickHull\n\n");
  start = clock();
  int quickCount = quickHull(points, quickPoints, count);
  end = clock();
  t=(end-start)/CLOCKS_PER_SEC;
  printf("The Convex Hull has %d points and completed in: %ds\n", quickCount, t);
  printf("-----------------------------\n");

  fclose(fp);
  return 0;
}
