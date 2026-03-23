#include <iostream>

#ifndef GAME_H
#define GAME_H

// The Game object is in charge of the board and checking if a win has occured
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

        int getPosition() const;

        bool isEmpty(int position);

    public:
        Game();
        virtual ~Game();

        void display() const;
        int place(char symbol);
        int place (char symbol, int position);
        bool check_win() const;
        void emptyCell(int position);
};

#endif // GAME_H
