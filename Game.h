#include <iostream>
#include "Queue.h"
using namespace std;

#ifndef GAME_H
#define GAME_H

class Game {
    private:
        // Tic-Tac-Toe Board
        char board[3][3] = {
            {'_', '_', '_'},
            {'_', '_', '_'},
            {'_', '_', '_'},
        };
        // Helper functions
        bool check_row() const;
        bool check_col() const;
        bool check_downward_diagonal() const;
        bool check_upward_diagonal() const;
        bool isValid(int position) const;
    public:
        Game();
        virtual ~Game();

        void display() const;
        void place(char symbol);
        char* locate(int position);
        bool check_win() const;
};

#endif // GAME_H
