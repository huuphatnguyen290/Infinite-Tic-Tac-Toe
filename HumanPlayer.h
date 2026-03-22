#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <iostream>
#include "Player.h"

class HumanPlayer : public Player {
public:
    HumanPlayer(const std::string& playerName, char playerSymbol)
        : Player(playerName, playerSymbol) {}

    Position getMove() override {
        int r, c;
        std::cout << name << " (" << symbol << ") enter row and column: ";
        std::cin >> r >> c;
        return Position(r, c);
    }
};

#endif
