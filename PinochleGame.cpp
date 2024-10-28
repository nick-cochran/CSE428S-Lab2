//
// Created by Nick Cochran on 9/29/24.
//

#include "PinochleGame.h"

// initialize the static vector of meld values in an array where each index corresponds to the meld in the enum
const unsigned int PinochleGame::meld_values[] =
        { 10, 20, 40, 40, 40, 60, 80, 100,
          150, 300, 400, 600, 800, 1000, 1500 };



// play function to play a game of Pinochle
int PinochleGame::play() {
    while(true) {
        deck.shuffle();
        deal();
        print_hands_and_melds(cout);
        collect_cards();

        int response = askToEndGame();
        if(response == SUCCESS) {
            return SUCCESS;
        }
    }
}

// Constructor for PinochleGame
PinochleGame::PinochleGame(int argc, const char **argv): Game(argc, argv) {

    for(int i = FIRST_PLAYER; i < argc; ++i) {
        CardSet<Suit, PinochleRank> hand;
        hands.push_back(hand);
    }
}

// deal out the cards to all player_names
void PinochleGame::deal() {
    // deal a packet to each player until deck is empty
    while(!deck.is_empty()) {
        for(auto &hand : hands) {
            this->deck >> hand >> hand >> hand;
        }
    }
}

void PinochleGame::print_hands_and_melds(ostream &ost) {
    for(long unsigned int i = 0; i < hands.size(); ++i) {

        ost << "Player " << player_names[i] << " has hand: " << endl;
        hands[i].print(ost, PINOCHLE_HAND_SIZE);

        // find melds after printing the player's hand
        vector<PinochleMeld> melds = vector<PinochleMeld>();
        suit_independent_eval(hands[i], melds);
        ost << endl;
        ost << player_names[i] << "'s " "melds: ";
        for(PinochleMeld meld : melds) {
            ost << meld << " ";
        }
        ost << endl << endl;
    }
}

void PinochleGame::collect_cards() {
    for(auto& hand : hands) {
        deck.collect(hand);
    }
}

void PinochleGame::suit_independent_eval(const CardSet<Suit, PinochleRank> &hand, vector<PinochleMeld>& melds) {

    CardSet<Suit, PinochleRank> hand_copy(hand);
    vector<Card<Suit, PinochleRank> > CardSet<Suit, PinochleRank>::*cards =
            CardSet<Suit, PinochleRank>::get_cards();

    // create a map of ranks to a vector of suits where each suit represents a card
    std::map<PinochleRank, vector<Suit> > cards_dict = std::map<PinochleRank, vector<Suit> >();

    // create references to make cleaner code
    auto& nines = cards_dict[PinochleRank::nine];
    auto& jacks = cards_dict[PinochleRank::jack];
    auto& queens = cards_dict[PinochleRank::queen];
    auto& kings = cards_dict[PinochleRank::king];
    auto& tens = cards_dict[PinochleRank::ten];
    auto& aces = cards_dict[PinochleRank::ace];

    // initialize each of the vectors
    nines = vector<Suit>(); jacks = vector<Suit>(); queens = vector<Suit>();
    kings = vector<Suit>(); tens = vector<Suit>(); aces = vector<Suit>();

    // push cards into the card dictionary
    for(auto card : hand_copy.*cards) {
        cards_dict[card.rank].push_back(card.suit);
    }

    // Aces meld is possible
    if(aces.size() >= 4) {
        // hand has all aces so it has the meld thousand_aces
        if(aces.size() == 8) {
            melds.push_back(PinochleMeld::thousand_aces);
        } else {
            if(find_all_suits(aces)) {
                melds.push_back(PinochleMeld::hundred_aces);
            }
        }
    }

    // Kings meld is possible
    if(kings.size() >= 4) {
        // hand has all aces so it has the meld thousand_aces
        if(kings.size() == 8) {
            melds.push_back(PinochleMeld::eight_hundred_kings);
        } else {
            if(find_all_suits(kings)) {
                melds.push_back(PinochleMeld::eighty_kings);
            }
        }
    }

    // Queens meld is possible
    if(queens.size() >= 4) {
        // hand has all aces so it has the meld thousand_aces
        if(queens.size() == 8) {
            melds.push_back(PinochleMeld::six_hundred_queens);
        } else {
            if(find_all_suits(queens)) {
                melds.push_back(PinochleMeld::sixty_queens);
            }
        }
    }

    // Jacks meld is possible
    if(jacks.size() >= 4) {
        // hand has all aces so it has the meld thousand_aces
        if(jacks.size() == 8) {
            melds.push_back(PinochleMeld::four_hundred_jacks);
        } else {
            if(find_all_suits(jacks)) {
                melds.push_back(PinochleMeld::forty_jacks);
            }
        }
    }

    // pinochle check
    int jack_diamonds = 0; int queen_spades = 0;
    for(Suit suit : jacks) {
        if(suit == Suit::diamonds) {
            jack_diamonds++;
        }
    }
    for(Suit suit : queens) {
        if(suit == Suit::spades) {
            queen_spades++;
        }
    }
    if(jack_diamonds == 2 && queen_spades == 2) {
        melds.push_back(PinochleMeld::double_pinochle);
    } else if(jack_diamonds == 1 && queen_spades == 1) {
        melds.push_back(PinochleMeld::pinochle);
    }
}

