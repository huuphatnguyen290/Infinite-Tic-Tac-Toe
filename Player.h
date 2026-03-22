#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "CircularQueue.h"
#include "Position.h"

class Player {
protected:
    // Player name
    std::string name;

    // Player symbol: usually X or O
    char symbol;

    // Queue of this player's moves
    // Used to keep track of the oldest move
    CircularQueue<Position> moves;

public:
    // Constructor to set name and symbol
    Player(const std::string& playerName, char playerSymbol)
        : name(playerName), symbol(playerSymbol) {}

    // Virtual destructor for base class
    virtual ~Player() {}

    std::string getName() const {
        return name;
    }

    char getSymbol() const {
        return symbol;
    }

    CircularQueue<Position>& getMoves() {
        return moves;
    }

    // Each child class must define how to get a move
    virtual Position getMove() = 0;
};

#endif