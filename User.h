#ifndef USER_H
#define USER_H

#include "card.h"
#include "deck.h"
#include "player.h"

#include <vector>
#include <string>
#include <iostream>

class Deck;
class Dealer; 

class User: public Player {
    public:
        friend void reshuffle(User &user, Dealer &computer, Deck &deck);

        User(): money(100.00), bet(0.00) {};

        inline double get_money() {return money;};

        void move(Deck &deck) override;
        void decide(Deck &deck) override;

        void make_bet();
        void payout(double multiplier);

    private:
        double money;
        double bet;
};

#endif