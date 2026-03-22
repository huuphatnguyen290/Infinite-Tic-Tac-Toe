#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include "Position.h"

class Board {
private:
    // 2D dynamic board
    std::vector<std::vector<char> > grid;

    // Range of the board
    int minRow;
    int maxRow;
    int minCol;
    int maxCol;

public:
    Board() {
        // Start with a 3x3 board: rows 0-2, cols 0-2
        minRow = 0;
        maxRow = 2;
        minCol = 0;
        maxCol = 2;
        resizeGrid();
    }

    void resizeGrid() {
        int rows = maxRow - minRow + 1;
        int cols = maxCol - minCol + 1;

        // Fill all cells with '_' to mean empty
        grid.assign(rows, std::vector<char>(cols, '_'));
    }

    void expandIfNeeded(int row, int col) {
        bool changed = false;

        // Save old board boundaries
        int oldMinRow = minRow;
        int oldMaxRow = maxRow;
        int oldMinCol = minCol;
        int oldMaxCol = maxCol;

        // Save old board data before resizing
        std::vector<std::vector<char> > oldGrid = grid;

        // Expand upward
        while (row < minRow) {
            minRow--;
            changed = true;
        }

        // Expand downward
        while (row > maxRow) {
            maxRow++;
            changed = true;
        }

        // Expand left
        while (col < minCol) {
            minCol--;
            changed = true;
        }

        // Expand right
        while (col > maxCol) {
            maxCol++;
            changed = true;
        }

        // If board size changed, create new grid and copy old values back
        if (changed) {
            resizeGrid();

            for (int r = oldMinRow; r <= oldMaxRow; r++) {
                for (int c = oldMinCol; c <= oldMaxCol; c++) {
                    grid[r - minRow][c - minCol] = oldGrid[r - oldMinRow][c - oldMinCol];
                }
            }
        }
    }

    bool isEmptyCell(int row, int col) const {
        // Outside current board is treated as empty
        if (row < minRow || row > maxRow || col < minCol || col > maxCol) {
            return true;
        }

        return grid[row - minRow][col - minCol] == '_';
    }

    void placeMark(int row, int col, char symbol) {
        // Expand board first if needed
        expandIfNeeded(row, col);

        // Place player's symbol
        grid[row - minRow][col - minCol] = symbol;
    }

    void clearCell(int row, int col) {
        // Clear cell only if it is inside the current board
        if (row >= minRow && row <= maxRow && col >= minCol && col <= maxCol) {
            grid[row - minRow][col - minCol] = '_';
        }
    }

    char getCell(int row, int col) const {
        // Outside current board is treated as empty
        if (row < minRow || row > maxRow || col < minCol || col > maxCol) {
            return '_';
        }

        return grid[row - minRow][col - minCol];
    }

    bool hasThreeInRow(char symbol, int row, int col) const {
        // 4 directions:
        // horizontal, vertical, diagonal down-right, diagonal down-left
        int directions[4][2] = {
            {0, 1},
            {1, 0},
            {1, 1},
            {1, -1}
        };

        for (int i = 0; i < 4; i++) {
            int dr = directions[i][0];
            int dc = directions[i][1];
            int count = 1;   // Count the current cell first

            // Check forward direction
            int r = row + dr;
            int c = col + dc;
            while (getCell(r, c) == symbol) {
                count++;
                r += dr;
                c += dc;
            }

            // Check backward direction
            r = row - dr;
            c = col - dc;
            while (getCell(r, c) == symbol) {
                count++;
                r -= dr;
                c -= dc;
            }

            // Win if 3 or more connected symbols
            if (count >= 3) {
                return true;
            }
        }

        return false;
    }

    void display() const {
        // Print column numbers
        std::cout << "\n   ";
        for (int c = minCol; c <= maxCol; c++) {
            std::cout << c << "  ";
        }
        std::cout << "\n";

        // Print each row number and board cell
        for (int r = minRow; r <= maxRow; r++) {
            std::cout << r << "  ";
            for (int c = minCol; c <= maxCol; c++) {
                std::cout << getCell(r, c) << "  ";
            }
            std::cout << "\n";
        }

        std::cout << "\n";
    }
};

#endif