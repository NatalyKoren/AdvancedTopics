#include <iostream>
#include "GameManager.h"
#include "FilePlayerAlgorithm.h"
#include "AutoPlayerAlgorithm.h"

int main(int argc, char *argv[]){
    if(argc < 2){
        std::cout<< "USAGE: Command line arguments" << std::endl;
        return ERROR;
    }
    GameManager game;
    char *format = argv[1];
    if(strcmp(format, "auto-vs-file")==0){
        game.setFirstPlayerAlgorithm(std::make_unique<AutoPlayerAlgorithm>(FIRST_PLAYER));
        game.setSecondPlayerAlgorithm(std::make_unique<FilePlayerAlgorithm>(SECOND_PLAYER));
    }
    else if(strcmp(format, "file-vs-auto")==0){
        game.setFirstPlayerAlgorithm(std::make_unique<FilePlayerAlgorithm>(FIRST_PLAYER));
        game.setSecondPlayerAlgorithm(std::make_unique<AutoPlayerAlgorithm>(SECOND_PLAYER));
    }
    else if(strcmp(format, "auto-vs-auto")==0){
        game.setFirstPlayerAlgorithm(std::make_unique<AutoPlayerAlgorithm>(FIRST_PLAYER));
        game.setSecondPlayerAlgorithm(std::make_unique<AutoPlayerAlgorithm>(SECOND_PLAYER));
    }
    else if(strcmp(format, "file-vs-file")==0){
        game.setFirstPlayerAlgorithm(std::make_unique<FilePlayerAlgorithm>(FIRST_PLAYER));
        game.setSecondPlayerAlgorithm(std::make_unique<FilePlayerAlgorithm>(SECOND_PLAYER));
    }
    else{
        std::cout<< "ERROR: Unknown command line arguments format" << std::endl;
        return ERROR;
    }
    // For Auto Player initial board
    srand(time(0));

	int result = game.startAndRunGame();

    if(result == ERROR)
        std::cout<< "Game ended with errors." << std::endl;

    //masterTestGameBoard();
    return 0;
}
