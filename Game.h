#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include "Player.h"

class Game {
private:
    char board[3][3] = {
        {'_', '_', '_'},
        {'_', '_', '_'},
        {'_', '_', '_'}
    };

    HumanPlayer player1;
    HumanPlayer player2;
    
    // Helper functions check for either a horizontal, vertically, or diagonally win for the check_win() function
    bool check_row() const {
        for (int i = 0; i < 3; i++) {
            bool res = true;
            // Compare same with other char from the same row
            char same = board[i][0];

            // '_' is considered empty space
            if (same == '_') continue;

            for (int j = 1; j < 3; j++) {
                if (board[i][j] != same) {
                    res = false;
                    break;
                }
            }

            if (res) return true;
        }

        return false;
    }

    bool check_col() const {
        for (int i = 0; i < 3; i++) {
            bool res = true;
            char same = board[0][i];

            if (same == '_') continue;

            for (int j = 1; j < 3; j++) {
                if (board[j][i] != same) {
                    res = false;
                    break;
                }
            }

            if (res) return true;
        }

        return false;
    }

    bool check_downward_diagonal() const {
        char same = board[0][0];
        if (same == '_') return false;

        for (int i = 0; i < 3; i++) {
            if (board[i][i] != same) return false;
        }

        return true;
    }

    bool check_upward_diagonal() const {
        char same = board[0][2];
        if (same == '_') return false;

        for (int i = 0; i < 3; i++) {
            if (board[i][2 - i] != same) return false;
        }

        return true;
    }

    bool isValid(int position) const {
        // Check if input is between 1 and 9
        if (position < 1 || position > 9) {
            std::cout << "Invalid position, enter a number between 1 and 9 inclusive" << std::endl;
            return false;
        }

        int row = (position - 1) / 3;
        int column = (position - 1) % 3;
        char symbol = board[row][column];

        // Check if position is already occupied
        if (board[row][column] != '_') {
            std::cout << "Position occupied with " << board[row][column] << ". Enter a new position.\n";
            return false;
        }


        return true;
    }

    // Set char at position to symbol
    void placeAt(int position, char symbol) {
        int row = (position - 1) / 3;
        int col = (position - 1) % 3;
        board[row][col] = symbol;
    }

    // Set char at position to '_'
    void clearAt(int position) {
        int row = (position - 1) / 3;
        int col = (position - 1) % 3;
        board[row][col] = '_';
    }

    void processMove(Player& currentPlayer) {
        int position = currentPlayer.getMove();

        while (!isValid(position)) {
            std::cout << "Invalid move. Try again.\n";
            position = currentPlayer.getMove();
        }
        
        placeAt(position, currentPlayer.getSymbol());
        currentPlayer.getMoves().enqueue(position);
        
        // Each player can only keep 3 active marks
        if (currentPlayer.getMoves().length() > 3) {
            int oldPosition = currentPlayer.getMoves().top();
            currentPlayer.getMoves().dequeue();
            clearAt(oldPosition);

            std::cout << currentPlayer.getName()
                      << "'s oldest move at position "
                      << oldPosition
                      << " was removed.\n";
        }

    }

public:
    Game(const std::string& name1, const std::string& name2)
        : player1(name1, 'X'), player2(name2, 'O') {}

    ~Game() {}

    void display() {
        // Display both the tic-tac-toe board and the position guide board
        std::string line = "--------------";
        std::cout << "\n";
        std::cout << board[0][0] << " | " << board[0][1] << " | " << board[0][2]
                << "\t"
                << "1 | 2 | 3" << std::endl;

        std::cout << line
                << "\t"
                << line << std::endl;

        std::cout << board[1][0] << " | " << board[1][1] << " | " << board[1][2]
                << "\t"
                << "4 | 5 | 6" << std::endl;

        std::cout << line                
                << "\t"
                << line << std::endl;

        std::cout << board[2][0] << " | " << board[2][1] << " | " << board[2][2]
                << "        "
                << "7 | 8 | 9" << std::endl;

    }

    void showGuide(){
        // Position guide board guide which input correspond to which position 
        std::cout << "Board positions:\n";
        std::cout << "1 | 2 | 3\n";
        std::cout << "----------\n";
        std::cout << "4 | 5 | 6\n";
        std::cout << "----------\n";
        std::cout << "7 | 8 | 9\n\n";
    }

    bool check_win() {
        return check_upward_diagonal() || check_downward_diagonal() || check_col() || check_row();
    }

    void play() {
        Player* current = &player1;
        // Show the numbered square 
        showGuide();

        while (true) {
            display();
            // Check if move is valid
            processMove(*current);
            display();

            if (check_win()) {
                std::cout << current->getName() << " (" << current->getSymbol() << ") wins!\n";
                break;
            }

            // Alternate between players
            if (current == &player1) {
                current = &player2;
            } else {
                current = &player1;
            }
        }
    }
};

#endif 
