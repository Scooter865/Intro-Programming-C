#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"

int int main(void) {
	deck_t * hand1 = malloc(sizeof(deck_t));
	char * cardStr = NULL;
	size_t lnsz = 0;
	card_t curCard;

	for (int i = 0, i < 7, i++) {
		getline(&cardStr, &lnsz, stdin);
		curCard = card_from_letters(cardStr[0], cardStr[1]);
		add_card_to(hand1, curCard);
	}

	printf("here's the hand:\n");
	print_hand(hand1);

	free_deck(hand1);
	return EXIT_SUCCESS;
}