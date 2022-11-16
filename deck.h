#ifndef DECK_H
#define DECK_H

#include <vector>
#include <random>
#include <iostream>
#include "card.h"
#include "player.h"

class Player;

class Deck {

    public:

        Card get_card(unsigned index) const {
            return cards[index];
        }

        Card draw() {
            Card top = get_card(cards.size()-1);
            cards.pop_back();
            return top;
        }

        void shuffle() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0,cards.size()-1);

            int rand1=0, rand2=0;
            Card temp;

            for(int i=0; i<100; ++i) {
                rand1 = dis(rd);
                rand2 = dis(rd);
                temp = cards[rand1];
                cards[rand1] = cards[rand2];
                cards[rand2] = temp;
            }
        }

        friend void reshuffle(Player &user, Player &computer, Deck &deck);

    private:
        std::vector<Card> cards = {{"A","H",1},{"2","H",2},{"3","H",3},{"4","H",4},{"5","H",5},{"6","H",6},{"7","H",7},{"8","H",8},
                                    {"9","H",9},{"10","H",10},{"J","H",10},{"Q","H",10},{"K","H",10},{"A","D",1},{"2","D",2}
                                    ,{"3","D",3},{"4","D",4},{"5","D",5},{"6","D",6},{"7","D",7},{"8","D",8},{"9","D",9},
                                    {"10","D",10},{"J","D",10},{"Q","D",10},{"K","D",10},{"A","C",1},{"2","C",2},{"3","C",3},
                                    {"4","C",4},{"5","C",5},{"6","C",6},{"7","C",7},{"8","C",8},{"9","C",9},{"10","C",10},
                                    {"J","C",10},{"Q","C",10},{"K","C",10},{"A","S",1},{"2","S",2},{"3","S",3},{"4","S",4}
                                    ,{"5","S",5},{"6","S",6},{"7","S",7},{"8","S",8},{"9","S",9},{"10","S",10},{"J","S",10},
                                    {"Q","S",10},{"K","S",10}};
};

#endif