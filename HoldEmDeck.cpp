/*
 * HoldEmDeck.cpp
 *
 * Nick Cochran
 * email: c.nick@wustl.edu
 *
 * This source file contains the definitions for the HoldEmDeck class and related operators for the rank enum.
 *
 */

#include "HoldEmDeck.h"

using namespace std;


// pushes back cards into the cards vector for the HoldEmDeck class
HoldEmDeck::HoldEmDeck() {
    for(Suit suit = firstSuit; suit != Suit::undefined; ++suit) {
        for(HoldEmRank rank = HoldEmRank::two; rank != HoldEmRank::undefined; ++rank) {
            cards.push_back(Card(suit, rank));
        }
    }
}


// overloads the << operator for the HoldEmRank enum
ostream& operator<<(ostream& ost, const HoldEmRank& heRank) {
    switch (heRank) {
        case HoldEmRank::two:
            ost << "2";
            return ost;
        case HoldEmRank::three:
            ost << "3";
            return ost;
        case HoldEmRank::four:
            ost << "4";
            return ost;
        case HoldEmRank::five:
            ost << "5";
            return ost;
        case HoldEmRank::six:
            ost << "6";
            return ost;
        case HoldEmRank::seven:
            ost << "7";
            return ost;
        case HoldEmRank::eight:
            ost << "8";
            return ost;
        case HoldEmRank::nine:
            ost << "9";
            return ost;
        case HoldEmRank::ten:
            ost << "10";
            return ost;
        case HoldEmRank::jack:
            ost << "J";
            return ost;
        case HoldEmRank::queen:
            ost << "Q";
            return ost;
        case HoldEmRank::king:
            ost << "K";
            return ost;
        case HoldEmRank::ace:
            ost << "A";
            return ost;
        default:
            ost << "?";
            return ost;
    }
}

// overloads the ++ prefix operator for the HoldEmRank enum
HoldEmRank& operator++(HoldEmRank& pRank) {
    switch (pRank) {
        case HoldEmRank::two:
            return pRank = HoldEmRank::three;
        case HoldEmRank::three:
            return pRank = HoldEmRank::four;
        case HoldEmRank::four:
            return pRank = HoldEmRank::five;
        case HoldEmRank::five:
            return pRank = HoldEmRank::six;
        case HoldEmRank::six:
            return pRank = HoldEmRank::seven;
        case HoldEmRank::seven:
            return pRank = HoldEmRank::eight;
        case HoldEmRank::eight:
            return pRank = HoldEmRank::nine;
        case HoldEmRank::nine:
            return pRank = HoldEmRank::ten;
        case HoldEmRank::ten:
            return pRank = HoldEmRank::jack;
        case HoldEmRank::jack:
            return pRank = HoldEmRank::queen;
        case HoldEmRank::queen:
            return pRank = HoldEmRank::king;
        case HoldEmRank::king:
            return pRank = HoldEmRank::ace;
        case HoldEmRank::ace:
            return pRank = HoldEmRank::undefined;
        default:
            return pRank = HoldEmRank::undefined;
    }
}