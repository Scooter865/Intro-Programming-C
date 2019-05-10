#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rotate.c"

#define COLUMNS 10
#define ROWS 10

void readMatrix(FILE * stream, char * matrix) {
  char row[COLUMNS + 2];
  char * newLineLoc;
  int numrows = 0;
  
  while(fgets(row, COLUMNS + 2, stream) != NULL) {
    //count each row read, fail if too many rows read
    numrows++;
    if (numrows > ROWS) {
      fprintf(stderr, "Too many rows\n");
      exit(EXIT_FAILURE);
    }
    
    //find a newline and make sure it's in the right place (after 10 chars)
    newLineLoc = strchr(row, '\n');
    if (newLineLoc != (row + ROWS)) {
      fprintf(stderr, "Row too short or too long.\n");
      exit(EXIT_FAILURE);
    }
    
    //write the first 10 chars of a row to the matrix
    for (size_t i = 0; i < COLUMNS; ++i) {
      matrix[(numrows-1)*ROWS + i] = row[i];
    }
  }
  
  //fail if too few rows read
  if (numrows < ROWS) {
    fprintf(stderr, "Too few rows.\n");
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Please specify a valid file name\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1],"r");
  if (f == NULL) {
    fprintf(stderr, "Failed to open file");
    return EXIT_FAILURE;
  }
  
  //initialize the matrix
  char matrix[10][10];
  char * matrix_ptr = &matrix[0][0];
  
  //read from file into matrix
  readMatrix(f, matrix_ptr);
  
  //call previously made rotator function
  rotate(matrix);
  
  //print the rotated matrix
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLUMNS; ++j) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
  
  return EXIT_SUCCESS;
}
