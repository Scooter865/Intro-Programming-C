#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int *array, size_t n);

void main(void) {
  //specify test arrays (all of length = 10), answers, and number of test arrays
  
  int arrays[][10] = {{1, 2, 3, 1, 2, 3, 1, 2, 3, 1}, //basic 123 mentioned in forum (3)
		      {1, 2, 1, 3, 5, 7, 2, 4, 6, 9}, //example in next-README (4)
		      {1, 3, 6, 8, 1, 2, 4, 1,99, 0}, //MaxSeq at beginning, OB1 case (4)
		      {1, 3, 6, 8, 3, 2, 3, 4,10,99}, //MaxSeq at end, OB1 case (5)
		      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //all the same (0)
		      {10,9, 8, 7, 6, 5, 4, 3, 2, 1}, //all decreasing (0)
		      {-3,-2,-1,0, 1, 2, 3, 0, 0, 0}, //increasing from negative (7)
		      {0, 1, 2,-3,-4,-5, 0, 0, 0, 0}  //increasing into negative (3)
  };
  
  int answers[] = {3,4,4,5,1,1,7,3};
  int n = 8;
  
  //loop through array of test arrays
  for (int i = 0; i < n; i++) {
    //check for correct answer
    if (maxSeq(arrays[i],10) != answers[i]) {
      //specify failed array and exit if answer is not correct
      printf("failed array %d\n",i);
      exit(EXIT_FAILURE);
    }
  }

  //empty array corner case
  int emptyArray[] = {};
  if (maxSeq(emptyArray,0) != 0) {
    printf("failed emptyArray\n");
    exit(EXIT_FAILURE);
  }

  printf("pass\n");

  exit(EXIT_SUCCESS);
}

