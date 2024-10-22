/*
 * Card_T.cpp
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This source file contains the definitions for the Card struct and a << operator for it.
 */

#include "Card_T.h"

using namespace std;

template<typename Suit, typename Rank>
Card<Suit, Rank>::Card(Suit suit, Rank rank): suit(suit), rank(rank) {}


template<typename Suit, typename Rank>
ostream& operator<<(ostream& ost, const Card<Suit, Rank>& card) {
    ost << card.suit;
    ost << card.rank;
    return ost;
}
