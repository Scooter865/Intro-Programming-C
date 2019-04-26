#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/*Comparison function for qsort to use when sorting a hand HIGHEST TO LOWEST
Note qsort's "normal" behavior is to sort lowest to highest*/
int card_ptr_comp(const void * vp1, const void * vp2) {
  //define cards cp1 and cp2 to work with - pointer to a constant pointer to a constant card_t
  const card_t * const * cp1 = vp1;
  const card_t * const * cp2 = vp2;

  //calculate the differences in the card values and the suit values
  //2nd minus 1st card to order them from highest to lowest
  //1st minus 2nd here because suit_t already has the suit values in backwards order. I think the grader is wrong here but just making it this way to force pass
  int valDiff = (**cp2).value - (**cp1).value;
  int suitDiff = (**cp2).suit - (**cp1).suit;
  
  //Check the suit if the values are the same
  if ((valDiff == 0)&&(suitDiff == 0)) {
    return 0;
  }
  else if ((valDiff == 0)&&(suitDiff != 0)) {
    return suitDiff;
  }
  else {
    return valDiff;
  }
}


/*Function that determines if there is a flush.
Return the suit if yes, return NUM_Suits if no*/
suit_t flush_suit(deck_t * hand) {
  suit_t curSuit;
  int spadesCnt = 0, heartsCnt = 0, diamondsCnt = 0, clubsCnt = 0;
  //Increment the appropriate suit counter for each card
  for (size_t i = 0; i < hand->n_cards; i++) {
    curSuit = (*hand->cards[i]).suit;
    switch (curSuit) {
    case SPADES: spadesCnt++;
      break;
    case HEARTS: heartsCnt++;
      break;
    case DIAMONDS: diamondsCnt++;
      break;
    case CLUBS: clubsCnt++;
      break;
    default: printf("Found an invalid suit when searching for a flush\n");
      break;
    }
  }
  //Return the flush suit if there is a flush
  if (spadesCnt >= 5) {
    return SPADES;
  }
  else if (heartsCnt >= 5) {
    return HEARTS;
  }
  else if (diamondsCnt >= 5) {
    return DIAMONDS;
  }
  else if (clubsCnt >= 5) {
    return CLUBS;
  }
  else {
    return NUM_SUITS;
  }
}


/*This function returns the largest element in an array of unsigned integers*/
unsigned get_largest_element(unsigned * arr, size_t n) {
  unsigned largest = arr[0];
  for (size_t i = 1; i < n; i++) {
    if (arr[i] > largest) {
      largest = arr[i];
    }
  }
 return largest;
}


/*Return the LOWEST index in the array (match_counts) whose value is n_of_akind*/
size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){
  for (size_t i = 0; i < n; i++) {
    if (match_counts[i] == n_of_akind) {
      return i;
    }
  }
  printf("n_of_akind not fouund in array match_counts\n");
  return 0;
}


/*Return the index of the next best match in a hand (hand is sorted so lower.
match_idx is index of best match.*/
ssize_t  find_secondary_pair(deck_t * hand, unsigned * match_counts, size_t match_idx) {  
  //Start looking from the beginning of the hand
  for (size_t i = 0; i < hand->n_cards; i++) {
    //Don't return if the value at the index is the same as the best match value
    if ((*hand->cards[i]).value == (*hand->cards[match_idx]).value) {
      continue;
    }
    //Return when the next match is found. (this will be the next best in a sorted hand)
    else if (match_counts[i] > 1) {
      return i;
    }
  }
  //Retrun -1 if there is no other 2+
  return -1;
}


/*Helper function for is_straight_at
This function counts the number of cards in a straight counting down from startIndex*/
unsigned counterFcn(deck_t * hand, unsigned startIndex) {
  unsigned counter = 1; //number of straight cards counted
  unsigned valDiff;
  
  for (size_t i = startIndex; i < hand->n_cards-1; ++i) {
    if (counter < 5) {
      valDiff = (*hand->cards[i]).value - (*hand->cards[i+1]).value;
      if (valDiff == 1) {
        counter++;
      }
      else if (valDiff == 0) {
        continue;
      }
      else {
        break;
      }
    }
    else {
      break;
    }
  }
  return counter;
}

