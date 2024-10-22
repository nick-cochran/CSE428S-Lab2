//
// Created by Nick Cochran on 9/28/24.
//

#ifndef LAB1_GAME_H
#define LAB1_GAME_H

#include "includes.h"

const int FIRST_PLAYER = 2;

// part 11

// abstract Game class
class Game {
 protected:
    vector<string> players;
    static int askToEndGame();
 public:
    Game(int argc, const char **argv);
    virtual int play() = 0;
    virtual ~Game() = default;
};

#endif //LAB1_GAME_H
