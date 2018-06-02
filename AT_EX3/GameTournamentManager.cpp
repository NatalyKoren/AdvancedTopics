//
// Created by DELL on 26/05/2018.
//

#include <random>
#include "GameTournamentManager.h"

TournamentManager TournamentManager::theTournamentManager;

AlgorithmRegistration::AlgorithmRegistration(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod) {
	TournamentManager::getTournamentManager().registerAlgorithm(id, factoryMethod);
}

void TournamentManager::registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod) {
	if(idToFactory.find(id) != idToFactory.end()){
		std::cout << "id " << id << " already registered! Overriding factory method." << std::endl;
	}
	idToFactory[id] = factoryMethod;
	idToScore[id] = 0;
    idToGameCount[id] = 0;
}

int TournamentManager::runGameBetweenTwoPlayers(std::string firstPlayerID, std::string secondPlayerID, bool updateSecondPlayer){
	GameManager game;
	// TODO: In the next line, idToFactory[firstPlayerID] is a nullptr - need to debug
	game.setFirstPlayerAlgorithm(idToFactory[firstPlayerID]());
	game.setSecondPlayerAlgorithm(idToFactory[secondPlayerID]());
	int winner;
	// run the game
    winner = game.startAndRunGame();
    // --- LOCK ---
    std::lock_guard<std::mutex> guard(scoreMutex);
    // TODO REMOVE THIS
    std::cout << "run game between " << firstPlayerID << " and " << secondPlayerID << " " << updateSecondPlayer <<std::endl;
    if(winner == FIRST_PLAYER)
        idToScore[firstPlayerID]+= WINNING_POINTS;
    else if(winner == SECOND_PLAYER && updateSecondPlayer)
        idToScore[secondPlayerID]+= WINNING_POINTS;
    else{
        idToScore[firstPlayerID]+= TIE_POINTS;
        if(updateSecondPlayer) idToScore[secondPlayerID]+= TIE_POINTS;
    }
	return SUCCESS;
}

int TournamentManager::printTournamentResults(std::ostream* ostream) const{
	std::map<int, std::string, std::greater<int>> sortedMap;
	int score;
	std::string id;
	// insert values to new map
	for(auto& pair : idToScore) {
		score = pair.second;
		id = pair.first;
		sortedMap[score] = id;
	}

	// now sortedMap is a descending order map.
	for(auto& pair : sortedMap) {
		score = pair.first;
		id = pair.second;
		*ostream << id << " " << score << std::endl;
		if(ostream->bad())
			return ERROR;
	}
	return SUCCESS;
}

int TournamentManager::verifyFileName(const char* fileName) {
	std::string filename(fileName);
	std::string start("RSPPlayer_");
	std::string end(".so");
	if (filename.length() != 22) return ERROR;
	std::string fileStart(filename.substr(0, start.length()));
	if (fileStart.compare(start) != 0) return ERROR;

	std::string fileEnd(filename.substr(start.length()+9, 22));
	if (fileEnd.compare(end) != 0) return ERROR;
	return SUCCESS;
}

int TournamentManager::loadDynamicFilesForGames() {
	DIR* directory = opendir(folderPath.c_str());
	if (directory == NULL) {
		std::cout << "Could not open the provided path: " << folderPath << std::endl;
		return ERROR;
	}
    std::cout << "start loading files" << std::endl;
	struct dirent* ep;
	while ((ep = readdir(directory))) {
		if (verifyFileName(ep->d_name) == SUCCESS) {
			std::cout << ep->d_name << std::endl;
			std::string fullPath(folderPath + std::string("/") + std::string(ep->d_name));
			void* algorithm = dlopen(fullPath.c_str(), RTLD_LAZY);
			if (!algorithm) {
				std::cout << "Cannot open library: " << dlerror() << std::endl;
				return ERROR;
			}
//			dlclose(algorithm);
		}
	}
	// close the library
	(void) closedir(directory);
    std::cout << "done loading files" << std::endl;
	// TODO: need to delete factory methods before closing the lib
	return SUCCESS;
}

void TournamentManager::runGamesInsideThread(int seedNum){
    std::string firstPlayer;
    std::string  secondPlayer;
    // For random numbers
    std::default_random_engine generator(seedNum*10);
    std::uniform_int_distribution<int> distribution(0,idToGameCount.size());
    while(idToGameCount.size() > 1){
        firstPlayer = "";
        secondPlayer = "";
        while(firstPlayer.compare(secondPlayer) == 0){
            firstPlayer = getPlayerId(distribution(generator)%idToGameCount.size());
            secondPlayer = getPlayerId(distribution(generator)%idToGameCount.size());
        }
        // --- Lock
        GameCountMutex.lock();

        idToGameCount[firstPlayer]++;
        idToGameCount[secondPlayer]++;

        if(idToGameCount[firstPlayer] == GAMES_COUNT)
            idToGameCount.erase(firstPlayer);

        if(idToGameCount[secondPlayer] == GAMES_COUNT)
            idToGameCount.erase(secondPlayer);

        // --- Unlock
        GameCountMutex.unlock();
        // run game between players
        runGameBetweenTwoPlayers(firstPlayer,secondPlayer,true);
    }
}

const std::string& TournamentManager::getPlayerId(int randNum){
    std::map<std::string,int>::iterator randomIter = idToGameCount.begin();
    if((unsigned int)randNum > idToGameCount.size())
        return randomIter->first;
    std::advance(randomIter, randNum);
    return randomIter->first;
}

int TournamentManager::runTournament(){
    std::vector<std::thread> threads;
    std::string leftPlayer;
    std::map<std::string,int>::iterator mapIter;
    // define and run threads
    for (int i = 0; i < threadsNum; i++) {
        threads.push_back(std::thread(&TournamentManager::runGamesInsideThread, this, i));
//    	runGamesInsideThread(i);
    }
    // Join all threads
    for (auto& th : threads)
        th.join();
    // handle leftover algorithms
    if(idToGameCount.size() > 0){
        // assuming idToGameCount.size() == 1
        if(idToGameCount.size() != 1)
            std::cout << "idToGameCount size is: " << idToGameCount.size() << std::endl; // TODO: remove this
        leftPlayer = idToGameCount.begin()->first;
        mapIter = idToScore.begin();
        while(idToGameCount[leftPlayer] < GAMES_COUNT){
            // do not play against yourself
            if(leftPlayer.compare(mapIter->first) != 0){
                runGameBetweenTwoPlayers(leftPlayer,mapIter->first,false);
                idToGameCount[leftPlayer]++;
            }
            mapIter++;
            // If we reached the end of the map - start over
            if(mapIter == idToScore.end())
                mapIter = idToScore.begin();
        }
    }
    return SUCCESS;
}


void TournamentManager::addToMap(){
    /*
    registerAlgorithm("123", []{return std::make_unique<RSPPlayer_222222222>();} );
    registerAlgorithm("456", []{return std::make_unique<RSPPlayer_222222222>();} );
    registerAlgorithm("789", []{return std::make_unique<RSPPlayer_222222222>();} );
    registerAlgorithm("222", []{return std::make_unique<RSPPlayer_222222222>();} );
    registerAlgorithm("111", []{return std::make_unique<RSPPlayer_222222222>();} );
    registerAlgorithm("112", []{return std::make_unique<RSPPlayer_222222222>();} );
     */
}


void TournamentManager::startAll(){
    // load files
    loadDynamicFilesForGames();
    if(idToFactory.size() <2){
        std::cout << "There is not enough players for tournament!" << std::endl;
        return;
    }
    // run tournament
    runTournament();
    // print results
    printTournamentResults(&std::cout);
    // Done
}
