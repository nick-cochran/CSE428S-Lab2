//
// Created by Nick Cochran on 9/29/24.
//

#include "HoldEmGame.h"

// play function to play a game of Texas Hold 'Em
int HoldEmGame::play() {
    while(true) {
        deck.shuffle();
        state = HoldEmState::preflop;

        deal(); // deal hands
        printHands(cout);
        deal(); // deal flop
        deal(); // deal turn
        deal(); // deal river

        collectCards();
        deck.collect(common_cards);

        int response = askToEndGame();
        if(response == SUCCESS) {
            return SUCCESS;
        }
    }
}

// Constructor for HoldEmGame
HoldEmGame::HoldEmGame(int argc, const char **argv): Game(argc, argv), state(INIT_STATE) {

    for(int i = FIRST_PLAYER; i < argc; ++i) {
        CardSet<Suit, HoldEmRank> hand;
        hands.push_back(hand);
    }
}


void HoldEmGame::deal() {
    const int two_cards = 2;
    switch (state) {
        case HoldEmState::preflop:
            // deal two cards to each player
            for(auto i = 0; i < two_cards; ++i) {
                for(auto& hand : hands) {
                    this->deck >> hand;
                }
            }
            state = HoldEmState::flop;
            break;
        case HoldEmState::flop:
            // deal three cards to the board
            this->deck >> common_cards >> common_cards >> common_cards;
            printBoard(cout);
            state = HoldEmState::turn;
            break;
        case HoldEmState::turn:
            // deal one card to the board
            this->deck >> common_cards;
            printBoard(cout);
            state = HoldEmState::river;
            break;
        case HoldEmState::river:
            // deal one card to the board
            this->deck >> common_cards;
            printBoard(cout);
            state = HoldEmState::undefined;
            break;
        default: // undefined case-- do nothing
            break;
    }
}

//
void HoldEmGame::printHands(ostream &ost) {
    for(long unsigned int i = 0; i < hands.size(); ++i) {
        ost << "Player " << players[i] << " has hand: " << endl;
        hands[i].print(ost, HOLDEM_HAND_SIZE);
    }
}

void HoldEmGame::printBoard(ostream &ost) {
    switch (state) {
        case HoldEmState::flop:
            ost << "BOARD(flop): ";
            common_cards.print(ost, 3);
            break;
        case HoldEmState::turn:
            ost << "BOARD(turn): ";
            common_cards.print(ost, 4);
            break;
        case HoldEmState::river:
            ost << "BOARD(river): ";
            common_cards.print(ost, 5);
            ost << endl;
            break;
        default: // do nothing for all other cases
            break;
    }
}

// collect cards from all players
void HoldEmGame::collectCards() {
    for(auto& hand : hands) {
        deck.collect(hand);
    }
}





// prefix increment operator for HoldEmState enum
//HoldEmState& operator++(HoldEmState& state) {
//    switch (state) {
//        case HoldEmState::preflop:
//            state = HoldEmState::flop;
//            return state;
//        case HoldEmState::flop:
//            state = HoldEmState::turn;
//            return state;
//        case HoldEmState::turn:
//            state = HoldEmState::river;
//            return state;
//        case HoldEmState::river:
//            state = HoldEmState::undefined;
//            return state;
//        default:
//            state = HoldEmState::undefined;
//            return state;
//    }
//}