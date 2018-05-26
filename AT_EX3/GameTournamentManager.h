//
// Created by DELL on 26/05/2018.
//

#ifndef AT_EX3_GAMETOURNAMENTMANAGER_H
#define AT_EX3_GAMETOURNAMENTMANAGER_H

#include <map>
#include <iostream>
#include "PlayerAlgorithm.h"
#include "GameManager.h"
#include "AlgorithmRegistration.h"

class TournamentManager {
    static TournamentManager theTournamentManager;
    std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> idToFactory;
    // for saving game results
    std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> idToScore;
    // Threads num
    int threadsNum;
    int playersNum;
    std::string folderPath;
    // private ctor
    TournamentManager():idToFactory(), idToScore(), threadsNum(0), playersNum(0), folderPath() {}
public:
    // Get instance of class
    static TournamentManager& getTournamentManager() {
        return theTournamentManager;
    }
    void registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod);
    // for tests
    void print(){std::cout <<"hii!" <<std::endl;}

    void setThreadsNum(int num) { threadsNum = num; }
    void setDirectoryPath(std::string dirPath) { folderPath = dirPath;}


    /***
     * Open folderPath and load all dynamic files in it.
     * @return number of loaded files.
     */
    int loadDynamicFilesForGames();

    /***
     * Run all the games in tournament.
     * @return ERROR in case an ERROR occurred. SUCCESS otherwise.
     */
    int runTournament();

    /**
     * Print the tournament results.
     * @return ERROR in case an ERROR occurred. SUCCESS otherwise.
     */
    int printTournamentResults();

    void run()const {
        for(auto& pair : idToFactory) {
            const auto& id = pair.first;
            std::cout << id << ": ";
            const auto& factoryMethod = pair.second;
            factoryMethod();
        }
    }
};




#endif //AT_EX3_GAMETOURNAMENTMANAGER_H
