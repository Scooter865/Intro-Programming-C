#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"


void print_hand(deck_t * hand){
  for(size_t i = 0; i < hand->n_cards; i++) {
    print_card(*hand->cards[i]);
    printf(" ");
  }
  printf("\n");
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


/*Add the particular card to the given deck (which will involve
reallocing the array of cards in that deck). Assuming that deck
is already alloc'd because this function doesn't return anything*/
void add_card_to(deck_t * deck, card_t c) {
  deck->n_cards++;
  if (deck->n_cards == 1) {
    deck->cards = malloc(sizeof(card_t*));
  }
  deck->cards = realloc(deck->cards, deck->n_cards * sizeof(card_t*)); //allocate space for the new card pointer
  deck->cards[deck->n_cards-1] = malloc(sizeof(card_t)); //allocate space for the card
  *deck->cards[deck->n_cards-1] = c;
}


/*Add a card whose value and suit are both 0, and return a pointer
to it in the deck. This will add an invalid card to use as a
placeholder for an unknown card.*/
card_t * add_empty_card(deck_t * deck) {
  card_t empty;
  empty.value = 0;
  empty.suit = 0;
  add_card_to(deck, empty);
  return deck->cards[deck->n_cards-1];
}


/*Create a deck that is full EXCEPT for all the cards that appear in 
excluded_cards. For example, if excluded_cards has Kh and Qs, you would 
create a deck with 50 cards---all of them except Kh and Qs. You will
need to use malloc to allocate this deck. (You will want this for the 
next function). Don't forget you wrote card_t card_from_num(unsigned c)
in Course 2 and int deck_contains(deck_t * d, card_t c) in Course 3!
They might be useful here.*/
deck_t * make_deck_exclude(deck_t * excluded_cards) {
  deck_t * builtDeck = malloc(sizeof(deck_t)); //Allocate a deck_t
  card_t card;
  for (size_t i = 0; i < 52; i++) { //Iterate through all cards
    card = card_from_num(i);
    if (deck_contains(excluded_cards, card) == 0) {
      add_card_to(builtDeck, card); //realloc pointer array and allocating card_t done in add_card_to
    }
  }
  return builtDeck;
 }


/*This function takes an array of hands (remember that we use deck_t to
represent a hand). It then builds the deck of cards that remain after those
cards have been removed from a full deck. For example, if we have two hands:
      Kh Qs ?0 ?1 ?2 ?3 ?4
      As Ac ?0 ?1 ?2 ?3 ?4
then this function should build a deck with 48 cards (all but As Ac Kh Qs).
You can just build one deck with all the cards from all the hands 
(remember you just wrote add_card_to), and then pass it to make_deck_exclude.*/
deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
  deck_t * exclusionDeck = malloc(sizeof(deck_t)); //allocate exclusion deck
  card_t exclusionCard;
  for (size_t i = 0; i < n_hands; i++) { //iterate through each hand (n_hands)
    for (size_t j = 0; j < hands[i]->n_cards; j++) { //iterate through each card in a hand
      exclusionCard = *(hands[i]->cards[j]);
      if (deck_contains(exclusionDeck, exclusionCard) == 0) {
        add_card_to(exclusionDeck, exclusionCard); //add NEW cards found in hands to exclusion deck
      }
    }
  }
  deck_t * remainingDeck = make_deck_exclude(exclusionDeck);
  free_deck(exclusionDeck);
  return remainingDeck;
}


/*Free the memory allocated to a deck of cards. For example, if you do
  deck_t * d = make_excluded_deck(something);
  free_deck(d);
it should free all the memory allocated by make_excluded_deck. Once you have
written it, add calls to free_deck anywhere you need to to avoid memory leaks.*/
void free_deck(deck_t * deck) {
  for (size_t i = 0; i < deck->n_cards; i++) {
    free(deck->cards[i]); //Free each card_t
  }
  free(deck->cards); //Free the array of card_t*
  free(deck); //Free the deck_t
}

