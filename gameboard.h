#include <iostream>
using namespace std;

class Gameboard{

    char gamespace[4][4];
    char winner;  // X, O, N for no winner
    int xScore;
    int oScore;
    bool gameState;
    char currentPlayer;

    public:
        Gameboard();
        int enterSpaceNumber(string rowOrColumn);
        void setGamespace(int row, int column);
        void printBoard();
        void setWinner(char winningPlayer);
        void setScore();
        void setCurrentPlayer();
        void clearGamespace();
        void setGameState(bool value);
        bool checkEmptyBoardSpace();
        void calculateWinner();
        void restartGame();
        void playGame();
        void playAgain();
        char playAgainQuestion();
        void verticalWin(char player);
        void diagonalWin(char player);
        void horizontalWin();
        void endGame();
        bool checkValidSpace(int value);

        ~Gameboard();
};
