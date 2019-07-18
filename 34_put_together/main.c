#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //Open file to read keys from
  FILE * keyFILE = fopen(filename, "r");
  if (keyFILE == NULL) {
    fprintf(stderr, "Problem opening key file\n");
    exit(EXIT_FAILURE);
  }

  counts_t * curCounts = createCounts(); //Initialize a count array

  char * curKey = NULL;
  size_t lineSz = 0;
  while(getline(&curKey, &lineSz, keyFILE) > 0) { //Enter key file reading loop
    char * curValue = lookupValue(kvPairs, curKey); //Lookup the value for a given key
    addCount(curCounts, curValue); //Count up for the value
  }

  free(curKey); //Free the memory used to read lines

  if (fclose(keyFILE) != 0) { //Close the key file
    fprintf(stderr, "Problem closing key file\n");
    exit(EXIT_FAILURE);
  }

  return curCounts;
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    fprintf(stderr, "problem with inputs\n");
    exit(EXIT_FAILURE);
  }
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);

 //count from 2 to argc (call the number you count i)
  for (size_t i = 0; i < argc; i++) {

    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);

    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w+");
    if (f == NULL) {
      fprintf(stderr, "Problem opening output file %zu\n", i);
      exit(EXIT_FAILURE);
    }

    //print the counts from c into the FILE f
    printCounts(c, f);

    //close f
    if (fclose(f) != 0) {
      fprintf(stderr, "Problem closeing output file %zu\n", i);
    }

    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }

 //free the memory for kv
  freeKVs(kv);

  return EXIT_SUCCESS;
}
