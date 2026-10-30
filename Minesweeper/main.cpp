#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Minesweeper.h"

int main(){

    //To initialize game, we first set up the board. Board contains board size and number of mines. Then we generate the minefield.
    //Then we modify the board depending on the minefield
    std::string mode;
    std::cout << "Welcome to Minesweeper! Enter a game mode easy, medium, or hard." << std::flush << std::endl;
    std::cin >> mode;
    Game newGame(mode);
    Board newBoard(mode);
    
}