#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Minesweeper.h"
#include <random>

//Miscellaneous functions
int generateRandomNumber(int firstRange, int lastRange){ //Generates random number in a given range
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(firstRange, lastRange);
    return distrib(gen);
}


//Constructor
//Square::Square(std::vector<int> coordinates){
    //squareLocation = coordinates;
//}

//Getters

bool Square::get_isMine(){
    return isMine;
}

bool Square::get_isFlag(){
    return isFlag;
}
bool Square::get_isUncovered(){
    return isUncovered;
}
int Square::get_adjacentMines(){
    return adjacentMines;
}

//Square definitions

std::vector<int> Square::get_squareLocation(){
    return squareLocation;
}

void Square::setLocation(std::vector<int> coordinates){
    squareLocation = coordinates;
}

void Square::setFlagSquare(char userInput){
    if (userInput == 'F'){
        isFlag = true;
    }
    else if (userInput == 'U'){
        isFlag = false;
    }
}

void Square::mineSquare(){
    isMine = true;
}

void Square::uncoverSquare(){
    isUncovered = true;
}

void Square::updateAdjacentMines(){
    ++adjacentMines;
}

//Board Definitions

//Constructor
Board::Board(std::string gameMode)
    : numberOfMines(determineNumberOfMines(gameMode)), 
      totalNumberOfSquares(determineTotalNumberOfSquares(gameMode)),
      width(determineWidth(gameMode)),
      height(determineHeight(gameMode)) 
{
    //Declare square instances in board
    boardSquares = std::vector<std::vector<Square>>(height, std::vector<Square>(width));

    //use curly to erase coordinateArray when finished
    {
        //Generate a vector with all possible coordinates of the board vector<vector<int>>
        std::vector<std::vector<int>> coordinateArray;//first element in vector int will be row, second will be column
        coordinateArray.reserve(width*height); //allocates memory for all coordinates in the board, coordinateArray is w*h spaces long

        //fill in coordinate Array with coordinates
        std::vector<int> coordinate;
        for(int i = 0; i < height; ++i){
            for(int j = 0; j < width; ++j){
                coordinate = {i,j};
                boardSquares[i][j].setLocation(coordinate);
                coordinateArray.push_back(coordinate);
            }
        }

        int arraySize = static_cast<int>(coordinateArray.size());
        int mine = 0;
        int mineLocation; 
        //loop ends when all mines are created
        while (mine < numberOfMines){
            //randomnly generate a number from the size of the vector
            //the coordinate indexed at the rng is a mine
            mineLocation = generateRandomNumber(0, arraySize - 1);
            allMineLocations.push_back(coordinateArray[mineLocation]);
            int mineRow = coordinateArray[mineLocation][0];
            int mineCol = coordinateArray[mineLocation][1];
            boardSquares[mineRow][mineCol].mineSquare();

            for (int mineAdjRow = mineRow - 1; mineAdjRow < mineRow + 2; ++mineAdjRow){//in this loop make sure the square with a mine doesn't get counted
                for (int mineAdjCol = mineCol - 1; mineAdjCol < mineCol + 2; ++mineAdjCol){
                    if(mineAdjRow >= 0 && mineAdjRow < height && mineAdjCol >= 0 && mineAdjCol < width){//checks if coordinates are a valid square
                        if(boardSquares[mineAdjRow][mineAdjCol].get_isMine() == true){
                            continue;
                        }
                        boardSquares[mineAdjRow][mineAdjCol].updateAdjacentMines();
                    }
                }
            }
                                
            //remove that coordinate from the coordinate vector
            coordinateArray.erase(coordinateArray.begin() + mineLocation);
            arraySize = arraySize - 1;
            ++mine;
        }
    }
}

//Function Definitions
std::vector<std::vector<Square>> Board::get_boardSquares(){
    return boardSquares;
}

int Board::get_width(){
    return width;
}

int Board::get_height(){
    return height;
}

int Board::get_numberOfMines(){
    return numberOfMines;
}

int Board::get_squaresUncovered(){
    return squaresUncovered;
}

int Board::get_squaresFlagged(){
    return squaresFlagged;
}

std::vector<std::vector<int>> Board::get_allMineLocations(){
    return allMineLocations;
}

void Board::displayBoard(){
    for (int row = 0; row < height; ++row){
        for (int col = 0; col < width; ++col){
            if(boardSquares[row][col].get_isUncovered() == true){
                if (boardSquares[row][col].get_adjacentMines() == 0)
                {
                    std::cout << 'U';
                }
                else{
                    std::cout << boardSquares[row][col].get_adjacentMines();
                }
            }
            else if(boardSquares[row][col].get_isFlag() == true){
                std::cout << 'F';
            }
            else{
                std::cout << 'O';//covered square
            }
        }
        std::cout << '\n';
    }
}

