//
// Created by Nick Cochran on 9/29/24.
//

#ifndef LAB1_HOLDEMGAME_H
#define LAB1_HOLDEMGAME_H

#include "includes.h"
#include "Game.h"
#include "HoldEmDeck.h"

// part 13

enum class HoldEmState {
    preflop, flop, turn, river, undefined
};
const HoldEmState INIT_STATE = HoldEmState::preflop;

HoldEmState& operator++(HoldEmState& state);

const int HOLDEM_HAND_SIZE = 2;


class HoldEmGame : public Game {
    void printHands(ostream &ost);
    void printBoard(ostream &ost);
    void collectCards();
 protected:
    HoldEmState state;
    HoldEmDeck deck;
    vector< CardSet<Suit, HoldEmRank> > hands;
    CardSet<Suit, HoldEmRank> common_cards;
    virtual void deal();
 public:
    HoldEmGame(int argc, const char **argv);
    virtual int play();
};

#endif //LAB1_HOLDEMGAME_H
