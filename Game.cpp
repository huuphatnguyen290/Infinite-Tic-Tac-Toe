#include <iostream>
#include <string>
#include <limits>
#include "Game.h"
using namespace std;

Game::Game() {

}

Game::~Game() {

}
// Check for horizontal win
bool Game::check_row() const {
    for (int i = 0; i < 3; i++) {
        bool res = true;
        // Check the first square, if the remaining square is the same, return true
        char same = board[i][0];
        if (same == '_') continue; // This row has empty spaces

        for (int j = 1; j < 3; j++) {
            if(board[i][j] != same) {
                res = false;
                break;
            }
        }
        if (res == true) return res;
    }

    return false;
}

// Check for vertical win
bool Game::check_col() const {
    for (int i = 0; i < 3; i++) {
        bool res = true;
        char same = board[0][i];
        if (same == '_') continue; // This row has empty spaces

        for (int j = 1; j < 3; j++) {
            if(board[j][i] != same) {
                res = false;
                break;
            }
        }
        if (res == true) return res;
    }

    return false;
}

// Check '\' diagonal
bool Game::check_downward_diagonal() const {
    char same = board[0][0];
    if (same == '_') return false;
    for (int i = 0; i < 3; i++)
        if (board[i][i] != same) return false;
    return true;
}

// Check '/' diagonal
bool Game::check_upward_diagonal() const {
    char same = board[0][2];
    if (same == '_') return false;
    for (int i = 0; i < 3; i++)
        if (board[i][2-i] != same) return false;
    return true;
}

// A win occur whenever three symbols (X or O) form a straight line on the board
bool Game::check_win() const {
    return ((check_upward_diagonal() || check_downward_diagonal()) || (check_col() || check_row()));
}

void Game::display() const {
    // Displays the board
    std::string line = "-----------";
    std::cout << "\n";
    std::cout << " " << board[0][0] << " | " << board[0][1] << " | "<< board[0][2] << "\t 1 | 2 | 3" << std::endl;
    std::cout << line << "\t" << line << std::endl;
    std::cout << " " << board[1][0] << " | " << board[1][1] << " | "<< board[1][2] << "\t 4 | 5 | 6" << std::endl;
    std::cout << line << "\t" << line << std::endl;
    std::cout << " " << board[2][0] << " | " << board[2][1] << " | "<< board[2][2] << "\t 7 | 8 | 9" << std::endl;
    return;
}

// Check if move is valid:
int Game::getPosition() const {
    int position;
    std::cout << "Enter position: ";
    while (true) {

        if (!(std::cin >> position)) {
            std::cout << "Invalid input, please enter an integer between 1 and 9: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (!(position >= 1 && position <= 9)) {
            std::cout << "Outside of range, please enter an integer between 1 and 9: ";
            continue;
        }

        int row = (position - 1) / 3;
        int column = (position - 1) % 3;
        char symbol = board[row][column];
        if (symbol != '_') {
            std::cout << "Position occupied by a " << symbol << ", please enter another position: ";
            continue;
        }

        return position;
    }
}

int Game::place(char symbol) {
    int position = getPosition();

    int row = (position - 1) / 3;
    int column = (position - 1) % 3;

    board[row][column] = symbol;
    return position;
}

int Game::place(char symbol, int position) {
    int row = (position - 1) / 3;
    int column = (position - 1) % 3;

    board[row][column] = symbol;
    return position;
}

void Game::emptyCell(int position) {
    int row = (position - 1) / 3;
    int column = (position - 1) % 3;

    board[row][column] = '_';
}
