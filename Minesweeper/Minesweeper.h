#include <iostream>
#include <vector>
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
    void setFlagSquare(char userInput);
    void mineSquare();
    void uncoverSquare();
    void updateAdjacentMines(); //adds 1 to adjacentMines

};


class Board{
    private:
    std::vector<std::vector<Square>> boardSquares = {}; //2D vector of squares that make up the board
    const int width; //width of the board
    const int height; //height of the board
    const int numberOfMines;
    const int totalNumberOfSquares;
    int squaresUncovered = 0;
    int squaresFlagged = 0;
    std::vector<std::vector<int>> allMineLocations;

    static int determineNumberOfMines(std::string gameMode){
        if (gameMode == "easy"){
            return 10;
        }
        if (gameMode == "medium"){
            return 40;
        }
        if (gameMode == "hard"){
            return 99;
        }
        return 0;
    }

    static int determineTotalNumberOfSquares(std::string gameMode){
                if (gameMode == "easy"){
            return 81; //9*9
        }
        if (gameMode == "medium"){
            return 256; //16*16
        }
        if (gameMode == "hard"){
            return 480; //30*16
        }
        return 0;
    }

    static int determineWidth(std::string gameMode){
        if (gameMode == "easy"){
            return 9;
        }
        if (gameMode == "medium"){
            return 16;
        }
        if (gameMode == "hard"){
            return 30;
        }
        return 0;

    }

    static int determineHeight(std::string gameMode){
        if (gameMode == "easy"){
            return 9;
        }
        if (gameMode == "medium" || gameMode == "hard"){
            return 16;
        }
        return 0;
    }
    

    public:
    //Constructor
    Board(std::string gameMode); //within this constructor, using random number generator, randomnly generate mine coordinates, and make the squares constructed with those coordinates into mines
    
    std::vector<std::vector<Square>> get_boardSquares();
    
    int get_numberOfMines();
    int get_width();
    int get_height();
    int get_squaresUncovered();
    int get_squaresFlagged();
    std::vector<std::vector<int>> get_allMineLocations();

    void displayBoard(); //generates board with flags and open squares
    void setSquareFlag(int row, int col, char userInput);
    void setSquareMine(int row, int col);
    void setSquareUncover(int row, int col);
    void setSquareAdjacentMines(int row, int col);
    //void placeMines();
    //void placeNumbers(); //places numbers that indicate how many mines surround the square
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
    void updateUserRow(int row);
    void updateUserCol(int col);

    void promptUser(Board& userBoard);//prompts user to pick a square and specify

    void userSelectsMine();
    void userSetsFlag(Board& userBoard, int row, int col, char userInput);
    void userSelectsSafeSquare(Board& userBoard, int row, int col);
    void executeUserCommand(Board& userBoard);
    void checkWinCondition(Board& userBoard);
};