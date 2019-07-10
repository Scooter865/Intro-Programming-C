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

  char * curKey = malloc(sizeof(char));
  char * curVal = malloc(sizeof(char));
  getKey(f, curKey);
  getVal(f, curVal);

  while((curKey != NULL)&&(curVal != NULL)) {
    (kvPairs->nKVs)++;
    kvPairs = realloc(kvPairs, sizeof(kvarray_t) + (kvPairs->nKVs)*sizeof(kvpair_t));
    kvPairs->kvArray[kvPairs->nKVs - 1].key = curKey;
    kvPairs->kvArray[kvPairs->nKVs - 1].value = curVal;
    
    char * curKey = malloc(sizeof(char));
    char * curVal = malloc(sizeof(char));
    getKey(f, curKey);
    getVal(f, curVal);
  }

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
