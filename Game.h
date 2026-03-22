#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Board.h"
#include "HumanPlayer.h"

class Game {
private:
    Board board;
    HumanPlayer player1;
    HumanPlayer player2;

public:
    Game(const std::string& name1, const std::string& name2)
        : player1(name1, 'X'), player2(name2, 'O') {}

    void removeOldestMoveIfNeeded(Player& player) {
        if (player.getMoves().size() > 3) {
            Position oldMove = player.getMoves().dequeue();
            board.clearCell(oldMove.row, oldMove.col);
            std::cout << player.getName() << "'s oldest mark disappeared at ("
                      << oldMove.row << ", " << oldMove.col << ").\n";
        }
    }

    bool takeTurn(Player& player) {
        Position move;

        while (true) {
            move = player.getMove();

            if (!board.isEmptyCell(move.row, move.col)) {
                std::cout << "Cell is already used. Try again.\n";
                continue;
            }

            break;
        }

        board.placeMark(move.row, move.col, player.getSymbol());
        player.getMoves().enqueue(move);
        removeOldestMoveIfNeeded(player);
        board.display();

        if (board.hasThreeInRow(player.getSymbol(), move.row, move.col)) {
            std::cout << player.getName() << " wins!\n";
            return true;
        }

        return false;
    }

    void showRules() {
        std::cout << "===== Infinite Tic-Tac-Toe =====\n";
        std::cout << "1. Two players take turns placing X and O.\n";
        std::cout << "2. You can play on any integer row and column.\n";
        std::cout << "3. Each player can only keep 3 active marks on the board.\n";
        std::cout << "4. When you place a 4th mark, your oldest mark disappears.\n";
        std::cout << "5. First player to make 3 in a row wins.\n\n";
    }

    void play() {
        showRules();
        board.display();

        while (true) {
            if (takeTurn(player1)) {
                break;
            }
            if (takeTurn(player2)) {
                break;
            }
        }
    }
};

#endif
