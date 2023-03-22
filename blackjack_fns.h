#ifndef BLACKJACK_FNS_H
#define BLACKJACK_FNS_H

#include "deck.h"
#include "card.h"

#include "User.h"
#include "Dealer.h"

#include <string>

//declarations of the functions in blackjack_fns.cpp to use in the game.
bool user_win(User user, Dealer computer);
void reshuffle(User &user, Dealer &computer, Deck &deck);
void check_for_naturals(User &user, Dealer &dealer);

#endif