void Board::setSquareFlag(int row, int col, char userInput){
    boardSquares[row][col].setFlagSquare(userInput);
    if (userInput == 'F'){
        ++squaresFlagged;
    }
    if (userInput == 'U'){
        squaresFlagged = squaresFlagged - 1;
    }
}

void Board::setSquareMine(int row, int col){
    boardSquares[row][col].mineSquare();
}

void Board::setSquareUncover(int row, int col){
    boardSquares[row][col].uncoverSquare();
    ++squaresUncovered;
}

void Board::setSquareAdjacentMines(int row, int col){
    boardSquares[row][col].updateAdjacentMines();
}
//Game Definitions

//Constructor
Game::Game(std::string mode){
    gameMode = mode;
}

//Functions
std::string Game::get_gameMode(){
    return gameMode;
}

bool Game::get_gameState(){
    return gameState;
}

int Game::get_minesFound(){
    return minesFound;
}

int Game::get_minesLeft(){
    return minesLeft;
}

void Game::updateMinesFound(){
    ++minesFound;
}

void Game::updateUserRow(int row){
    userRow = row;
}

void Game::updateUserCol(int col){
    userCol = col;
}

void Game::promptUser(Board& userBoard){
    std::cout << "Mines Found: " << minesFound << std::endl;
    std::cout << "Mines Left: " << userBoard.get_numberOfMines() - minesFound << std::endl;
    std::cout << "You will be prompted to enter a row and column number to select a square." << std::endl;
    std::cout << "Then you will be prompted to enter the action you would like for that square." << std::endl;
    std::cout << "You can choose F to flag the square or C to click it" << std::endl;
    std::cout << "Enter the row" << std::endl;
    std::cin >> userRow;
    std::cout << "Enter the column" << std::endl;
    std::cin >> userCol;
    std::cout << "Enter your action" << std::endl;
    std::cin >> userAction;
}

void Game::userSelectsMine(){
    gameState = false;
    std::cout << "You selected a mine. You lose" << std::endl;
}

void Game::userSetsFlag(Board& userBoard, int row, int col, char userInput){
    userBoard.setSquareFlag(row, col, userInput);
}

void Game::userSelectsSafeSquare(Board& userBoard, int row, int col){
    //Check if the square is inbounds
    if (row < 0 || row > userBoard.get_height() - 1 || col < 0 || col > userBoard.get_width() - 1){ //user input will need to be how vectors are indexed
        return;
    }
    //Check if the square is a flagged, mine, uncovered
    if (userBoard.get_boardSquares()[row][col].get_isMine() == true || userBoard.get_boardSquares()[row][col].get_isFlag() == true || userBoard.get_boardSquares()[row][col].get_isUncovered() == true){
        return;
    }

    //uncover the square
    userBoard.setSquareUncover(row, col);

    if (userBoard.get_boardSquares()[row][col].get_adjacentMines() > 0){
        return;
    }

    //Search adjacent squares
    for (int i = row - 1; i <= row + 1; ++i){
        for (int j = col - 1; j <= col + 1; ++j){
            if (i == row && j == col){
                continue;
            }
            userSelectsSafeSquare(userBoard, i, j); //continue; stack overflow is happening needs work, 11/5 code is going back and forth between two squares
        }
    }
}

void Game::executeUserCommand(Board& userBoard){
    if (userBoard.get_boardSquares()[userRow][userCol].get_isMine() == true && userAction == 'C' && userBoard.get_boardSquares()[userRow][userCol].get_isFlag() == false){
        userSelectsMine();
    }
    else if (userAction == 'C' && userBoard.get_boardSquares()[userRow][userCol].get_isFlag() == true){
        std::cout << "Invalid selection. Square is flagged." << std::endl;
    }
    else if (userAction == 'F'){
        userSetsFlag(userBoard, userRow, userCol, userAction);
        ++minesFound;
    }
    else if (userAction == 'U'){
        userSetsFlag(userBoard, userRow, userCol, userAction);
        if (minesFound > 0){
            minesFound = minesFound - 1;
        }
    }
    else if (userBoard.get_boardSquares()[userRow][userCol].get_isMine() == false){
        userSelectsSafeSquare(userBoard, userRow, userCol);
    }
}

void Game::checkWinCondition(Board& userBoard){
    bool earlyBreak;
    for (int i = 0; i < userBoard.get_numberOfMines() - 1; ++i){
        if (userBoard.get_boardSquares()[userBoard.get_allMineLocations()[i][0]][userBoard.get_allMineLocations()[i][1]].get_isFlag() == false){//if there is a square where there is a mine and it IS NOT flagged, we break; if it passes through entirely, they win
            earlyBreak = true;
            break;
        }

    }
    if (earlyBreak == true){
        return;
    }
    else{
        std::cout << "Congratulations! You found all the mines. You win!" << std::flush;
        gameState = false;
    }
}