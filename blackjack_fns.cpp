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
    for(Card card: user.second_hand) {
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
    user.set_paid_out(false);
}

 //Checks if the dealer has natural, if so the player gets a 1x payout if they also have a natural and 0x payout
 //if they don't. If the dealer does not have a natural and the player does they immediately get a 1.5x payout.
void check_for_naturals(User &user, Dealer &computer) {
    if(computer.natural()) {
        cout << "\nThe Dealer has a natural. \n";
        if(user.natural()) {
            user.payout(1);
            cout << "You also have a natural so it is a tie! \n";
        } else {
            user.payout(0);
            cout << "The House wins! \n";
        }
    } else if(user.natural()) {
        user.payout(1.5);
        cout << "You have a natural, you win! \n";
    }
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

//_____________________________________________________________________________________________________________________________

//FUNCTION DEFINITIONS FOR USER.H
//_____________________________________________________________________________________________________________________________


/*Outputs the cards and score of a players hand.*/
ostream& User::display(ostream &os) {
            for(Card card: hand) {
                os << card.get_name() << "\n";
            }
            os << "Total: " << bj_total() << "\n\n";
            return os;
        }
    
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

/*Allows the user to make their move. Will inform the user of their current hand. If they are Bust
playin will be set to false and their turn will end. If not it will ask them to decide to stick
or twist*/
void User::move(Deck &deck) {
    
    cout << "Your hand is: \n\n";
    display(cout);

    check_pair();

    if(has_split_hand == true) {
        split_move();
    } else {
        if(bj_total()>21) {
            cout << "\nYou went bust!";
            set_playing(false);
        } else {
            cout << "Will you stick or twist? (type s/t): ";
            decide(deck);
        }
    }

}

/*Checks whether the user has been given a pair in their original hand. If yes, it asks them
whether they would like to split that pair and if so changes the split pair flag to true.
The split pair flag will etermine what the move action of the player involves. */
void User::check_pair() {
    if(hand.size() == 2 && hand[1].bj_points == hand[0].bj_points) {
        cout << "You have a pair. Would you like to split the pair? (y/n): ";
        string response;
        cin >> response;
        while(true) {            
            if(response == "y") {
                set_split_hand(true);
                split_pair();
                break;
            } else if(response == "n") {
                break;
            }
            cout << "Invalid input, please try again. \n";
        }
    }
}

/*Splits the pair by placing one of the hand cards into the second hand. WILL NEED TO CLEAN UP 
THE SECOND HAND IN RESHUFFLE!!!!!!!!!!*/
void User::split_pair() {
    Card temp = hand[1];
    hand.pop_back();
    second_hand.push_back(temp);
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

/*Adds money to the Users account equal to their current bet multiplied by multiplier. It also flags
 that the user has been paid out in order to only enter one payout sequence.*/
void User::payout(double multiplier) {
    double winnings = bet*multiplier;
    money += winnings;
    set_paid_out(true);
}

//_____________________________________________________________________________________________________________________________

//FUNCTION DEFINITIONS FOR DEALER.H
//_____________________________________________________________________________________________________________________________

/*Makes the dealers decision to stick or twist. The dealer will twist on any total 16 or less
and will stick otherwise.*/
void Dealer::decide(Deck &deck) {
    if(bj_total() <= 16) {
        add_card(deck.draw());
        cout << "\nDealer decided to twist.\n";
        concealed_display(cout);
    } else if(bj_total() > 21) {
        cout << "The Dealer went bust." << "\n";
        set_playing(false);
    } else {
        stick();
        cout << "\nDealer decided to stick.\n";
    }
}

/*Outputs the dealers cards with one card left face down. Overrides the usual display function where all cards 
 are revealed. The dealer does have a method which does this called display_final.*/
std::ostream& Dealer::concealed_display(std::ostream &os) {
    os << "The Dealer has: \n";
    auto iter = get_hand().begin() + 1;
    while(iter != get_hand().end()) {
        os << iter->get_name() << "\n";
        ++iter;
    }
    os << "And one face down card." << "\n\n"; 
    return os;
}

/*Outputs the cards and score of a players hand.*/
ostream& Dealer::display(ostream &os) {
            for(Card card: hand) {
                os << card.get_name() << "\n";
            }
            os << "Total: " << bj_total() << "\n\n";
            return os;
        }

//_______________________________________________________________________________________________________________________________


