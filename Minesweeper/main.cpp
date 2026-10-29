#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Minesweeper.h"

int main(){
    std::string mode;
    std::cout << "Welcome to Minesweeper! Enter a game mode easy, medium, or hard." << std::flush << std::endl;
    std::cin >> mode;
    Game newGame(mode);
    Board newBoard(mode);
    
}