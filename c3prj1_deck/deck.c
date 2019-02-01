#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"


void print_hand(deck_t * hand){
  for(size_t i = 0; i < hand->n_cards; i++) {
    print_card(*hand->cards[i]);
    printf(" ");
  }
}


int deck_contains(deck_t * d, card_t c) {
  card_t chkCard;
  //check each card in d
  for(int i = 0; i < d->n_cards; i++) {
    //check if the current card = c, return 1 if it does
    chkCard.value = (*d->cards[i]).value;
    chkCard.suit = (*d->cards[i]).suit;
    if ((chkCard.value == c.value)&&(chkCard.suit == c.suit)) {
      return 1;
    }
  }
  //return 0 if there are no matches
  return 0;
}


//function to qsort deckRands based on random members (for use in shuffle)
int randSorter(const void * rand1_vp, const void * rand2_vp) {
  //define cardRand for this function (should probably be in header)
  typedef struct randcard {
    card_t * card_p;
    long int rand;
  } cardRand;

  //define usable pointers to cardRands
  const cardRand * rand1_p = rand1_vp;
  const cardRand * rand2_p = rand2_vp;
  
  //calculate difference between 2 elements
  long int randDiff = rand1_p->rand - rand2_p->rand;
  //use if statement b/c need to return int, not long int
  return randDiff;
}

void shuffle(deck_t * d){
  size_t decksize = d->n_cards;
  //define new struct type 'cardRand'
  typedef struct randcard {
    card_t * card_p;
    long int rand;
  } cardRand;
  //create new array of cardRands called 'deckRands'
  cardRand deckRands[decksize];
  //fill deckRands with the card info from d and a random
  for(size_t i = 0; i < decksize; i++) {
    deckRands[i].card_p = d->cards[i];
    deckRands[i].rand = random();
  }
  //qsort deckRands based on the random members
  qsort(deckRands, decksize, sizeof(cardRand), randSorter);
  //write the cards members back to d in the new (qsorted/shuffled) order
  for (size_t i = 0; i < decksize; i++) {
    d->cards[i] = deckRands[i].card_p;
  }
}

 
void assert_full_deck(deck_t * d) {
  //declare a card to check for
  card_t card;
  //assume a full deck at the start
  int fulldeck = 1;
  //have one loop for suit and a nested loop for value
  for (suit_t i = SPADES; i < NUM_SUITS; i++) {
    for (unsigned j = 2; j <= VALUE_ACE; j++) {
      //define the value the checked for card each loop
      card.value = j;
      card.suit = i;
      int contains = deck_contains(d, card);
      //print any missing card and say the deck is not full
      if (contains == 0) {
	printf("deck is missing %c%c\n",value_letter(card), suit_letter(card));
	fulldeck = 0;
      }
    }
  }
  assert(fulldeck);
}

