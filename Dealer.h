#ifndef DEALER_H
#define DEALER_H

#include "card.h"
#include "deck.h"

#include <vector>
#include <string>
#include <iostream>

class Deck;
class User;

class Dealer: public Player {
    public:
        friend void reshuffle(User &user, Dealer &computer, Deck &deck);

        void decide(Deck &deck) override;
        inline void move(Deck &deck) override {decide(deck);}
        std::ostream& concealed_display(std::ostream&);

        std::ostream& display(std::ostream&) override;
};

#endif
