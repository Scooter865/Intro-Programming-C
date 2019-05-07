#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/*Count the frequency of characters in a stream and write how many
times a specific character appears to an array. Return a pointer
to that array.*/
int * charCount(FILE * f) {
	int c;
	static int result[26] = {0};
	while ((c = fgetc(f)) != EOF) {
		if (isalpha(c)) {
			++result[c - 'a'];
		}
	}
	return result;
}

/*Find the the largest number in the character frequency array.
Return the index of that number which corresponds to the most frequently
used character which is assumed to be encrypted e*/
int findE(int * freqArray) {
	int lrgIdx = 0;
	for (size_t i = 1; i < 26; ++i) {
		if (freqArray[i] > freqArray[lrgIdx]) {
			lrgIdx = i;
		}
	}
	return lrgIdx;
}


int main(int argc, char ** argv) {
  //error handling
  if (argc != 2) {
    fprintf(stderr, "Please specify a valid file name\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Failed to open file");
  }
  
  //Scan the file at this point with charCount
  int * charFreq;
  charFreq = charCount(f);
  
  //Find the encrypted e
  int encryptedE;
  encryptedE = findE(charFreq);
  
  //calculate the key based with the encrypted e
  unsigned key;
  if ((encryptedE >= 0) && (encryptedE < 4)) {
    key = encryptedE + 22;
  }
  else if ((encryptedE >= 4) && (encryptedE < 26)) {
    key = encryptedE - 4;
  }
  else {
    printf("I think key is out of range.\n");
    return EXIT_FAILURE;
  }
  
  printf("%d\n", key);
  
  return EXIT_SUCCESS;
}
