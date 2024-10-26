//
// Created by Nick Cochran on 9/29/24.
//

#include "HoldEmGame.h"

// play function to play a game of Texas Hold 'Em
int HoldEmGame::play() {
    while(true) {
        deck.shuffle();
        state = HoldEmState::preflop;

        deal(); // deal hands
        print_hands(cout);

        holdem_hand_eval(deck); // temp wrong use to make CLion happy

        deal(); // deal flop
        deal(); // deal turn
        deal(); // deal river

        collect_cards();
        deck.collect(common_cards);

        int response = askToEndGame();
        if(response == SUCCESS) {
            return SUCCESS;
        }
    }
}

// Constructor for HoldEmGame
HoldEmGame::HoldEmGame(int argc, const char **argv): Game(argc, argv), state(INIT_STATE) {

    for(int i = FIRST_PLAYER; i < argc; ++i) {
        CardSet<Suit, HoldEmRank> hand;
        hands.push_back(hand);
    }
}


void HoldEmGame::deal() {
    const int two_cards = 2;
    switch (state) {
        case HoldEmState::preflop:
            // deal two cards to each player
            for(auto i = 0; i < two_cards; ++i) {
                for(auto& hand : hands) {
                    this->deck >> hand;
                }
            }
            state = HoldEmState::flop;
            break;
        case HoldEmState::flop:
            // deal three cards to the board
            this->deck >> common_cards >> common_cards >> common_cards;
            print_board(cout);
            state = HoldEmState::turn;
            break;
        case HoldEmState::turn:
            // deal one card to the board
            this->deck >> common_cards;
            print_board(cout);
            state = HoldEmState::river;
            break;
        case HoldEmState::river:
            // deal one card to the board
            this->deck >> common_cards;
            print_board(cout);
            state = HoldEmState::undefined;
            break;
        default: // undefined case-- do nothing
            break;
    }
}

//
void HoldEmGame::print_hands(ostream &ost) {
    for(long unsigned int i = 0; i < hands.size(); ++i) {
        ost << "Player " << players[i] << " has hand: " << endl;
        hands[i].print(ost, HOLDEM_HAND_SIZE);
    }
}

void HoldEmGame::print_board(ostream &ost) {
    switch (state) {
        case HoldEmState::flop:
            ost << "BOARD(flop): ";
            common_cards.print(ost, 3);
            break;
        case HoldEmState::turn:
            ost << "BOARD(turn): ";
            common_cards.print(ost, 4);
            break;
        case HoldEmState::river:
            ost << "BOARD(river): ";
            common_cards.print(ost, 5);
            ost << endl;
            break;
        default: // do nothing for all other cases
            break;
    }
}

// collect cards from all players
void HoldEmGame::collect_cards() {
    for(auto& hand : hands) {
        deck.collect(hand);
    }
}


HoldEmHandRank HoldEmGame::holdem_hand_eval(const CardSet<Suit, HoldEmRank>& hand) {

    CardSet<Suit, HoldEmRank> hand_copy(hand);
    vector<Card<Suit, HoldEmRank> > CardSet<Suit, HoldEmRank>::*hand_cards =
            CardSet<Suit, HoldEmRank>::get_cards();

    vector< Card<Suit, HoldEmRank> > cards = hand_copy.*hand_cards;


    std::sort(cards.begin(), cards.end(),
              [](Card<Suit, HoldEmRank> a, Card<Suit, HoldEmRank> b) {
                        return lt_rank_suit(a,b);
                    });

    if(cards.size() < HOLDEM_RANKS_SIZE || cards.size() > HOLDEM_RANKS_SIZE) {
        return HoldEmHandRank::undefined;
    }

    bool straight = is_straight(cards);
    bool flush = is_flush(cards);
    vector<int> counts = how_many_same_rank(cards); // counts must have 2 ints at minimum

    if(straight && flush) {
        return HoldEmHandRank::straight_flush;
    }
    // NOTE: some of these values are hardcoded on purpose, because the return makes it clear what it means
    if(counts[LARGEST_COUNT] == 4) {
        return HoldEmHandRank::four_of_a_kind;
    }
    if(counts[LARGEST_COUNT] == 3 && counts[SECOND_LARGEST_COUNT] == 2) {
        return HoldEmHandRank::full_house;
    }
    if(flush) {
        return HoldEmHandRank::flush;
    }
    if(straight) {
        return HoldEmHandRank::straight;
    }
    if(counts[LARGEST_COUNT] == 3) {
        return HoldEmHandRank::three_of_a_kind;
    }
    if(counts[LARGEST_COUNT] == 2 && counts[SECOND_LARGEST_COUNT] == 2) {
        return HoldEmHandRank::two_pair;
    }
    if(counts[LARGEST_COUNT] == 2) {
        return HoldEmHandRank::pair;
    }
    return HoldEmHandRank::x_high;

}

