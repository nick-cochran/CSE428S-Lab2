/*
 * Card_T.cpp
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This source file contains the definitions for the Card struct and a << operator for it.
 */

#include "Card_T.h"

/*
 * TODO fn docs
 */
template<typename Suit, typename Rank>
Card<Suit, Rank>::Card(Suit suit, Rank rank): suit(suit), rank(rank) {}

/*
 * TODO fn docs
 */
template<typename Suit, typename Rank>
ostream& operator<<(ostream& ost, const Card<Suit, Rank>& card) {
    ost << card.rank << card.suit;
    return ost;
}

/*
 * TODO fn docs
 */
template<typename Suit, typename Rank>
bool lt_rank_suit(const Card<Suit, Rank>& card1, const Card<Suit, Rank>& card2) {
    if(card1.rank < card2.rank) {
        return true;
    }
    if(card1.rank == card2.rank && card1.suit < card2.suit) {
        return true;
    }
    return false;
}

/*
 * TODO fn docs
 */
template<typename Suit, typename Rank>
bool lt_suit_rank(const Card<Suit, Rank>& card1, const Card<Suit, Rank>& card2) {
    if(card1.suit < card2.suit) {
        return true;
    }
    if(card1.suit == card2.suit && card1.rank < card2.rank) {
        return true;
    }
    return false;
}
