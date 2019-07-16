#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"


/*Allocate memory for a counts_t structure, and initialize
it to represent that nothing has been counted yet*/
counts_t * createCounts(void) {
  //Allocate the counts_t and initialize all counts to 0
  counts_t * cntsStruct = malloc(sizeof(counts_t));
  cntsStruct->oneCntArray = NULL;
  cntsStruct->nStr = 0;
  cntsStruct->nUnk = 0;
  return cntsStruct;
}


/*Increment the count for the corresponding name. Name will
be NULL in the case of something that is unknown*/
void addCount(counts_t * c, const char * name) {
  if (name == NULL) {
    c->nUnk++;
  }
  else {
    size_t i = 0;
    int newStr = 1;
    while (i < c->nStr) {
      if (strcmp(name, c->oneCntArray[i]->str) == 0) {
        //Increment that string count if name already exists in the array
        c->oneCntArray[i]->strCnt++;
        i++;
        newStr = 0;
      }
      else {
        i++;
      }
    }
    if (newStr == 1) {
      //Allocate and create a new element for a new string
      c->nStr++;
      c->oneCntArray = realloc(c->oneCntArray, (c->nStr) * sizeof(one_count_t*));
      c->oneCntArray[c->nStr-1] = malloc(sizeof(one_count_t));
      c->oneCntArray[c->nStr-1]->str = strdup(name);
      c->oneCntArray[c->nStr-1]->strCnt = 1;
    }
  }
}


/*Takes a counts_t and prints that information to the FILE
outFile. These should appear in the order that the name is
first added, with unknown always appearing last. If there 
are no unknown values, you should not print a line for unknown.*/
void printCounts(counts_t * c, FILE * outFile) {
  for (size_t i = 0; i < c->nStr; i++) {
    printf("%s: %zu\n", c->oneCntArray[i]->str, c->oneCntArray[i]->strCnt);
  }
  if (c->nUnk != 0) {
    printf("<unknown> : %zu\n", c->nUnk);
  }
}


/*free all the memory associated with a counts_t*/
void freeCounts(counts_t * c) {
  for (size_t i = 0; i < c->nStr; i++) {
    free(c->oneCntArray[i]->str);
    free(c->oneCntArray[i]);
  }
  free(c->oneCntArray);
  free(c);
}