// return true if the hand is a straight
bool HoldEmGame::is_straight(vector< Card<Suit, HoldEmRank> > hand) {
    HoldEmRank start = hand[0].rank;


    if(start == HoldEmRank::jack || start == HoldEmRank::queen || start == HoldEmRank::king) {
        return false; // cannot have a straight starting at these ranks
    } else if(start == HoldEmRank::ace) {
        start = HoldEmRank::two; // prefix operator will not work for a low ace
    } else {
        ++start;
    }

    for(int i = 1; i < HOLDEM_RANKS_SIZE; i++) {
        // if the next card in hand is not the next card in the straight
        if(hand[i].rank != start) {
            return false;
        }
        ++start;
    }

    return true;
}

// return true if the hand is a flush
bool HoldEmGame::is_flush(vector< Card<Suit, HoldEmRank> > hand) {
    Suit to_match = hand[0].suit;

    for(auto card : hand) {
        if(card.suit != to_match) {
            return false;
        }
    }

    // all cards matched suit
    return true;
}

// return a vector holding the number of cards with the same rank
// for example if you have a hand of {J, J, J, Q, K} it will return 3, 1, 1
vector<int> HoldEmGame::how_many_same_rank(vector< Card<Suit, HoldEmRank> > hand) {
    auto iter1 = hand.begin();
    auto iter2 = hand.begin()++;
    int count = 1;
    vector<int> counts = vector<int>();


    while(iter1 != hand.end()) {
        if(iter2 != hand.end() && (*iter1).rank == (*iter2).rank) {
            count++;
            iter2++;
        } else {
            counts.push_back(count);
            count = 1;
            iter1 = iter2;
            if(iter2 != hand.end()) {
                iter2++;
            }
        }
    }

    // getting a warning on std::greater but using cppreference example, so ignoring it
    std::sort(counts.begin(), counts.end(), std::greater<int>());
}


// placed at the end because it is large and fairly intuitive
// overload the << operator to print a string representative of a hold em hand rank
ostream& operator<<(ostream& ost, const HoldEmHandRank& hand_rank) {
    switch (hand_rank) {
        case HoldEmHandRank::x_high:
            ost << "High Card ";
            break;
        case HoldEmHandRank::pair:
            ost << "Pair ";
            break;
        case HoldEmHandRank::two_pair:
            ost << "Two Pair ";
            break;
        case HoldEmHandRank::three_of_a_kind:
            ost << "Three of a Kind ";
            break;
        case HoldEmHandRank::straight:
            ost << "Straight ";
            break;
        case HoldEmHandRank::flush:
            ost << "Flush ";
            break;
        case HoldEmHandRank::full_house:
            ost << "Full House ";
            break;
        case HoldEmHandRank::four_of_a_kind:
            ost << "Four of a Kind ";
            break;
        case HoldEmHandRank::straight_flush:
            ost << "Straight Flush ";
            break;
        default:
            ost << "Undefined ";
            break;
    }
}