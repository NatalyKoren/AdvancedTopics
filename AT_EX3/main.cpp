#include <iostream>
#include <unistd.h>
#include "GameManager.h"
#include "GameTournamentManager.h"

int main(int argc, char *argv[]){
    int numOfThreads = DEFAULT_THREADS_NUM;
    // Getting current working directory as default path for .so files
    char buff[FILENAME_MAX];
    getcwd( buff, FILENAME_MAX );

    std::string pathToFiles(buff); // Current working directory
    std::cout << "argc is " << argc << std::endl; //DEBUG
    // Parse command line arguments
    for(int i=1; i<argc; i++){
        // Threads
        if((strcmp(argv[i],"-threads") == 0)){
            if( i+1 < argc){
                // try to get threads number
                if(sscanf(argv[i+1], " %d ", &numOfThreads) != 1)
                    numOfThreads = DEFAULT_THREADS_NUM;
            }
        }
        // Path
        if((strcmp(argv[i],"-path") == 0)){
            if( i+1 < argc){
                // try to get path
                pathToFiles = argv[i+1];
            }

        }
    }
    TournamentManager::getTournamentManager().setThreadsNum(numOfThreads);
    TournamentManager::getTournamentManager().setDirectoryPath(pathToFiles);
    TournamentManager::getTournamentManager().startAll();
    return 0;
}
