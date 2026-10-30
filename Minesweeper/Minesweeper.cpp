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
        bool shouldBreakAll = false;
        int indexToRemove;
        std::vector<std::vector<int>> mineLocations; 
        //loop ends when all mines are created
        while (mine < numberOfMines){
            //randomnly generate a number from the size of the vector
            //the coordinate indexed at the rng is a mine
            mineLocation = generateRandomNumber(0, arraySize);
            for(int i = 0; i < height; ++i){
                for(int j = 0; j < width; ++j){
                    if(coordinateArray[mineLocation] == boardSquares[i][j].get_squareLocation()){
                        //change that square to a mine
                        boardSquares[i][j].mineSquare(); //changes the square to a mine
                        mineLocations.push_back(coordinateArray[mineLocation]);
                        for (int mineRow = coordinateArray[mineLocation][mineRow] - 1; mineRow < coordinateArray[mineLocation][mineRow] + 2; ++mineRow){//in this loop make sure mine square doesn't change
                            for (int mineCol = coordinateArray[mineLocation][mineCol] - 1; mineRow < coordinateArray[mineLocation][mineCol] + 2; ++mineCol){
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
            }
            //remove that coordinate from the coordinate vector
            indexToRemove = mineLocation;
            coordinateArray.erase(coordinateArray.begin() + indexToRemove);
            arraySize = arraySize - 1;
            ++mine;
        }

        //Now that mines are placed, find and assign number of adjacent mines to squares
        //Find where the mines are (go back and create a separate array with coordinate of mines)
        //At each mine location, add 1 to every adjacent square
        for (int i = 0; i < numberOfMines; ++i){
            for (int mineRow = mineLocations[i][mineRow] - 1; mineRow < mineLocations[i][mineRow] + 1; ++mineRow)
        }
    }

}

//Function Definitions
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
    
}






//Game Definitions

//Constructor
Game::Game(std::string mode){
    gameMode = mode;
}