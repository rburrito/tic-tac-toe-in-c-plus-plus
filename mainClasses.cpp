#include <iostream>
using namespace std;
#include "mainFunctions.cpp"

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

Gameboard::Gameboard(){
    gameState = true;
    xScore=0;
    oScore=0;
    setWinner('N');  // setting to no winner
    setCurrentPlayer();
    clearGamespace();
}


void Gameboard::setGamespace(int row, int column){

  if (gamespace[row-1][column-1]=='-'){
    gamespace[row-1][column-1]=currentPlayer;
    printBoard();
    calculateWinner();
    if (winner == 'X' || winner == 'O'){
      cout << "Game over\n";
      cout << "Current score: X - "<< xScore << ", O - " << oScore << endl;
      playAgain();
    }
    setCurrentPlayer();
  }
   else {

    cout << "Space already taken by " << gamespace[row-1][column-1]<<". Please choose a different space.\n";
  }
}

void Gameboard::printBoard(){
  for (int i=0; i < 3; i++){
    for (int j=0; j < 3; j++){
      cout << gamespace[i][j]<<" ";
    }
      cout << endl;
  }
  cout << endl;
}

void Gameboard::calculateWinner(){

  // horizontal calculation
  horizontalWin();

  // vertical calculation  spaces [0][0], [1][0], [2][0]; [0][1], [1][1], [2][1]; [0][2], [1][2], [2],[2]
  verticalWin('X');
  verticalWin('O');

  // diagonal calculation spaces [0][0], [1][1], [2][2]; [0][2], [1],[1], [2][0]
  diagonalWin('X');
  diagonalWin('O');

  setScore();
}

void Gameboard::horizontalWin(){
  for (int i=0; i < 3; i++){
    int xWin = 0;
    int oWin = 0;
    for (int j=0; j < 3; j++){
      if (gamespace[i][j] == 'X'){
        xWin+=1;
      } else if (gamespace[i][j]=='O'){
        oWin+=1;
      }
    }
    if (xWin==3){
      cout << "Player X wins.\n";
      setWinner('X');
    } else if (oWin==3) {
      cout << "Player O wins.\n";
      setWinner('O');
    }
  }
}

void Gameboard::verticalWin(char player){
  if (gamespace[0][0]==player && gamespace[1][0]==player && gamespace[2][0]==player|| gamespace[0][1]==player && gamespace[1][1]==player && gamespace[2][1]==player|| gamespace[0][2]==player && gamespace[1][2]==player && gamespace[2][2]==player){
    setWinner(player);
  }
}

void Gameboard::diagonalWin(char player){
  if (gamespace[0][0]==player && gamespace[1][1]==player && gamespace[2][2]==player || gamespace[0][2]==player && gamespace[1][1]==player && gamespace[2][0]==player){
    setWinner(player);
  }
}

void Gameboard::setWinner(char winningPlayer){
  winner = winningPlayer;
}

void Gameboard::setScore(){
  if (winner=='X'){
    xScore+=1;
  } else if (winner == 'O') {
    oScore+=1;
  }
}

void Gameboard::setCurrentPlayer(){
    if (currentPlayer == 'X'){
      currentPlayer = 'O';
    } else if (currentPlayer='O'){
      currentPlayer = 'X';
    }

  if (gameState){
    cout << "Current player: "<<currentPlayer<<"\n";
  }
}

int Gameboard::enterSpaceNumber(string rowOrColumn){
  bool isValidSpace;
  int spaceNumber;
  cout << "Player "<< currentPlayer<<", please enter "<< rowOrColumn << " number. \n";
  cin >> spaceNumber;

  isValidSpace = checkValidSpace(spaceNumber);
  if (isValidSpace){
    return spaceNumber;
  } else {
    return enterSpaceNumber(rowOrColumn);
  }

}

bool Gameboard::checkValidSpace(int value){
    if (value > 3 || value < 1 ){
      return false;
    }
    return true;
}

void Gameboard::clearGamespace(){
  for (int i = 0; i < 3; i++){
      for (int j = 0; j < 3; j++){
          gamespace[i][j]='-';
      }
  }
}

bool Gameboard::checkEmptyBoardSpace(){
  for (int i=0; i < 3; i++){
    for (int j=0; j < 3; j++){
      if(gamespace[i][j]=='-'){
        return true;
      }
    }
  }
  return false;
}

void Gameboard::setGameState(bool value){
  gameState=value;
}


void Gameboard::playGame(){
int playerRowValue;
int playerColumnValue;
 while (gameState) {
   if (checkEmptyBoardSpace()){
     playerRowValue = enterSpaceNumber("row");
     playerColumnValue = enterSpaceNumber("column");
     setGamespace(playerRowValue, playerColumnValue);
    } else {
    cout << "No more remaining spaces to fill.\n";
    //winner = 'T';
    playAgain();
      }
  }
}

void Gameboard::restartGame(){
  setGameState(true);
  clearGamespace();
  winner ='N';
}

void Gameboard::playAgain(){
 char answer;
   while (answer != 'y' && answer !='n' ){
    answer = playAgainQuestion();
    if (answer=='y'){

      restartGame();
    } else if (answer=='n'){
      endGame();
     break;
    } else {
      cout<< "Wrong value.";
    }
  }
}

void Gameboard::endGame(){
  setGameState(false);
}


char Gameboard::playAgainQuestion(){
  char anotherGame;
  cout << "Do you want to play again? Type y or n. ";
  cin >> anotherGame;
  cout << endl;
  return anotherGame;
}

Gameboard::~Gameboard(){
    cout<<"Exiting game!\n";
}
