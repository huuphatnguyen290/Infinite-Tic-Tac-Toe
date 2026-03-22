#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <iostream>
#include "Player.h"

class HumanPlayer : public Player {
public:
    // Call the parent Player constructor
    HumanPlayer(const std::string& playerName, char playerSymbol)
        : Player(playerName, playerSymbol) {}

    Position getMove() override {
        int r, c;

        // Ask the human player to enter row and column
        std::cout << name << " (" << symbol << ") enter row and column: ";
        std::cin >> r >> c;

        // Return the move as a Position object
        return Position(r, c);
    }
};

#endif