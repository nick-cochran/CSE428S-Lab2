/*
 * HoldEmDeck.h
 *
 * Nick Cochran
 * email: c.nick@wustl.edu
 *
 * This header file contains declarations for the HoldEmDeck class which inherits the Deck class.  This
 *   contains important operators and in the class: a cards vector, a constructor, and a print function.
 *
 */

#ifndef LAB0_HOLDEMDECK_H
#define LAB0_HOLDEMDECK_H

#include "includes.h"
#include "Deck_T.h"
#include "Card_T.h"

enum class HoldEmRank {
    two, three, four, five, six, seven, eight, nine, ten,
        jack, queen, king, ace, undefined
};
ostream& operator<<(ostream& ost, const HoldEmRank& heRank);
HoldEmRank& operator++(HoldEmRank& heRank);


class HoldEmDeck : public Deck<Suit, HoldEmRank> {
 public:
    HoldEmDeck();
};

#endif //LAB0_HOLDEMDECK_H
