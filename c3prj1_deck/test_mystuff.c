#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

void printdeck(card_t * deck, size_t decksize) {
  printf("Here's a %zu card deck:\n",decksize);
  for(int i = 0; i < decksize; i++) {
    print_card(deck[i]);
    printf(" ");
  }
  printf("\n");
}
  
int main(void) {
  //store all the cards of a deck in an array
  card_t allcards[52];
  for(suit_t j = SPADES; j < NUM_SUITS; j++) {
    for(unsigned i = 2; i <= VALUE_ACE; i++) {
      allcards[(j*13)+(i-2)].value = i;
      allcards[(j*13)+(i-2)].suit = j;
    }
  }
  printdeck(allcards, 52);

  //create an array of pointers to cards
  card_t * allcards_p[52];
  for(int i = 0; i < 52; i++) {
    allcards_p[i] = &allcards[i];
  }
  //printf("is this a pointer? %d\n",allcards_p[24]);
  //it is

  //store the deck in a deck_t
  deck_t fulldeck;
  fulldeck.n_cards = 0;
  fulldeck.cards = allcards_p;
  
  //work on full deck
  deck_t * fulldeck_p;
  fulldeck_p = &fulldeck;
  fulldeck_p->n_cards = 52;
  fulldeck_p->cards = allcards_p;
  printdeck(*fulldeck_p->cards, fulldeck_p->n_cards);

  //deck_contains test (bc assert_deck_full uses this)
  card_t sixhearts;
  sixhearts.value = 6;
  sixhearts.suit = HEARTS;
  printf("deck_contains 6h: %d\n",deck_contains(fulldeck_p,sixhearts));

  //now test assert_full_deck
  assert_full_deck(fulldeck_p);
  printf("We got a full deck!\n");


  //Build a hand to shuffle
  //print the array of cards
  card_t somecards[5] = {{.value = 6, .suit = CLUBS},
			 {.value = VALUE_QUEEN, .suit = SPADES},
			 {.value = 2, .suit = SPADES},
			 {.value = 0, .suit = HEARTS},
			 {.value = VALUE_ACE, .suit = CLUBS}};
  printdeck(somecards, 5);

  //make the array of pointers
  card_t * somecards_p[5];
  for(int i = 0; i < 5; i++) {
    somecards_p[i] = &somecards[i];
  }

  //make the hand
  deck_t hand = {.n_cards = 5, .cards = somecards_p};
  //make and print the pointer to the hand
  deck_t * hand_p = &hand;
  printdeck(*hand_p->cards, hand_p->n_cards);
  
  //shuffle dat hand and print result
  shuffle(hand_p);
  printf("this should be shuffled:\n");
  printdeck(*hand_p->cards, hand_p->n_cards);
  
  return EXIT_SUCCESS;
}
