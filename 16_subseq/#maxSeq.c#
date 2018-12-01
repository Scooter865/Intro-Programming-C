#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int *array, size_t n) {
  //intialize the counters to be used
  size_t tempCounter = 1;
  size_t maxCount = 1;

  //corner case for n < 0
  if (n < 1) {
    return 0;
  }
  
  for (size_t i = 0; i < n; i++) {
    //write to max count for last value if temp counter is greater
    if ((i == n-1)&&(tempCounter > maxCount)) {
      maxCount = tempCounter;
    }
    else if (array[i+1] > array[i]) {
      //increment temp counter when next element is larger
      tempCounter++;
    }
    else {
      //after an increasing sequence:
      //write temp counter to max counter if greater
      if (tempCounter > maxCount) {
	maxCount = tempCounter;
      }
      //reset temp counter
      tempCounter = 1;
    }
  }
  
  return maxCount;
}

