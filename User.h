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

        User(): money(100.00), bet(0.00), paid_out(false) {};

        inline double get_money() {return money;};

        void move(Deck &deck) override;
        void decide(Deck &deck) override;

        void make_bet();
        void payout(double multiplier);

        bool is_paid_out() {return paid_out;}
        void set_paid_out(bool b) {paid_out = b;}

    private:
        double money;
        double bet;
        bool paid_out;
};

#endif