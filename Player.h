#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "queue.h"

class Player {
protected: 
    std::string name;
    char symbol;
    Queue<int> moves;   // store positions 1 to 9

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

    Queue<int>& getMoves() {
        return moves;
    }

    virtual int getMove() = 0;
};

class HumanPlayer : public Player {
public:
    HumanPlayer(const std::string& playerName, char playerSymbol)
        : Player(playerName, playerSymbol) {}

    int getMove() override {
        int position;
        std::cout << name << " (" << symbol << "), enter position (1-9): ";
        std::cin >> position;
        return position;
    }
};

#endif