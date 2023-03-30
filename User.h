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

        User(): money(100.00), bet(0.00), paid_out(false), split_hand(false) {};

        inline double get_money() {return money;};

        void move(Deck &deck) override;
        void decide(Deck &deck) override;
        std::ostream& display(std::ostream&) override;
        void check_pair();
        void split_move(Deck &deck);

        void make_bet();
        void payout(double multiplier);

        bool is_paid_out() {return paid_out;}
        void set_paid_out(bool b) {paid_out = b;}
        bool has_split_hand() {return split_hand;}
        void set_split_hand(bool b) {split_hand = b;}

        void split_pair();

    private:
        double money;
        double bet;
        bool paid_out;
        bool split_hand;
        std::vector<Card> second_hand;
};

#endif