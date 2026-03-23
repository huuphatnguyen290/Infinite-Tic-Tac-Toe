#include <iostream>
#include "game.h"
using namespace std;

int main() {
    string name1, name2;

    cout << "Enter Player 1 name: ";
    getline(cin, name1);

    cout << "Enter Player 2 name: ";
    getline(cin, name2);

    Game game(name1, name2);
    game.play();

    return 0;
}  