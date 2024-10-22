/*
 * PinochleDeck.h
 *
 * Nick Cochran
 * email: c.nick@wustl.edu
 *
 * This header file contains declarations for the PinochleDeck class which inherits the Deck class.  This
 *   contains important operators and in the class: a cards vector, a constructor, and a print function.
 *
 */

#ifndef LAB0_PINOCHLEDECK_H
#define LAB0_PINOCHLEDECK_H

#include "includes.h"
#include "Deck_T.h"
#include "Card_T.h"

enum class PinochleRank {
    nine, jack, queen, king, ten, ace, undefined
};

class PinochleDeck : public Deck<Suit, PinochleRank> {
 public:
    PinochleDeck();
};

ostream& operator<<(ostream& ost, const PinochleRank& pRank);
PinochleRank& operator++(PinochleRank& pRank);

#endif //LAB0_PINOCHLEDECK_H
