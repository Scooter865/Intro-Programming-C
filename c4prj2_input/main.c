#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

int main(int argc, char ** argv) {
  FILE * f = fopen(argv[1], "r");
  size_t n_hands = atoi(argv[2]);
  
  future_cards_t * fc = malloc(sizeof(future_cards_t));
  fc->n_decks = 0;
  fc->decks = NULL;

  deck_t ** hands = read_input(f, &n_hands, fc);
  printf("Here are the input hands:\n");
  for (size_t i = 0; i < n_hands; i++) {
    print_hand(hands[i]);
  }

  deck_t * deck = build_remaining_deck(hands, n_hands);
  printf("Here's the remaining deck:\n");
  print_hand(deck);
  shuffle(deck);

  future_cards_from_deck(deck, fc);
  printf("Here are the filled in hands:\n");
  for (size_t i = 0; i < n_hands; i++) {
    print_hand(hands[i]);
  }

  return EXIT_SUCCESS;
}
