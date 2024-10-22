//
// Created by Nick Cochran on 9/29/24.
//

#ifndef LAB1_PINOCHLEGAME_H
#define LAB1_PINOCHLEGAME_H

#include "includes.h"
#include "Game.h"
#include "PinochleDeck.h"

// part 12

const int PINOCHLE_HAND_SIZE = 3;

class PinochleGame : public Game {
    void printHands(ostream &ost);
    void collectCards();
 protected:
    PinochleDeck deck;
    vector< CardSet<Suit, PinochleRank> > hands;
    virtual void deal();
 public:
    PinochleGame(int argc, const char **argv);
    virtual int play();
};

#endif //LAB1_PINOCHLEGAME_H
