//
// Created by Nick Cochran on 9/29/24.
//

#ifndef LAB1_HOLDEMGAME_H
#define LAB1_HOLDEMGAME_H

#include "includes.h"
#include "Game.h"
#include "HoldEmDeck.h"


const int HOLDEM_HAND_SIZE = 2;
const int HOLDEM_RANKS_SIZE = 5;

const int LARGEST_COUNT = 0;
const int SECOND_LARGEST_COUNT = 1;

enum class HoldEmState {
    preflop, flop, turn, river, undefined
};
HoldEmState& operator++(HoldEmState& state);

const HoldEmState INIT_STATE = HoldEmState::preflop;

enum class HoldEmHandRank {
    x_high, pair, two_pair, three_of_a_kind, straight, flush, full_house, four_of_a_kind, straight_flush, undefined
};
ostream& operator<<(ostream& ost, const HoldEmHandRank& hand_rank);


class HoldEmGame : public Game {
    void print_hands(ostream &ost);
    void print_board(ostream &ost);
    void collect_cards();
    HoldEmHandRank holdem_hand_eval(const CardSet<Suit, HoldEmRank>& hand);
    static bool is_straight(vector< Card<Suit, HoldEmRank> > hand);
    static bool is_flush(vector< Card<Suit, HoldEmRank> > hand);
    static vector<int> how_many_same_rank(vector< Card<Suit, HoldEmRank> > hand);

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
