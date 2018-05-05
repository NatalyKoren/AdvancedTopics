#include <iostream>
//#include "GameBoardUnitTest.h"
#include "GameManager.h"
int main(int argc, char *argv[]){
    if(argc < 2){
        std::cout<< "USAGE: Command line arguments" << std::endl;
        return ERROR;
    }
    int firstPlayer, secondPlayer;
    char *format = argv[1];
    if(strcmp(format, "auto-vs-file")==0){
        firstPlayer = AUTO_PLAYER;
        secondPlayer = FILE_PLAYER;
    }
    else if(strcmp(format, "file-vs-auto")==0){
        firstPlayer = FILE_PLAYER;
        secondPlayer = AUTO_PLAYER;
    }
    else if(strcmp(format, "auto-vs-auto")==0){
        firstPlayer = AUTO_PLAYER;
        secondPlayer = AUTO_PLAYER;
    }
    else if(strcmp(format, "file-vs-file")==0){
        firstPlayer = FILE_PLAYER;
        secondPlayer = FILE_PLAYER;
    }
    else{
        std::cout<< "ERROR: Unknown command line arguments format" << std::endl;
        return ERROR;
    }
    GameManager game(firstPlayer,secondPlayer);
    int result = game.startAndRunGame();
    if(result == ERROR)
        std::cout<< "Game ended with errors." << std::endl;

    //masterTestGameBoard();
    return 0;
}
