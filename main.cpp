#include <iostream>
#include "Game.h"
#include "Player.h"
using namespace std;


int main() {
    Game* newGame = new Game();
    Player<char*> player_1;
    Player<char*> player_2;

    bool finished = 0;
    int input, turn = 0;
    while (!finished) {
        newGame->display();
        if (turn % 2 == 0) {
            newGame->place('X');
            player_1.enqueue(newGame->locate(input));
            player_1.printQueue();
            turn++;
        } else {
            newGame->place('O');
            player_2.enqueue(newGame->locate(input));
            player_2.printQueue();
            turn++;
        }
        //std::cout << "Checking Winner" << std::endl;
        if (newGame->check_win()) {
            std::cout << "WINNER: ";
            finished = 1;
        }
    }
    return 0;
}
