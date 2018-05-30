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
		std::cout << "id " << id << " already register! Overriding factory method." << std::endl;
	}
	idToFactory[id] = factoryMethod;
	idToScore[id] = 0;
    idToGameCount[id] = 0;
}

int TournamentManager::runGameBetweenTwoPlayers(std::string firstPlayerID, std::string secondPlayerID, bool updateSecondPlayer){
	GameManager game;
	game.setFirstPlayerAlgorithm(idToFactory[firstPlayerID]());
	game.setSecondPlayerAlgorithm(idToFactory[secondPlayerID]());
	int winner;

	// run the game
    winner = game.startAndRunGame();
    // --- LOCK ---
    std::lock_guard<std::mutex> guard(scoreMutex);
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

int TournamentManager::loadDynamicFilesForGames() {
	/*
	void* algorithm = dlopen(folderPath.c_str(), RTLD_LAZY);

	if (!algorithm) {
		std::cout << "Cannot open library: " << dlerror();
		// TODO: handle error
		return 0;
	}*/
//	// load the symbol
//	typedef PlayerAlgorithm* create_t();
//	typedef void destroy_t(PlayerAlgorithm*);
//
//	create_t* create_algo = (create_t*)dlsym(algorithm, "register_me_307941401");
//	//destroy_t* destroy = (destroy_t*)dlsym(algorithm,"destroy");
//	 if (!create_algo) {
//		 std::cout << "The error is %s" << dlerror();
//	 }
////	 if (!destroy) {
////		 std::cout << "The error is %s" << dlerror();
////	 }
//	 PlayerAlgorithm* algo = create_algo();
//	 destroy(algo);
//	 return 1;
	/*
	// for when we have many so files: http://en.cppreference.com/w/cpp/filesystem/directory_iterator
	for(auto& file: std::filesystem::directory_iterator(filderPath)) {
		std::cout << file << std::endl;
	}
	*/

	// TODO: need to delete factory methods before closing the lib
	// close the library
	/*dlclose(algorithm);*/
	return SUCCESS;
}

void TournamentManager::runGamesInsideThread(int seedNum){
    std::string firstPlayer;
    std::string  secondPlayer;
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

        runGameBetweenTwoPlayers(firstPlayer,secondPlayer,true);
    }
}

std::string& TournamentManager::getPlayerId(int randNum){
    std::map<std::string,int>::iterator randomIter = idToGameCount.begin();
    std::advance(randomIter, randNum);
    randomIter->first;
}

int TournamentManager::runTournament(){
    std::vector<std::thread> threads;
    std::string leftPlayer;
    std::map<std::string,int>::iterator mapIter;

    for (int i = 0; i < threadsNum; i++) {
        threads.push_back(std::thread(runGamesInsideThread,this, i));
    }
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
}


int TournamentManager::addToMap(){
    registerAlgorithm("123", []{return std::make_unique<RSPPlayer_307941401>();} );
    registerAlgorithm("456", []{return std::make_unique<RSPPlayer_307941401>();} );
    registerAlgorithm("789", []{return std::make_unique<RSPPlayer_307941401>();} );
    registerAlgorithm("789", []{return std::make_unique<RSPPlayer_307941401>();} );
    registerAlgorithm("111", []{return std::make_unique<RSPPlayer_307941401>();} );
    registerAlgorithm("112", []{return std::make_unique<RSPPlayer_307941401>();} );
}
