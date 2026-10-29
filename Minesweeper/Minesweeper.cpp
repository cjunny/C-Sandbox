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