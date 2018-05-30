//
// Created by DELL on 26/05/2018.
//

#ifndef AT_EX3_GAMETOURNAMENTMANAGER_H
#define AT_EX3_GAMETOURNAMENTMANAGER_H

#include <map>
#include <iostream>
#include <mutex>
#include <thread>
#include <algorithm>

#include <dlfcn.h>
#include <filesystem>

#include "PlayerAlgorithm.h"
#include "GameManager.h"
#include "AlgorithmRegistration.h"

class TournamentManager {
    static TournamentManager theTournamentManager;
    std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> idToFactory;
    // for saving game results
    std::map<std::string, int> idToScore;
    // Threads num
    int threadsNum;
    // Number of register players
    int playersNum;
    std::string folderPath;
    // lock for updating score
    std::mutex scoreMutex;
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
     * Print the tournament results to stream.
     * @param ostream - stream to print results.
     * @return ERROR in case an ERROR occurred. SUCCESS otherwise.
     */
    int printTournamentResults(std::ostream* ostream) const;

    /***
     * Each thread will run this function.
     * After every game, the thread will update the score according to the winner.
     * @param numOfGames - number of games to perform between the two players.
     * @param firstPlayerID - first player id
     * @param secondPlayerID - second player id
     * @return ERROR if an ERROR occurred. SUCCESS otherwise.
     */
    int runGameBetweenTwoPlayers(int numOfGames, std::string firstPlayerID, std::string secondPlayerID);

    // Todo remove this
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
