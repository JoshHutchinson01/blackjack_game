#include <iostream>
#include <vector>
#include "card.h"
#include "deck.h"
#include "User.h"
#include "Dealer.h"
#include "blackjack_fns.h"

using namespace std;

int main() {

    cout << "Welcome to the Blackjack game. \n";

    Deck deck;
    deck.shuffle();
    
    User user;
    Dealer computer;

    //program currently runs indefinitely
    while(true) {

        user.make_bet();

         //Deal two cards to each player to start the game.
        for(int n=0; n<2;++n) {
            user.add_card(deck.draw());
            computer.add_card(deck.draw());
        }

        //main body if the game - runs if either the user or dealer are still playing
        while(user.is_playing() || computer.is_playing()) {

            if(user.is_playing()) {
                cout << "Your hand is: \n\n";
                user.display(cout);

                if(user.bj_total()>21) {
                    cout << "\nYou went bust!";
                    break;
                } else {
                    cout << "Will you stick or twist? (type s/t): ";
                }

                user.decide(deck);
            }

            if(computer.is_playing()) {
                computer.decide(deck);
            }

        }

        cout << "\nThe dealer had: \n";
        computer.display(cout);

        if(user_win(user, computer)) {
            cout << "\nYou win!" << endl;
            user.payout(2);
        } else {
            cout << "\nThe house wins!" << endl;
        }

        reshuffle(user, computer, deck);
        cout << "\nNew round starting. Continue? (y/n): ";

        string response;
        cin >> response;
        if(response == "n") {break;}
    }

    return 0;
}