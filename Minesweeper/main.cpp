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

    while (newGame.get_gameState()){
        newBoard.displayBoard();
        newGame.promptUser(newBoard);
        newGame.executeUserCommand(newBoard);
        newGame.checkWinCondition(newBoard);
    }

 
    //Add win condition
    //  minesFound we will keep as a characteristic of Game since it does not necessarily reflect the board, the user can make a mistake
    //  let's add a totalNumberOfSquares, squaresUncovered counter and squares flagged counter to Board that we will use to check the win condition
    //      if all mines are flagged AND the rest of the squares are uncovered, the user wins
    
    //We can potentially allow user to add multiple inputs with the same action to speed up the game
    //change board to include numbers on the edges for row and column selection
}