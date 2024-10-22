//
// Created by Nick Cochran on 9/28/24.
//

#include "Game.h"

Game::Game(int argc, const char **argv) {

    for(int i = FIRST_PLAYER; i < argc; i++) {
        players.push_back(argv[i]);
    }
}

int Game::askToEndGame() {
    cout << "Would you like to end the game? (yes/[no]): " << endl;
    string response;
    cin >> response;
    if(response == "yes") {
        cout << "Successfully Ended Game." << endl;
        return SUCCESS;
    } else {
        return CONTINUE_GAME;
    }
}