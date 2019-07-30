#include <stdlib.h>
#include <stdio.h>
#include "future.h"
#include "cards.h"
#include "eval.h"
#include "input.h"


/*This reads one signle line and converts it into a hand*/
deck_t * hand_from_string(const char * str, future_cards_t * fc){

}

/*This function reads the input from f. Recall that the input file has one hand
per line (and that we represent a hand with a deck_t). You should allocate a
deck_t for each hand and place it into an array of pointers to deck_ts, which is
your answer. This function needs to tell its caller how many hands it read. We
could return a struct, but we are going to do this a different way: it will fill
in *n_hands with the number of hands. This is a bit different, but you have seen
it before: this is how getline "returns" the string it read and the size of the
space allocated to that string.*/
deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  file = fopen(f, "r");
  if (file == NULL) {
    fprintf(stderr, "problem openning input file\n", );
    exit(EXIT_FAILURE);
  }

  //Read a line with getline
  //Call hand_from_string to add that line to fc
}
