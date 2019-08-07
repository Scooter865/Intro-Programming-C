#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  //initialize variables to be used for card checks
  int v;
  int vvalidity = 0;
  //check c value against all possible values
  for (v = 2; v <= VALUE_ACE; v++) {
    if (c.value == v) {
      //indicate true if c value is a valid one
      vvalidity = 1;
      break;
    }
  }
  assert(vvalidity == 1);
  int s;
  int svalidity = 0;
  //check c suit against all possible suits
  for (s = 0; s < NUM_SUITS; s++) {
    if (c.suit == s) {
      //indicate true if c suit is a valid one
      svalidity = 1;
      break;
    }
  }
  assert(svalidity == 1);
}


const char * ranking_to_string(hand_ranking_t r) {
  switch (r) {
  case STRAIGHT_FLUSH:  return "STRAIGHT_FLUSH";  break;
  case FOUR_OF_A_KIND:  return "FOUR_OF_A_KIND";  break;
  case FULL_HOUSE:      return "FULL_HOUSE";      break;
  case FLUSH:           return "FLUSH";           break;
  case STRAIGHT:        return "STRAIGHT";        break;
  case THREE_OF_A_KIND: return "THREE_OF_A_KIND"; break;
  case TWO_PAIR:        return "TWO_PAIR";        break;
  case PAIR:            return "PAIR";            break;
  case NOTHING:         return "NOTHING";         break;
  default:              return "INVALID";
  }
}


char value_letter(card_t c) {
  char x;
  if ((c.value >= 2) && (c.value <= 9)) {
    x = '0' + c.value;
  }
  else {
    switch (c.value) {
    case 10:          x = '0'; break;
    case VALUE_JACK:  x = 'J'; break;
    case VALUE_QUEEN: x = 'Q'; break;
    case VALUE_KING:  x = 'K'; break;
    case VALUE_ACE:   x = 'A'; break;
    default:          x = 'X'; break;
    }
  }
  return x;
}


char suit_letter(card_t c) {
  char x;
  switch (c.suit) {
  case SPADES:   x = 's'; break;
  case HEARTS:   x = 'h'; break;
  case DIAMONDS: x = 'd'; break;
  case CLUBS:    x = 'c'; break;
  default:       x = 'x'; break;
  }
  return x;
}


void print_card(card_t c) {
  char value = value_letter(c);
  char suit = suit_letter(c);
  printf("%c%c",value,suit);
}


card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
  //determine value if it's a number card
  if (value_let >= '2' && value_let <= '9') {
    temp.value = value_let - '0';
  }
  //determine value if it's a face card
  else if (value_let == '0' || value_let == 'J' || value_let == 'Q'
	   || value_let == 'K' || value_let == 'A') {
    switch (value_let) {
    case '0': temp.value = 10;          break;
    case 'J': temp.value = VALUE_JACK;  break;
    case 'Q': temp.value = VALUE_QUEEN; break;
    case 'K': temp.value = VALUE_KING;  break;
    case 'A': temp.value = VALUE_ACE;   break;
    default:  temp.value = 0;
    }
  }
  //error if it's not a valid card
  else {
    printf("invalid value\n");
    exit(EXIT_FAILURE);
  }
  //switch case to assign suit
  switch (suit_let) {
  case 's': temp.suit = SPADES;   break;
  case 'h': temp.suit = HEARTS;   break;
  case 'd': temp.suit = DIAMONDS; break;
  case 'c': temp.suit = CLUBS;    break;
  default:  exit(EXIT_FAILURE);
  }
  return temp;
}


card_t card_from_num(unsigned c) {
  card_t temp;
  unsigned suitNum = c / 13;
  unsigned valNum = c % 13;
  //map spades to c 0-12, hearts to c 13-25, diamonds to c 26-38, clubs to c 39-51
  switch (suitNum) {
  case 0: temp.suit = SPADES;   break;
  case 1: temp.suit = HEARTS;   break;
  case 2: temp.suit = DIAMONDS; break;
  case 3: temp.suit = CLUBS;    break;
  default: exit(EXIT_FAILURE);
  }
  //map from 2 up to A within the 13 cards of each suit
  temp.value = valNum + 2;

  return temp;
}
