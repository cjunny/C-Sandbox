#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class Board{//stores board data and changes board data;
    private:
    std::vector<std::vector<Grid>> board;
    bool boardSolved = 0;

    public:
    Board(); //constructor




};

class Grid{
    private:
    std::vector<std::vector<Square>> grid;
    bool gridSolved = 0;

    public:
    Grid(); //constructor

};

class Square{//individual squares that make up the board; lock the square once it is solved
    private:
    const std::vector<int> possibleValues = {1, 2, 3, 4, 5, 6, 7, 8, 9}; //place somewhere else...don't need to create this every time we create a square
    unsigned int squareValue;
    bool squareSolved = 0;

    public:
    Square(); //constructor
    void set_squareValue();
    void set_squareSolved();

};