// helper function to see if a vector of suits contains all of the suits
bool PinochleGame::find_all_suits(vector<Suit>& suit_vec) {
    bool clubs = false;
    bool diamonds = false;
    bool hearts = false;
    bool spades = false;

    for(Suit suit : suit_vec) {
        if(suit == Suit::clubs) {
            clubs = true;
        } else if(suit == Suit::diamonds) {
            diamonds = true;
        } else if(suit == Suit::hearts) {
            hearts = true;
        } else if(suit == Suit::spades) {
            spades = true;
        }
    }

    return clubs && diamonds && hearts && spades;
}


// placed at the end because it is large and fairly intuitive
// overload the << operator to print a PinochleMeld according to its value
ostream& operator<<(ostream& ost, const PinochleMeld& meld) {
    switch(meld) {
        case PinochleMeld::dix:
            ost << "dix "
                << PinochleGame::meld_values[static_cast<unsigned int>(PinochleMeld::dix)];
            break;
        case PinochleMeld::off_suit_marriage:
            ost << "off-suit marriage "
                << PinochleGame::meld_values[static_cast<unsigned int>(PinochleMeld::off_suit_marriage)];
            break;
        case PinochleMeld::forty_jacks:
            ost << "forty jacks "
                << PinochleGame::meld_values[static_cast<unsigned int>(PinochleMeld::forty_jacks)];
            break;
        case PinochleMeld::pinochle:
            ost << "pinochle "
                << PinochleGame::meld_values[static_cast<unsigned int>(PinochleMeld::pinochle)];
            break;
        case PinochleMeld::in_suit_marriage:
            ost << "in-suit marriage "
                << PinochleGame::meld_values[static_cast<unsigned int>(PinochleMeld::in_suit_marriage)];
            break;
        case PinochleMeld::sixty_queens:
            ost << "sixty queens "
                << PinochleGame::meld_values[static_cast<unsigned int>(PinochleMeld::sixty_queens)];
            break;
        case PinochleMeld::eighty_kings:
            ost << "eighty kings "
                << PinochleGame::meld_values[static_cast<unsigned int>(PinochleMeld::eighty_kings)];
            break;
        case PinochleMeld::hundred_aces:
            ost << "hundred aces "
                << PinochleGame::meld_values[static_cast<unsigned int>(PinochleMeld::hundred_aces)];
            break;
        case PinochleMeld::in_suit_run:
            ost << "in-suit run "
                << PinochleGame::meld_values[static_cast<unsigned int>(PinochleMeld::in_suit_run)];
            break;
        case PinochleMeld::double_pinochle:
            ost << "double pinochle "
                << PinochleGame::meld_values[static_cast<unsigned int>(PinochleMeld::double_pinochle)];
            break;
        case PinochleMeld::four_hundred_jacks:
            ost << "four hundred jacks "
                << PinochleGame::meld_values[static_cast<unsigned int>(PinochleMeld::four_hundred_jacks)];
            break;
        case PinochleMeld::six_hundred_queens:
            ost << "six hundred queens "
                << PinochleGame::meld_values[static_cast<unsigned int>(PinochleMeld::six_hundred_queens)];
            break;
        case PinochleMeld::eight_hundred_kings:
            ost << "eight hundred kings "
                << PinochleGame::meld_values[static_cast<unsigned int>(PinochleMeld::eight_hundred_kings)];
            break;
        case PinochleMeld::thousand_aces:
            ost << "thousand aces "
                << PinochleGame::meld_values[static_cast<unsigned int>(PinochleMeld::thousand_aces)];
            break;
        case PinochleMeld::in_suit_double_run:
            ost << "in-suit double run "
                << PinochleGame::meld_values[static_cast<unsigned int>(PinochleMeld::in_suit_double_run)];
            break;
    }
    return ost;
}