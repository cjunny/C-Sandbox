#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Minesweeper.h"

//Mine definitions

//Constructor
Mine::Mine(std::vector<int> coordinate){
    location = coordinate;
}

//Function Definitions
std::vector<int> Mine::get_location(){
    return location;
}

int Mine::get_mineState(){
    return mineState;
}

void Mine::detonate(){
    mineState = 1;
}

//Board Definitions

//Constructor
Board::Board(std::string gameMode){
    if (gameMode == "easy"){
        boardDimensions = {9, 9};
        numberOfMines = 10;
    };
    if (gameMode == "medium"){
        boardDimensions = {16, 16};
        numberOfMines = 40;
    };
    if (gameMode == "hard"){
        boardDimensions = {30, 16};
        numberOfMines = 99;
    };
}

//Function Definitions
std::vector<int> Board::get_boardDimensions(){
    return boardDimensions;
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