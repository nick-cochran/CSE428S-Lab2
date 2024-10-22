/*
 * Suit.h
 *
 * Nick Cochran
 * email: c.nick@wustl.edu
 *
 * This header file contains declarations for the Suit enum and relevant operators.
 *
 */

#ifndef LAB0_SUIT_H
#define LAB0_SUIT_H

#include "includes.h"

enum class Suit {clubs, diamonds, hearts, spades, undefined};
const Suit firstSuit = Suit::clubs;

ostream& operator<<(ostream& ost, const Suit& suit);
Suit& operator++(Suit& suit);

#endif //LAB0_SUIT_H
