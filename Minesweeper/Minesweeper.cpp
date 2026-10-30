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

void Square::flagSquare(){
    isFlag = true;
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
Board::Board(std::string gameMode){
    if (gameMode == "easy"){
        width = 9;
        height = 9;
        numberOfMines = 10;
    };
    if (gameMode == "medium"){
        width = 16;
        height = 16;
        numberOfMines = 40;
    };
    if (gameMode == "hard"){
        width = 30;
        height = 16;
        numberOfMines = 99;
    };

//Declare square instances in board

boardSquares = std::vector<std::vector<Square>>(height, std::vector<Square>(width));
std::vector<std::vector<int>> allMineLocations;

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

            /*for(int i = 0; i < height; ++i){
                for(int j = 0; j < width; ++j){
                    if(coordinateArray[mineLocation] == boardSquares[i][j].get_squareLocation()){
                        //change that square to a mine
                        boardSquares[i][j].mineSquare(); //changes the square to a mine
                        //takes location of mine and updates adjacent square count of surrounding mines
                        //if square is a mine, does not add a count
                        for (int mineRow = coordinateArray[mineLocation][0] - 1; mineRow < coordinateArray[mineLocation][0] + 2; ++mineRow){//in this loop make sure mine square doesn't change
                            for (int mineCol = coordinateArray[mineLocation][1] - 1; mineRow < coordinateArray[mineLocation][1] + 2; ++mineCol){
                                if(mineRow >= 0 && mineRow < height && mineCol >= 0 && mineCol < width)
                                    if(boardSquares[mineRow][mineCol].get_isMine() == false){
                                        boardSquares[mineRow][mineCol].updateAdjacentMines();
                                    }
                            }
                        }
                        shouldBreakAll = true;
                        break;
                    }
                }
                //BREAK FROM THE LOOP THAT IS GOING THROUGH THE COORDINATE VECTOR
                if(shouldBreakAll){
                    break;
                }
            }*/
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

void Board::displayBoard(){
    for (int row = 0; row < height; ++row){
        for (int col = 0; col < width; ++col){
            if(boardSquares[row][col].get_isUncovered() == true){
                if (boardSquares[row][col].get_adjacentMines() == 0)
                {
                    std::cout << 'C';
                }
                
                std::cout << boardSquares[row][col].get_adjacentMines();
            }
            if(boardSquares[row][col].get_isFlag() == true){
                std::cout << 'F';
            }
            std::cout << 'O';//covered square
        }
        std::cout << '\n';
    }
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

void Game::promptUser(){
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

void Game::userFlags(Board& userBoard){
    userBoard.get_boardSquares()[userRow][userCol].flagSquare();
}

void Game::userSelectsSafeSquare(Board& userBoard){//add recursion
    userBoard.get_boardSquares()[userRow][userCol].uncoverSquare();
    int rowSearch = userBoard.get_boardSquares()[userRow][userCol].get_squareLocation()[0];
    int colSearch = userBoard.get_boardSquares()[userRow][userCol].get_squareLocation()[1];
    for (int i = rowSearch - 1; i < rowSearch + 2; ++i){
        for (int j = colSearch - 1; j < colSearch + 2; ++j){
            if (userBoard.get_boardSquares()[rowSearch][colSearch].get_isMine() == false){
                userSelectsSafeSquare(userBoard);
            }
        }
    }
}

void Game::executeUserCommand(Board& userBoard){
    if (userBoard.get_boardSquares()[userRow][userCol].get_isMine() == true){
        userSelectsMine();
    }
    if (userAction == 'F'){
        userFlags(userBoard);
    }
    if (userBoard.get_boardSquares()[userRow][userCol].get_isMine() == false){
        userSelectsSafeSquare(userBoard);
    }
}
