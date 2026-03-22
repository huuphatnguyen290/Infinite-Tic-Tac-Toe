#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "CircularQueue.h"
#include "Position.h"

class Player {
protected:
    std::string name;
    char symbol;
    CircularQueue<Position> moves;

public:
    Player(const std::string& playerName, char playerSymbol)
        : name(playerName), symbol(playerSymbol) {}

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

    virtual Position getMove() = 0;
};

#endif
