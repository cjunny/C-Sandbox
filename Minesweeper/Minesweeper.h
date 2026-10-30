#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>


class Square{//square on the board
    private:
    std::vector<int> squareLocation; //two integers with row and column location, first integer is row, second is column
    bool isMine = false; //"false" means no mine, "true" means mine
    bool isFlag = false; //"false" means no flag, "true" means flag
    bool isUncovered = false; //"false" means covered, "true" means uncovered
    int adjacentMines = 0; //number of mines surrounding the square

    public:
    //Constructor
    Square() = default;
    //Square(std::vector<int> coordinates);

    //Getters
    std::vector<int> get_squareLocation();
    bool get_isMine();
    bool get_isFlag();
    bool get_isUncovered();
    int get_adjacentMines();

    //Functions
    void setLocation(std::vector<int> coordinates);
    void flagSquare();
    void mineSquare();
    void uncoverSquare();
    void updateAdjacentMines(); //adds 1 to adjacentMines

};


class Board{
    private:
    std::vector<std::vector<Square>> boardSquares = {}; //2D vector of squares that make up the board
    int width; //width of the board
    int height; //height of the board
    int numberOfMines;

    public:
    //Constructor
    Board(std::string gameMode); //within this constructor, using random number generator, randomnly generate mine coordinates,
    // and make the squares constructed with those coordinates into mines

    std::vector<std::vector<Square>> get_boardSquares();
    
    int get_numberOfMines();
    int get_width();
    int get_height();

    void displayBoard(); //generates board with flags and open squares
    //void placeMines();
    //void placeNumbers(); //places numbers that indicate how many mines surround the square
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
    bool gameState = true; //0 means game over, 1 means still going (true)
    int minesLeft;
    int minesFound = 0;
    int userRow;
    int userCol;
    char userAction;

    public:
    Game(std::string mode);
    std::string get_gameMode();
    bool get_gameState();
    int get_minesLeft();
    int get_minesFound();

    void updateMinesFound();
    void promptUser();//prompts user to pick a square and specify

    void userSelectsMine();
    void userFlags(Board& userBoard);
    void userSelectsSafeSquare(Board& userBoard);
    void executeUserCommand(Board& userBoard);
};