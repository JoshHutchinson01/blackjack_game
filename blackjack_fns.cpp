#include "player.h"
#include "deck.h"
#include "card.h"
#include "User.h"
#include "Dealer.h"

#include <iostream>
#include <string>

using namespace std;

class Deck;
class Player;
class User;
class Dealer;

/*Compares the user's score to the dealers and returns true if the user wins or false
    if the dealer wins.*/
bool user_win(User user, Dealer computer) {
    if(user.bj_total()<=21 && computer.bj_total()>21) {
        return true;
    }else if(user.bj_total() <=21 && user.bj_total()>computer.bj_total()) {
        return true;
    } else {
        return false;
    }
} 

/*Puts the cards in players hands back in the deck and reshuffles the deck. Resets the
    playing members of the players to true.*/
void reshuffle(User &user, Dealer &computer, Deck &deck) {
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

//FUNCTION DEFINITIONS FROM DECK.H

/*Removes the top card from the deck and returns a copy of that card.*/
Card Deck::draw() {
            Card top = get_card(cards.size()-1);
            cards.pop_back();
            return top;
        }

/*Shuffles the deck.*/
void Deck::shuffle() {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(0,cards.size()-1);

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

//FUNCTION DEFINITIONS FROM PLAYER.H

/*Outputs the cards and score of a players hand.*/
ostream& Player::display(ostream &os) {
            for(Card card: hand) {
                os << card.get_name() << "\n";
            }
            os << "Total: " << bj_total() << "\n\n";
            return os;
        }

/*Calculates the total score of the cards in a Player's hand.*/
int Player::bj_total() {
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

//FUNCTION DEFINITIONS FOR USER.H

/*Accepts and input of s or t from user and excetues the corresponding stick or twist functions.
If a different input is received the user will be prompted to input something valid.*/
void User::decide(Deck &deck) {
    string response;
    while(true) {
        cin >> response;
        if(response == "t") {
            add_card(deck.draw());
            break;
        } else if(response == "s") {
            stick();
            break;
        } else {
            cout << "\nInvalid input, please try again, (type s/t): ";
        }
    }
}

/*Informs the User of their current money and promts them to input a bet amount.
If a valid bet is input then it is subtracted from their total and their current bet
is set to that amount. If not they are prompted to input something valid.*/
void User::make_bet() {
    cout.precision(2);
    cout << "You have \x9C" << fixed << get_money() << ". Place your bet for the current round: ";
    double bet_amount;
    while(true) {
        double bet_amount;
        cin >> bet_amount;
        if(bet_amount<=money && bet_amount != 0) {
            money -= bet_amount;
            bet = bet_amount;
            break;
        } else {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "\nYou cannot bet that amount, please try again: ";
        }
    }
}

/*Adds money to the Users account equal to their current bet multiplied by multiplier.*/
void User::payout(double multiplier) {
    double winnings = bet*multiplier;
    money += winnings;
}

//FUNCTION DEFINITIONS FOR DEALER.H

/*Makes the dealers decision to stick or twist. The dealer will twist on any total 16 or less
and will stick otherwise.*/
void Dealer::decide(Deck &deck) {
    if(bj_total() <= 16) {
        add_card(deck.draw());
        cout << "\nDealer decided to twist.\n";
    } else {
        stick();
        cout << "\nDealer decided to stick.\n";
    }
}

/*Outputs the dealers cards with one card left face down.*/
std::ostream& Dealer::display(std::ostream &os) {
    auto iter = get_hand().begin() + 1;
    while(iter != get_hand().end()) {
        os << iter->get_name() << "\n";
        ++iter;
    }
    os << "And one face down card." << "\n\n"; 
    return os;
}


