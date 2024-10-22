/*
 * lab0.cpp
 *
 * Nick Cochran
 * email: c.nick@wustl.edu
 *
 * This source file contains the main function to run the code.
 *
 */

#include "includes.h"
#include "Game.h"
#include "PinochleGame.h"
#include "HoldEmGame.h"
#include <memory>

using namespace std;

int main(int argc, const char **argv);
int usage();
shared_ptr<Game> create(int argc, const char **argv);


// main function to run the code
int main(int argc, const char **argv) {
    string game_name = argv[GAME_NAME];

    if (argc < 2) {
        cout << "Error: not enough arguments" << endl;
        return usage();
    }
    if(game_name != "Pinochle" && game_name != "HoldEm") {
        cout << "Error: invalid game name" << endl;
        return usage();
    }
    if(game_name == "Pinochle" && argc != (INPUTS_PRE_PLAYERS + PINOCHLE_REQUIRED_PLAYERS)) {
        cout << "Error: There must be four players to play Pinochle." << endl;
        return usage();
    }
    if(game_name == "HoldEm" && (argc < (INPUTS_PRE_PLAYERS + HOLDEM_MIN_PLAYERS)
            || argc > (INPUTS_PRE_PLAYERS + HOLDEM_MAX_PLAYERS))) {
        cout << "Error: There must be between 2 and 9 players to play HoldEm." << endl;
        return usage();
     }

    shared_ptr<Game> game = create(argc, argv);
    if(game) {
        return game->play();
    } else {
        cout << "Error: game not created" << endl;
        return NULL_GAME_POINTER;
    }

}

// usage function to return with bad arguments
int usage() {
    cout << "Usage: ./lab1 <game_name> {player1}, {player2}, ..." << endl;
    return INVALID_PROGRAM_ARGUMENTS;
}

// create function to create a game based on the given arguments
shared_ptr<Game> create(int argc, const char **argv) {
    shared_ptr<Game> game;

    string game_name = argv[GAME_NAME];
    if (game_name == "Pinochle") {
        game = make_shared<PinochleGame>(argc, argv);
    } else if (game_name == "HoldEm") {
        game = make_shared<HoldEmGame>(argc, argv);
    }

    return game;
}