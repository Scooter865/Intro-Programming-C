#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "future.h"
#include "input.h"

void add_future_card (future_cards_t* fc, size_t index, card_t* ptr) {
        if (index >= fc->n_decks) {
                fc->decks = realloc(fc->decks, (index + 1) * sizeof(*fc->decks));
                while (index >= fc->n_decks) {
                        fc->decks[fc->n_decks].cards = NULL;
                        fc->decks[fc->n_decks].n_cards = 0;
                        fc->n_decks++;
                }
        }
        add_card_to(&fc->decks[index], *ptr);
}

void future_cards_from_deck (deck_t* deck, future_cards_t* fc) {
        if (deck->n_cards < fc->n_decks) {
//              perror("Need more cards in deck");
                return;
        }
        for (int i = 0; i < fc->n_decks; i++) {
                if (fc->decks[i].n_cards == 0) {continue;}
                for (int j = 0; j < fc->decks[i].n_cards; j++) {
                        fc->decks[i].cards[j]->suit = deck->cards[i]->suit;
                        fc->decks[i].cards[j]->value = deck->cards[i]->value;
                }
        }
}
