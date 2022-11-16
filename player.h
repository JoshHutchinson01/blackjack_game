#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "deck.h"
#include <vector>

class Deck;

class Player {

    public: 

        void add_card(Card new_card) {
            hand.push_back(new_card);
        }

        std::ostream &display(std::ostream &os = std::cout) {
            for(Card card: hand) {
                os << card.get_name() << "\n";
            }
            std::cout << "Total: " << bj_total() << "\n\n";
            return os;
        }

        int bj_total() {
            int total = 0;
            bool has_ace = false;
            for(Card card: hand) {
                if(card.value == "A") {
                    has_ace = true;
                }
                total += card.bj_points;
            }
            if(has_ace && total+10<=21) {
                total += 10;
            }
            return total;
        }

        void stick() {
            playing = false;
        }

        bool is_playing() {
            return playing;
        } 

        friend void reshuffle(Player &user, Player &computer, Deck &deck);

    private:
        std::vector<Card> hand = {};
        bool playing = true;
        int money = 1000;

};

#endif