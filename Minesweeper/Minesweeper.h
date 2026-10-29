#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>


class Mine{
    private:
    std::vector<int> location; // two integers with row and column location, first integer is row, second is column
    int mineState = 0; //"0" means not detonated, "1" means detonated

    public:
    //Constructor
    Mine(std::vector<int> coordiantes);

    //Getter functions
    std::vector<int> get_location();
    int get_mineState();

    void detonate();

};

class Board{
    private:
    std::vector<int> boardDimensions;
    int numberOfMines;
    std::vector<std::vector<int>> uncoveredSquares = {};

    public:
    //Constructor
    Board(std::string gameMode);

    std::vector<int> get_boardDimensions();
    int get_numberOfMines();

    void displayBoard(); //generates board with flags and open squares
    void placeMines();
    void placeNumbers(); //places numbers that indicate how many mines surround the square
};

class Flag{
    private:
    std::vector<int> flagLocation;

    public:
    std::vector<int> get_flagLocation();
    void squareImmunity(); //prevents user from selecting a square with a flag on it

};

class Game{
    private:
    std::string gameMode;
    int gameScore; //0 means you won, 1 means you lost

    public:
    Game(std::string mode);
    std::string get_gameMode();
};