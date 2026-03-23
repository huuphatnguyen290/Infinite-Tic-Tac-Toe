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
        std::string input;

        while (true) {
            std::cout << name << " (" << symbol << "), enter position (1-9): ";
            std::cin >> input;

            if (input.length() == 1 && input[0] >= '1' && input[0] <= '9') {
                return input[0] - '0';
            }

            std::cout << "Error: input must be an integer from 1 to 9.\n";
        }
    }
};

#endif