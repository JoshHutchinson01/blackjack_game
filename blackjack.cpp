#include <iostream>
#include <vector>
#include "card.h"
#include "deck.h"
#include "player.h"
#include "blackjack_fns.h"

using namespace std;

int main() {

    cout << "Welcome to the Blackjack game. \nAt any time press q to quit.\n";

    Deck deck;
    deck.shuffle();

    Player user, computer;

    string response;

    //program currently runs indefinitely
    while(true) {

         //Deal two cards to each player to start the game.
        for(int n=0; n<2;++n) {
            user.add_card(deck.draw());
            computer.add_card(deck.draw());
        }

        //main body if the game - runs if either the user or dealer are still playing
        while(user.is_playing() || computer.is_playing()) {

            if(user.is_playing()) {
                cout << "Your hand is: \n\n";
                user.display();

                if(user.bj_total()>21) {
                    cout << "\nYou went bust!";
                    break;
                } else {
                    cout << "Will you stick or twist? (type s/t): ";
                }

                user_decide(user, response, deck);
            }

            if(computer.is_playing()) {
                computer_decide(computer, deck);
            }

        }

        cout << "\nThe dealer had: \n";
        computer.display();

        if(user_win(user, computer)) {
            cout << "\nYou win!" << endl;
        } else {
            cout << "\nThe house wins!" << endl;
        }

        reshuffle(user, computer, deck);
        cout << "\nNew round starting.\n";
    }

    return 0;
}