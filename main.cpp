#include <iostream>
#include "Game.h"
#include "Player.h"

int main() {
    Game* newGame = new Game();
    Player<int>* player_1 = new Player<int>();
    Player<int>* player_2 = new Player<int>();

    bool finished = 0;
    int input, turn = 0;
    newGame->display();
    while (!finished) {
        std::cout << "===========================" << std::endl;

        // Player 1 play on the even turns, player 2 plays on the odd turns.
        if (turn % 2 == 0) {
            std::cout << "[PLAYER 1'S TURN]" << std::endl;
            // Display the respective players' queue, the left-most one will be deleted
            std::cout << "Size: " << player_1->size() << ", Queue: ";
            player_1->printQueue();

            // Turn 5 is when there will be three X for player 1
            if (player_1->size() == 3 && turn > 5) {
                newGame->emptyCell(player_1->top());
            }
            // Add the position of the newly placed X to the queue
            player_1->enqueue(newGame->place('X'));

            newGame->display();
            turn++;
        } else {
            std::cout << "[PLAYER 2'S TURN]" << std::endl;
            std::cout << "Size: " << player_2->size() << ", Queue: ";
            player_2->printQueue();

            // Turn 6 is when there will be three O for player 2
            if (player_2->size() == 3 && turn > 6) {
                newGame->emptyCell(player_2->top());
            }
            // Add the position of the newly placed O to the queue
            player_2->enqueue(newGame->place('O'));


            newGame->display();
            turn++;
        }

        // Announce winner
        if (newGame->check_win()) {
            std::cout << "WINNER: ";
            if ((turn-1) % 2 == 0) std::cout << "player 1";
            else std::cout << "player 2";
            finished = 1;
        }
    }
    return 0;
}
