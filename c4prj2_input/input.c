#include <string.h>
#include <ctype.h>
#include "input.h"
#include "future.h"

deck_t * hand_from_string(const char * str, future_cards_t * fc) {
        deck_t* tmp = malloc(sizeof(*tmp));
        tmp->cards = NULL;
        tmp->n_cards = 0;
        for(int i = 0; i < strlen(str); i++) {
                if(isspace(str[i])) {
                        continue;
                } else if(str[i] == '?') {
                        char num[2];
                        int j = 0;
                        i++;
                        while(isdigit(str[i])) {
                                num[j++] = str[i++];
                        }
                        num[j] = '\0';
                        add_future_card(fc, atoi(num), add_empty_card(tmp));
                } else {
                        card_t c = card_from_letters(str[i], str[i+1]);
                        add_card_to(tmp, c);
                        i++;
                }
        }
        if (tmp->n_cards < 5) {
//              perror("short number of card");
                return NULL;
        }
        return tmp;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
        if (f == NULL) {
//              perror("Invalid file");
                return NULL;
        }
        deck_t** input = NULL; // malloc(sizeof(*input));
        size_t n_hand = 0;

        char* line = NULL;
        size_t sz = 0;
        while (getline(&line, &sz, f) >= 0) {
                input = realloc(input, (n_hand + 1) * sizeof(*input));
                input[n_hand] = hand_from_string(line, fc);
                n_hand++;
        }
        *n_hands = n_hand;
        free(line);

        return input;
}
