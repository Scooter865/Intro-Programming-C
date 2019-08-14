#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"


int main(int argc, char ** argv) {
  int num_trials;
  
  if (argc < 2) {
    fprintf(stderr, "Need more inputs\n");
    exit(EXIT_FAILURE);
  }
  else if (argc == 3) {
    num_trials = atoi(argv[2]);
  }
  else {
    num_trials = 10000;
  }
  
  FILE * input = fopen(argv[1], "r");
  if (input == NULL) {
    fprintf(stderr, "Problem opening file\n");
    exit(EXIT_FAILURE);
  }
  
  future_cards_t * fc = malloc(sizeof(future_cards_t));
  fc->n_decks = 0;
  fc->decks = NULL;
  size_t n_hands = 0;

  deck_t ** hands = read_input(input, &n_hands, fc);
  printf("Here are the input hands:\n");
  for (size_t i = 0; i < n_hands; i++) {
    print_hand(hands[i]);
    printf("\n");
  }

  deck_t * remainingDeck = build_remaining_deck(hands, n_hands); //Should maybe allocate this
  printf("Here's the remaining deck:\n");
  print_hand(remainingDeck);
  printf("\n");

  int windex[n_hands + 1];
  for (size_t i = 0; i <= n_hands; i++) {
    windex[i] = 0;
  }

  int compRes;
  size_t winnerIdx;
  int tie;

  for (size_t i = 0; i < num_trials; i++) {
    shuffle(remainingDeck);
    future_cards_from_deck(remainingDeck, fc);
    winnerIdx = 0;
    tie = 0;

    for (size_t j = 1; j < n_hands; j++) {
      compRes = compare_hands(hands[winnerIdx], hands[j]);
      /*if (compRes > 0) {
	  windex[winnerIdx]++;
	  }*/
	if (compRes == 0) {
	  tie = 1;
	}
	else if (compRes < 0) {
	  winnerIdx = j;
	  tie = 0;
	}
    }
    if (tie) {
      windex[n_hands]++;
    }
    else {
      windex[winnerIdx]++;
    }
  }
  
  for (size_t i = 0; i < n_hands; i++) {
    //double winPct = (windex[i]/num_trials)*100;
    printf("Hand %zu won %u / %u times (%.2f%%)\n", i, windex[i], num_trials,((double)windex[i]/(double)num_trials)*100);
  }
  printf("And there were %u ties\n", windex[n_hands]);

  free_deck(remainingDeck);
  for (size_t i = 0; i < n_hands; i++) {
    free_deck(hands[i]);
  }
  free(hands);
  for (size_t i = 0; i < fc->n_decks; i++) {
    free(fc->decks[i].cards);
  }
  free(fc->decks);
  free(fc);

  if (fclose(input) != 0) {
    fprintf(stderr, "problem closing input file\n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
