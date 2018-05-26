#include <iostream>
#include "GameManager.h"
#include "FilePlayerAlgorithm.h"
#include "AutoPlayerAlgorithm.h"
#include "GameTournamentManager.h"

int main(int argc, char *argv[]){
    /*
    if(argc < 2){
        std::cout<< "USAGE: Command line arguments" << std::endl;
        return ERROR;
    }
    GameManager game;
    char *format = argv[1];
    if(strcmp(format, "auto-vs-file")==0){
        game.setFirstPlayerAlgorithm(std::make_unique<RSPPlayer_307941401>(FIRST_PLAYER));
        game.setSecondPlayerAlgorithm(std::make_unique<FilePlayerAlgorithm>(SECOND_PLAYER));
    }
    else if(strcmp(format, "file-vs-auto")==0){
        game.setFirstPlayerAlgorithm(std::make_unique<FilePlayerAlgorithm>(FIRST_PLAYER));
        game.setSecondPlayerAlgorithm(std::make_unique<RSPPlayer_307941401>(SECOND_PLAYER));
    }
    else if(strcmp(format, "auto-vs-auto")==0){
        game.setFirstPlayerAlgorithm(std::make_unique<RSPPlayer_307941401>(FIRST_PLAYER));
        game.setSecondPlayerAlgorithm(std::make_unique<RSPPlayer_307941401>(SECOND_PLAYER));
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
    */
    int numOfThreads = DEFAULT_THREADS_NUM;
    std::string pathToFiles = "./"; // Current working directory
    // Parse command line arguments
    for(int i=1; i<argc; i++){
        // Threads
        if((strcmp(argv[i],"-threads") == 0)){
            if( i+1 < argc){
                // try to get threads number
                if(sscanf(argv[i], " %d ", &numOfThreads) != 1)
                    numOfThreads = DEFAULT_THREADS_NUM;
            }

        }
        // Path
        if((strcmp(argv[i],"-path") == 0)){
            if( i+1 < argc){
                // try to get threads number
                pathToFiles = argv[i];
            }

        }
    }

    TournamentManager::getTournamentManager().setThreadsNum(numOfThreads);
    TournamentManager::getTournamentManager().setDirectoryPath(pathToFiles);
    TournamentManager::getTournamentManager().print();
    return 0;
}
