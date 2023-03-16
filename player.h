#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "deck.h"
#include <vector>

class Deck;
class User;
class Dealer;

class Player {

    public: 
        friend void reshuffle(User &user, Dealer &computer, Deck &deck);

        inline void add_card(Card new_card) {
            hand.push_back(new_card);
        }

        virtual std::ostream& display(std::ostream &);
        int bj_total(); 
        inline void stick() {playing = false;}
        inline bool is_playing() {return playing;}

        virtual void decide(Deck &deck) = 0;

        inline std::vector<Card>& get_hand() {
            return hand;
        }

    private:
        std::vector<Card> hand = {};
        bool playing = true;

};

#endif