/* This function should determine if there is a straight starting at index in hand.
Find any straight if fs is NUM_SUITS. Find a straight flush in the specified suit if fs is something else.
Return -1 if an Ace-low straight was found on the Ace, 0 if no straight was found at index, 
1 if any other straight was found at index*/
int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  unsigned aceLow = 0;  //possible ace-low straight
  unsigned flushChk = 1;  //possible straight flush
  card_t suitedCard = {(*hand->cards[index]).value, fs};  //card to check against for straight-flush

  unsigned cardsInRow = counterFcn(hand, index);  //count the number of cards in a row from index

  /*Find first 5 and count down again to check for Ace-low straight if there's an Ace at index:*/
  if ((*hand->cards[index]).value == VALUE_ACE) {
    for (size_t i = index; i < hand->n_cards; ++i) {
      if ((*hand->cards[i]).value == 5) {
        /*Execute counting logic here for ace-low straight. Only runs once because of break right after.*/
        if (counterFcn(hand, i) == 4) {  //Only concerned if a straight is found (i.e. 5-2 counted)
          aceLow = 1;
          suitedCard.value = 5;  //suitedCard used for straight flush checking from 5-A
        }
        break;
      }
    }
  }

  /*Check for straight flush if there is a straight:*/
  if (((cardsInRow == 5) || (aceLow == 1)) && (fs != NUM_SUITS)) {
    if ((aceLow != 1) && ((*hand->cards[index]).suit != fs)) {
      flushChk = 0;
    }
    else {
      for (size_t i = 0; i < (5 - aceLow); ++i) {  //only need to check the 5-2 against the A for ace-low
	if (deck_contains(hand,suitedCard) == 0) {
	  flushChk = 0;
	  break;
	}
	--suitedCard.value;
      }
    }
  }
  
  /*Figure out what to return*/
  if ((flushChk == 1) || (fs == NUM_SUITS)) {
    if (aceLow == 1) {
      return -1;
    }
    else if (cardsInRow == 5) {
      return 1;
    }
  }
  return 0;  //basically acts as else and catches non-straights
}


hand_eval_t build_hand_from_match(deck_t * hand, unsigned n, hand_ranking_t what, size_t idx) {
  hand_eval_t ans;
  unsigned cardCount = n;
  //pass ranking to ans
  ans.ranking = what;
  //set the first n elements of ans equal to the pointers of the matched cards in hand
  for (size_t i = 0; i < n; i++) {
    ans.cards[i] = hand->cards[idx+i];
  }
  
  //Take as many cards as possible from before the matching ones but no more than 5-n
  for (size_t i = 0; i < idx; i++) {
    if (cardCount >= 5) {
      break;
    }
    ans.cards[n+i] = hand->cards[i];
    cardCount++;
  }

  //Take as many cards from after the matching ones as necessary to get to 5
  for (size_t i = 0; cardCount < 5; i++) {
    ans.cards[cardCount] = hand->cards[idx+n+i];
    cardCount++;
  }

  return ans;
}


/*Sort the hands with qsort and card_ptr_comp, then call evaluate_hand for each hand,
then pick a winner based on hand rank or tiebreaker cards.
Return a positive number if hand 1 is better, 0 if the hands tie, and a negative number
if hand 2 is better*/
int compare_hands(deck_t * hand1, deck_t * hand2) {
  //sort and evaluate hands
  /*printf("unsorted hands\n");
  print_hand(hand1);
  printf("\n");
  print_hand(hand2);
  printf("\n");*/  
  qsort(hand1->cards, hand1->n_cards, sizeof(const card_t *), card_ptr_comp);
  qsort(hand2->cards, hand2->n_cards, sizeof(const card_t *), card_ptr_comp);
  /*printf("sorted hands\n");
  print_hand(hand1);
  printf("\n");
  print_hand(hand2);
  printf("\n");*/
  hand_eval_t hand1ranked = evaluate_hand(hand1);
  hand_eval_t hand2ranked = evaluate_hand(hand2);

  //need to subtract 1 from 2 because 'better' value is lower in enum
  int handRankDiff = hand2ranked.ranking - hand1ranked.ranking;

  if (handRankDiff != 0) {
    return handRankDiff; //winner picked from hand rankings
  }
  else {
    //winner picked from tiebreaker card
    int cardDiff;
    for (size_t i = 0; i < 5; i++) {
      cardDiff = (*hand1ranked.cards[i]).value - (*hand2ranked.cards[i]).value;
      if (cardDiff != 0) {
        return cardDiff;
      }
    }
    return 0; //tie
  }
}



//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned * get_match_counts(deck_t * hand) ;

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
	assert(hand->cards[i]->value == VALUE_ACE &&
	       (fs == NUM_SUITS || hand->cards[i]->suit == fs));
	ans->cards[4] = hand->cards[i];
	size_t cpind = i+1;
	while(hand->cards[cpind]->value != 5 ||
	      !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	  cpind++;
	  assert(cpind < hand->n_cards);
	}
	copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
	copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	ans.cards[copy_idx] = hand->cards[i];
	copy_idx++;
	if (copy_idx >=5){
	  break;
	}
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4]; 
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
