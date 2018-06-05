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
#include <random>
#include <string.h>

#include <dlfcn.h>
#include <sys/types.h>
#include <dirent.h>

#include "PlayerAlgorithm.h"
#include "GameManager.h"
#include "AlgorithmRegistration.h"
//#include "AutoPlayerAlgorithm.h" // TODO REMOVE THIS - for addToMap function


class TournamentManager {
    static TournamentManager theTournamentManager;
    std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> idToFactory;
    // for saving game results
    std::map<std::string, int> idToScore;
    // For running the games
    std::map<std::string, int> idToGameCount;
    // Threads num
    int threadsNum;
    // Number of register players
    int playersNum;
    std::string folderPath;
    // lock for updating score
    std::mutex scoreMutex;
    // For game count map
    std::mutex GameCountMutex;
    // list for so files handle
    std::vector<void *> soFilesHandle;
    // private ctor
    TournamentManager():idToFactory(), idToScore(), threadsNum(0), playersNum(0), folderPath(".") {}
    ~TournamentManager();

public:
    // Get instance of class
    static TournamentManager& getTournamentManager() {
        return theTournamentManager;
    }
    // Block copy constructor and operator =
    TournamentManager& operator=(const TournamentManager&) = delete;
    TournamentManager(const TournamentManager&) = delete;
    /**
     * Register algorithm to tournament.
     * @param id - player id
     * @param factoryMethod - instance method
     */
    void registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod);

    // --- Setters ---
    void setThreadsNum(int num) { threadsNum = num; }
    void setDirectoryPath(std::string dirPath) { folderPath = dirPath;}

    /*
     * Verifies that a file name is of an "RSPPlayer_<id>.so" pattern
     * returns SUCCESS or ERROR accordingly
     */
    int verifyFileName(const char* filename);

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
     * @param firstPlayerID - first player id
     * @param secondPlayerID - second player id
     * @param updateSecondPlayer - if true update second player score (for leftover games).
     * @return ERROR if an ERROR occurred. SUCCESS otherwise.
     */
    int runGameBetweenTwoPlayers(std::string firstPlayerID, std::string secondPlayerID, bool updateSecondPlayer);
    /***
     * Return player id using randNum value
     * @param randNum - random number between zero to idToGameCount.size
     * @return playerId at randNum position on idToGameCount map
     */
    const std::string& getPlayerId(int randNum);
    /***
     * The main function for each thread. This will run games until no more games is left or
     * only one player left with games.
     * @param seedNum - the thread number. Used as seed for random numbers.
     */
    void runGamesInsideThread(int seedNum);
    /***
     * Run all tournament from the beginning: load files, run turnament and print results.
     */
    void startAll();

    // FOR TESTS ONLY
    void addToMap();
};



#endif //AT_EX3_GAMETOURNAMENTMANAGER_H
