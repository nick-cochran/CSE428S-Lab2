//
// Created by Nick Cochran on 9/28/24.
//

#include "Deck_T.h"


// part 8
template<typename Suit, typename Rank>
void Deck<Suit, Rank>::shuffle() {
    std::random_device random_device;
    auto rng = std::mt19937(random_device());

    std::shuffle(this->cards.begin(), this->cards.end(), rng);
}

// part 10
template<typename Suit, typename Rank>
void Deck<Suit, Rank>::collect(CardSet<Suit, Rank>& card_set) {

    if(card_set.is_empty()) {
        return; // nothing to collect
    }

    while(!card_set.is_empty()) {
        card_set >> *this;
    }

}