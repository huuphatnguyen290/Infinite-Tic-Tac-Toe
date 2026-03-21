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

// Checks for diagonal win

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

bool Game::check_win() const {
    return ((check_upward_diagonal() || check_downward_diagonal()) || (check_col() || check_row()));
}

void Game::display() const {
    // Displays the board
    std::cout << "\n";
    std::cout << board[0][0] << " | " << board[0][1] << " | "<< board[0][2] << std::endl;
    std::cout << "--------------" << std::endl;
    std::cout << board[1][0] << " | " << board[1][1] << " | "<< board[1][2] << std::endl;
    std::cout << "--------------" << std::endl;
    std::cout << board[2][0] << " | " << board[2][1] << " | "<< board[2][2] << std::endl;
    std::cout << "--------------" << std::endl;
    return;
}

// Check if move is valid:
bool Game::isValid(int position) const {
    // Position is between 1 and 9
    if (position < 1 || position> 9) {
        std::cout << "Invalid position, enter a number between 1 and 9 inclusive" << std::endl;
        return false;
    }
    // No symbol is already at the position
    int row = (position - 1) / 3;
    int column = (position - 1) % 3;
    char symbol = board[row][column];

    if (symbol != '_') {
        std::cout << "Position occupied with a " << symbol << ", enter new position" << std::endl;
        return false;
    }
    return true;
}

void Game::place(char symbol) {
    int position;
    std::cout << "Enter position (1-9): " << std::endl;
    std::cin >> position;

    while (!isValid(position)) {
        std::cout << "Invalid move! Try again." << std::endl;
        std::cin >> position;
    }

    int row = (position - 1) / 3;
    int column = (position - 1) % 3;
    board[row][column] = symbol;
    return;
}

char* Game::locate(int position) {

    int row = (position - 1) / 3;
    int column = (position - 1) % 3;

    return &board[row][column];
}
