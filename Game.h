#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Board.h"
#include "HumanPlayer.h"

class Game {
private:
    // The game board
    Board board;

    // Two human players
    HumanPlayer player1;
    HumanPlayer player2;

public:
    // Create 2 players and assign X and O
    Game(const std::string& name1, const std::string& name2)
        : player1(name1, 'X'), player2(name2, 'O') {}

    void removeOldestMoveIfNeeded(Player& player) {
        // Each player can only keep 3 marks on the board
        if (player.getMoves().size() > 3) {
            // Remove the oldest move from the queue
            Position oldMove = player.getMoves().dequeue();

            // Clear that old mark from the board
            board.clearCell(oldMove.row, oldMove.col);

            std::cout << player.getName() << "'s oldest mark disappeared at ("
                      << oldMove.row << ", " << oldMove.col << ").\n";
        }
    }

    bool takeTurn(Player& player) {
        Position move;

        while (true) {
            // Get move from current player
            move = player.getMove();

            // Keep asking if the cell is already used
            if (!board.isEmptyCell(move.row, move.col)) {
                std::cout << "Cell is already used. Try again.\n";
                continue;
            }

            break;
        }

        // Place the mark on the board
        board.placeMark(move.row, move.col, player.getSymbol());

        // Store this move in the player's queue
        player.getMoves().enqueue(move);

        // Remove oldest move if player has more than 3 marks
        removeOldestMoveIfNeeded(player);

        // Show updated board
        board.display();

        // Check if this move creates 3 in a row
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
        // Show game rules first
        showRules();

        // Show empty board at the beginning
        board.display();

        // Keep playing until one player wins
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