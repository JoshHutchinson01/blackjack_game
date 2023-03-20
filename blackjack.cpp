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

        //Informs the user of the Dealers's hand. 
        computer.concealed_display(cout);

        //While the user is still playing they make a move.
        while(user.is_playing()) {
            user.move(deck);
        }

        //Com. turn happens after the user turn. While the computer is still playing, it makes a move
        while(computer.is_playing()) {
            computer.move(deck);
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