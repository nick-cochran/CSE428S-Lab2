//
// Created by Nick Cochran on 9/29/24.
//

#include "PinochleGame.h"


// play function to play a game of Pinochle
int PinochleGame::play() {
    while(true) {
        deck.shuffle();
        deal();
        printHands(cout);
        collectCards();

        int response = askToEndGame();
        if(response == SUCCESS) {
            return SUCCESS;
        }
    }
}

// Constructor for PinochleGame
PinochleGame::PinochleGame(int argc, const char **argv): Game(argc, argv) {

    for(int i = FIRST_PLAYER; i < argc; ++i) {
        CardSet<Suit, PinochleRank> hand;
        hands.push_back(hand);
    }
}

void PinochleGame::deal() {

    // deal a packet to each player until deck is empty
    while(!deck.is_empty()) { // TODO make sure this works properly later
        for(auto &hand : hands) {
            this->deck >> hand >> hand >> hand;
        }
    }
}

void PinochleGame::printHands(ostream &ost) {
    for(long unsigned int i = 0; i < hands.size(); ++i) {
        ost << "Player " << players[i] << " has hand: " << endl;
        hands[i].print(ost, PINOCHLE_HAND_SIZE);
    }
}

void PinochleGame::collectCards() {
    for(auto& hand : hands) {
        cout << "collecting Pinochle cards" << endl;
        deck.collect(hand);
    }
}