#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"

int main(void) {
  deck_t * hand1 = malloc(sizeof(deck_t));
  char * cardStr = NULL;
  size_t lnsz = 0;
  card_t curCard;
  
  printf("Enter 7 cards to make a hand\n");
  for (int i = 0; i < 7; i++) {
    getline(&cardStr, &lnsz, stdin);
    curCard = card_from_letters(cardStr[0], cardStr[1]);
    add_card_to(hand1, curCard);
  }
  
  printf("here's the hand:\n");
  print_hand(hand1);

  printf("here's the hand's match counts\n");
  get_match_counts(hand1);

  printf("here's the rest of the deck\n");
  deck_t * restOfDeck = make_deck_exclude(hand1);
  print_hand(restOfDeck);

  printf("here's the hand with an empty card added\n");
  add_empty_card(hand1);
  print_hand(hand1);
  
  free_deck(hand1);
  free_deck(restOfDeck);
  return EXIT_SUCCESS;
}
