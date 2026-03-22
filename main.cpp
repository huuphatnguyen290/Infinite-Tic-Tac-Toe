#include <iostream>
#include "Game.h"

int main() {
    std::string name1, name2;

    std::cout << "Enter Player 1 name: ";
    std::getline(std::cin, name1);

    std::cout << "Enter Player 2 name: ";
    std::getline(std::cin, name2);

    Game game(name1, name2);
    game.play();

    return 0;
}
