/*
 * Card_T.h
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This header file contains declarations for the Card struct and a << operator for it.
 */

#ifndef LAB0_CARD_T_H
#define LAB0_CARD_T_H

#include "includes.h"
#include "Suit.h"

template<typename Suit, typename Rank> struct Card {
    Suit suit;
    Rank rank;

    Card(Suit suit, Rank rank);
};

template<typename Suit, typename Rank>
ostream& operator<<(ostream& ost, const Card<Suit, Rank>& card);


#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE

#include "Card_T.cpp"

#endif // TEMPLATE_HEADERS_INCLUDE_SOURCE

#endif //LAB0_CARD_T_H
