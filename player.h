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
        friend bool user_win(User user, Dealer computer);

        virtual inline void add_card(Card new_card) {
            hand.push_back(new_card);
        }

        int bj_total(std::vector<Card> h); 
        virtual inline void stick() {playing = false;}
        inline void set_playing(bool b) {playing = b;}
        inline bool is_playing() {return playing;}

        inline bool natural() {return bj_total(hand) == 21;}

        virtual void move(Deck &deck) = 0;
        virtual void decide(Deck &deck) = 0;
        virtual std::ostream& display(std::ostream &) = 0;

        inline std::vector<Card>& get_hand() {
            return hand;
        }

    protected:
        std::vector<Card> hand = {};
        bool playing = true;

};

#endif