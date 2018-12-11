#include <stdlib.h>
#include <stdio.h>

void rotate(char matrix[10][10]) {
  char tempMat[10][10];
  
  //rotate into tempMat
  for (int i = 1; i <= 10; i++) {
    for (int j = 1; j <= 10; j++) {
      tempMat[j][11-i] = matrix[i][j];
    }
  }
    
  //copy tempMat back to matrix
  matrix = tempMat;

  return;
}
