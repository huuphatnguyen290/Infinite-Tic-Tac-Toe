#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "queue.h"

class Player {
protected: 
    std::string name;   
    char symbol;        // symbol can either be 'X' or 'O'
    Queue<int> moves;   // store positions 1 to 9

public:
    // Parameterized constructor
    Player(const std::string& playerName, char playerSymbol)
        : name(playerName), symbol(playerSymbol) {}

    // Destructor
    virtual ~Player() {}

    // Getter functions
    std::string getName() const {
        return name;
    }

    char getSymbol() const {
        return symbol;
    }
    
    Queue<int>& getMoves() {
        return moves;
    }

    /*  Player getMove() virtual function allow other 
        derived classes to implement their own getMove() function*/
    virtual int getMove() = 0;
};

class HumanPlayer : public Player {
public:
    HumanPlayer(const std::string& playerName, char playerSymbol)
        : Player(playerName, playerSymbol) {}

    // HumanPlayer getMove() function return an int for a position on the board
    int getMove() override {
        std::string input;
        
        while (true) {
            std::cout << name << " (" << symbol << "), enter position (1-9): ";
            std::cin >> input;
            
            // If input has one digit and is between 1 and 9 inclusive, it is valid
            if (input.length() == 1 && input[0] >= '1' && input[0] <= '9') {
                return input[0] - '0';
            }

            std::cout << "Error: input must be an integer from 1 to 9.\n";
        }
    }
};

#endif
