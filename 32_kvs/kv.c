#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"


void getKey(FILE * file, char * curKey) {
  int k;
  size_t i = 0;
  while((k = fgetc(file)) != '=') {
    if (k == EOF) {
      curKey = NULL; //using NULL to indicate EOF
    }
    else {
      curKey = realloc(curKey, (i+1) * sizeof(char));
      curKey[i] = k;
      i++;
    }
  }
}


void getVal(FILE * file, char * curVal) {
  int v;
  size_t i = 0;
  while((v = fgetc(file)) != '\n') {
    if (v == EOF) {
      curVal = NULL;
    }
    else {
      curVal = realloc(curVal, (i+1) * sizeof(char));
      curVal[i] = v;
      i++;
    }
  }
}


int writePair(FILE * file, kvarray_t * targetStruct, size_t pairIdx) {
  char * curKey = malloc(sizeof(char));
  char * curVal = malloc(sizeof(char));
  getKey(file, curKey);
  getVal(file, curVal);
  
  //indicate to calling function when EOF is encountered
  if ((curKey == NULL)||(curVal == NULL)) {
    return 0;
  }
  
  //need to write duplicate check

  targetStruct->nKVs = pairIdx + 1;
  targetStruct = realloc(targetStruct, sizeof(kvpair_t) + (targetStruct->nKVs * sizeof(kvpair_t)));
  (targetStruct->kvArray[pairIdx]).key = curKey;
  (targetStruct->kvArray[pairIdx]).value = curVal;
  
  //indicate to calling function that a pair was written
  return 1;
  //Not free-ing anything here, free-ing to be done in freeKVs
}


kvarray_t * readKVs(const char * fname) {
  //Open file
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Problem opening file\n");
    exit(EXIT_FAILURE);
  }

  //Allocate the struct to write kv pairs to
  kvarray_t * kvPairs = malloc(sizeof(kvarray_t));
  kvPairs->nKVs = 0;

  //Call funciton to write pairs as long as EOF hasn't been reached
  int pairWritten = 1;
  size_t pairNo = 0; //purposely not using nKVs for empty file corner case
  do {
    pairWritten = writePair(f, kvPairs, pairNo);
    pairNo++;
  }
  while (pairWritten != 0);
  
  //Close file
  if(fclose(f) != 0) {
    fprintf(stderr, "Problem closing file\n");
  }
  return kvPairs;
}


void freeKVs(kvarray_t * pairs) {
  /*dig down into each kvpair_t element in pairs and free the key and value members.
    All of these were allocated by multiple writePair calls*/
  for (size_t i = 0; i < pairs->nKVs; i++) {
    free(pairs->kvArray[i].key);
    free(pairs->kvArray[i].value);
  }
  free(pairs); //The kvarray_t was also allocated
}

void printKVs(kvarray_t * pairs) {
  for(size_t i = 0; i < pairs->nKVs; i++) {
    printf("key = '%s' value = '%s'\n", (pairs->kvArray[i]).key, (pairs->kvArray[i]).value);
  }
}


/*Searches paris for key and returns corresponding value*/
char * lookupValue(kvarray_t * pairs, const char * key) {
  for (size_t i = 0; i < pairs->nKVs; i++) {
    if (strcmp((pairs->kvArray[i]).key, key) == 0) {
      return ((pairs->kvArray[i]).value);
    }
  }
  return NULL;
}
