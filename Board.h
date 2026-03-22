#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <iomanip>
#include "Position.h"

class Board {
private:
    std::vector<std::vector<char> > grid;
    int minRow;
    int maxRow;
    int minCol;
    int maxCol;

public:
    Board() {
        minRow = -2;
        maxRow = 2;
        minCol = -2;
        maxCol = 2;
        resizeGrid();
    }

    void resizeGrid() {
        int rows = maxRow - minRow + 1;
        int cols = maxCol - minCol + 1;
        grid.assign(rows, std::vector<char>(cols, '.'));
    }

    void expandIfNeeded(int row, int col) {
        bool changed = false;

        while (row < minRow) {
            minRow--;
            changed = true;
        }
        while (row > maxRow) {
            maxRow++;
            changed = true;
        }
        while (col < minCol) {
            minCol--;
            changed = true;
        }
        while (col > maxCol) {
            maxCol++;
            changed = true;
        }

        if (changed) {
            std::vector<Position> filled;
            std::vector<char> values;

            for (int r = 0; r < (int)grid.size(); r++) {
                for (int c = 0; c < (int)grid[r].size(); c++) {
                    if (grid[r][c] != '.') {
                        filled.push_back(Position(r + oldMinRow, c + oldMinCol));
                        values.push_back(grid[r][c]);
                    }
                }
            }
        }
    }

private:
    int oldMinRow;
    int oldMinCol;

public:
    void prepareExpand(int row, int col) {
        oldMinRow = minRow;
        oldMinCol = minCol;
        expandIfNeeded(row, col);

        if (oldMinRow != minRow || oldMinCol != minCol ||
            (maxRow - minRow + 1) != (int)grid.size() ||
            (maxCol - minCol + 1) != (int)grid[0].size()) {

            std::vector<std::vector<char> > oldGrid = grid;
            int previousMinRow = oldMinRow;
            int previousMinCol = oldMinCol;
            int previousMaxRow = previousMinRow + (int)oldGrid.size() - 1;
            int previousMaxCol = previousMinCol + (int)oldGrid[0].size() - 1;

            resizeGrid();

            for (int r = previousMinRow; r <= previousMaxRow; r++) {
                for (int c = previousMinCol; c <= previousMaxCol; c++) {
                    char value = oldGrid[r - previousMinRow][c - previousMinCol];
                    if (value != '.') {
                        grid[r - minRow][c - minCol] = value;
                    }
                }
            }
        }
    }

    bool isEmptyCell(int row, int col) const {
        if (row < minRow || row > maxRow || col < minCol || col > maxCol) {
            return true;
        }
        return grid[row - minRow][col - minCol] == '.';
    }

    void placeMark(int row, int col, char symbol) {
        prepareExpand(row, col);
        grid[row - minRow][col - minCol] = symbol;
    }

    void clearCell(int row, int col) {
        if (row >= minRow && row <= maxRow && col >= minCol && col <= maxCol) {
            grid[row - minRow][col - minCol] = '.';
        }
    }

    char getCell(int row, int col) const {
        if (row < minRow || row > maxRow || col < minCol || col > maxCol) {
            return '.';
        }
        return grid[row - minRow][col - minCol];
    }

    bool hasThreeInRow(char symbol, int row, int col) const {
        int directions[4][2] = {
            {0, 1},
            {1, 0},
            {1, 1},
            {1, -1}
        };

        for (int i = 0; i < 4; i++) {
            int dr = directions[i][0];
            int dc = directions[i][1];
            int count = 1;

            int r = row + dr;
            int c = col + dc;
            while (getCell(r, c) == symbol) {
                count++;
                r += dr;
                c += dc;
            }

            r = row - dr;
            c = col - dc;
            while (getCell(r, c) == symbol) {
                count++;
                r -= dr;
                c -= dc;
            }

            if (count >= 3) {
                return true;
            }
        }

        return false;
    }

    void display() const {
        std::cout << "\nCurrent board:\n\n";

        std::cout << std::setw(5) << " ";
        for (int c = minCol; c <= maxCol; c++) {
            std::cout << std::setw(3) << c;
        }
        std::cout << "\n";

        for (int r = minRow; r <= maxRow; r++) {
            std::cout << std::setw(5) << r;
            for (int c = minCol; c <= maxCol; c++) {
                std::cout << std::setw(3) << getCell(r, c);
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
};

#endif
