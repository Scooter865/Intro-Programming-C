#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"


char * getKey(FILE * file) {
	int k;
	char * curKey;
	size_t i = 0;
	while((k = fgetc(file)) != '=') {
		if (k == EOF) {
			return NULL; //using NULL to indicate EOF
		}
		else {
			curKey[i] = k;
			i++;
		}
	}
	return curKey;
}

char * getVal(FILE * file) {
	int v;
	char * curVal;
	size_t i = 0;
	while((v = fgetc(file)) != '\n') {
		if (v == EOF) {
			return NULL;
		}
		else {
			curVal[i] = v;
			i++;
		}
	}
	return curVal;
}


int writePair(FILE * file, kvarray_t * targetArray, size_t pairIdx) {
	char * keyToWrite = getKey(file);
	char * valToWrite = getVal(file);

	//indicate to calling function when EOF is encountered
	if ((keyToWrite == NULL)||(valToWrite == NULL)) {
		return 0;
	}

	//need to write duplicate check

	(targetArray->nKVs)++;
	targetArray = realloc(targetArray, sizeof(kvpair_t) + (nKVs * sizeof(kvpair_t)));
	(targetArray->kvArray[pairIdx]).key = keyToWrite;
	(targetArray->kvArray[pairIdx]).value = valToWrite;

	//indicate to calling function that a pair was written
	return 1;
}


kvarray_t * readKVs(const char * fname) {
	//Open file
	FILE * f = fopen(fname, "r");
	if (f == NULL) {
		fprintf(stderr, "Problem opening file\n");
		exit(EXIT_FAILURE);
	}

	//Allocate the array to write kv pairs to
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
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
	for(size_t i = 0; i < pairs->nKVs; i++) {
  		printf("key = '%s' value = '%s'\n", (pairs->kvArray[i]).key, (pairs->kvArray[i]).value);
  	}
}


/*Searches paris for key and returns corresponding value*/
char * lookupValue(kvarray_t * pairs, const char * key) {
	for (size_t i = 0; i < pairs->nKVs; i++) {
		if ((strcmp(pairs->kvArray[i]).key, key) == 0) {
			return ((pairs->kvArray[i]).value);
		}
	}
	return NULL;
}