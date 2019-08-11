#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "future.h"
#include "cards.h"
#include "eval.h"
#include "input.h"


/*This reads one signle line and converts it into a hand*/
deck_t * hand_from_string(const char * str, future_cards_t * fc){
  deck_t * hand = malloc(sizeof(deck_t));
  hand->n_cards = 0;
  hand->cards = NULL;
  card_t cardToAdd;
  int unkIdx;
  card_t * futureCardPtr = NULL;
  
  for (size_t i = 0; i < strlen(str); i++) { //Iterate through each character in the string
    //Call card_from_letters with the char and the next one if it's a capital letter or number
    if (isupper(str[i]) || isdigit(str[i])) {
      cardToAdd = card_from_letters(str[i], str[i+1]);
      add_card_to(hand, cardToAdd);
    }
    else if (str[i] == '?') { //Call add_empty_card for any ? encountered
      unkIdx = atoi(&str[i+1]); //read the number after the ? to determine the unkIdx
      
      futureCardPtr = add_empty_card(hand);
      add_future_card(fc, unkIdx, futureCardPtr);

      do {
	    i++;
      } while (isdigit(str[i])); //move past ? index
    }
  }
  return hand;
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
  char * handStr = NULL;
  size_t handStrSz = 0;
  deck_t ** hands = NULL;
  *n_hands = 0;

  while (getline(&handStr, &handStrSz, f) > 0) { //Read a line with getline
    *n_hands = *n_hands + 1;
    if (strlen(handStr) < 15) { //make sure it has at least 5 cards
      fprintf(stderr, "I think there's a problem with input line %zu\n", *n_hands);
      exit(EXIT_FAILURE);
    }

    hands = realloc(hands, *n_hands * sizeof(deck_t*));
    hands[*n_hands - 1] = hand_from_string(handStr, fc); //Call hand_from_string to add that line to hands arrays
  }
  free(handStr);
  
  return hands;
}
