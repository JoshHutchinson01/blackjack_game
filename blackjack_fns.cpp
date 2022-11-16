#include "player.h"
#include "deck.h"
#include "card.h"

using namespace std;

void user_decide(Player &user, string &response, Deck &deck) {
    while(true) {
        cin >> response;
        if(response == "t") {
            user.add_card(deck.draw());
            break;
        } else if(response == "s") {
            user.stick();
            break;
        } else {
            cout << "\nInvalid input, please try again, (type s/t): ";
        }
    }
}

void computer_decide(Player &computer, Deck &deck) {
    if(computer.bj_total() <= 14) {
        computer.add_card(deck.draw());
        cout << "\nDealer decided to twist.\n";
    } else {
        computer.stick();
        cout << "\nDealer decided to stick.\n";
    }
}

bool user_win(Player user, Player computer) {
    if(user.bj_total()<=21 && computer.bj_total()>21) {
        return true;
    }else if(user.bj_total() <=21 && user.bj_total()>computer.bj_total()) {
        return true;
    } else {
        return false;
    }
} 

void reshuffle(Player &user, Player &computer, Deck &deck) {
    for(Card card: user.hand) {
        deck.cards.push_back(card);
    }
    for(Card card: computer.hand) {
        deck.cards.push_back(card);
    }
    user.hand.clear();
    computer.hand.clear();
    deck.shuffle();
    user.playing = true;
    computer.playing = true;
}