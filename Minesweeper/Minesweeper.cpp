#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Minesweeper.h"


//Square definitions
Square::Square(std::vector<int> coordinates){
    squareLocation = coordinates;
    for (const int& num: {coordinates[0] - 1, coordinates[0], coordinates[0] + 1}){
        for (const int& num2: {coordinates[1] - 1, coordinates[1], coordinates[1] + 1}){
            if ()//check surrounding squares for mines and increment adjacentMines if there is a mine
        }
    }
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

    //Generate a vector with all possible coordinates of the board vector<vector<int>>
    //randomnly generate a number from the size of the vector
    //the coordinate indexed at the rng is a mine
    //change that square to a mine
    //BREAK FROM THE LOOP THAT IS GOING THROUGH THE COORDINATE VECTOR
    //remove that coordinate from the coordinate vector
    //a while loop will control all this, loop ends when all mines are created

    
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