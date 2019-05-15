#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

//This function takes care of reading, sort call, and printing
void doEverything(FILE * inputFile) {
  //create the data array
  char ** arrayOfStr = NULL;
  char * line = NULL;
  size_t lineSz = 0;
  size_t nLines = 0;
  while (getline(&line, &lineSz, inputFile) >= 0) {
    nLines++;
    arrayOfStr = realloc(arrayOfStr, nLines * sizeof(*arrayOfStr));
    arrayOfStr[nLines-1] = line;
    line = NULL;
  }
  free(line);
  
  //sort the data
  sortData(arrayOfStr, nLines);
  
  //print and free each line
  for (size_t i = 0; i < nLines; ++i) {
    printf("%s", arrayOfStr[i]);
    free(arrayOfStr[i]);
  }
  free(arrayOfStr);
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    //no need to open or close any files, just create, sort, and print array
    doEverything(stdin);
  }
  else if (argc > 1) {
    //open file, create array, sort array, print array, close file
    for (size_t i = 1; i < argc; ++i){
      FILE * curFile = fopen(argv[1], "r");
      if (curFile == NULL) {
	fprintf(stderr, "problem openning file\n");
	return(EXIT_FAILURE);
      }
      doEverything(curFile);
      if(fclose(curFile) != 0) {
	fprintf(stderr, "problem closing file\n");
	return(EXIT_FAILURE);
      }
    }
  }
  else {
    fprintf(stderr, "problem with inputs\n");
    return(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
