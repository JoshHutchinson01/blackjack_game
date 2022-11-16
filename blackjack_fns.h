#include "player.h"
#include "deck.h"
#include "card.h"
#include <string>

//declarations of the functions in blackjack_fns.cpp to use in the game.
void user_decide(Player &user, std::string &response, Deck &deck);
void computer_decide(Player &computer, Deck &deck);
bool user_win(Player player, Player computer);