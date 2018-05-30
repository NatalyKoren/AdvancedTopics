//
// Created by DELL on 26/05/2018.
//

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
}

int TournamentManager::runGameBetweenTwoPlayers(int numOfGames, std::string firstPlayerID, std::string secondPlayerID){
	GameManager game;
	game.setFirstPlayerAlgorithm(idToFactory[firstPlayerID]());
	game.setSecondPlayerAlgorithm(idToFactory[secondPlayerID]());
	int winner;

	// run the games
	for(int i=0; i<numOfGames; i++){
		winner = game.startAndRunGame();
		// --- LOCK ---
		scoreMutex.lock();
		if(winner == FIRST_PLAYER)
			idToScore[firstPlayerID]+= WINNING_POINTS;
		else if(winner == SECOND_PLAYER)
			idToScore[secondPlayerID]+= WINNING_POINTS;
		else{
			idToScore[firstPlayerID]+= TIE_POINTS;
			idToScore[secondPlayerID]+= TIE_POINTS;
		}
		// --- UNLOCK ---
		scoreMutex.unlock();
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
	void* algorithm = dlopen(folderPath.c_str(), RTLD_LAZY);

	if (!algorithm) {
		std::cout << "Cannot open library: " << dlerror();
		// TODO: handle error
		return 0;
	}
	// load the symbol
	typedef PlayerAlgorithm* create_t();
	typedef void destroy_t(PlayerAlgorithm*);

	create_t* create_algo = (create_t*)dlsym(algorithm, "create");
	destroy_t* destroy = (destroy_t*)dlsym(algorithm,"destroy");
	 if (!create_algo) {
		 std::cout << "The error is %s" << dlerror();
	 }
	 if (!destroy) {
		 std::cout << "The error is %s" << dlerror();
	 }
	 PlayerAlgorithm* algo = create_algo();
	 // TODO: call player algo methods?
	 destroy(algo);
	 return 1;
	/*
	// for when we have many so files: http://en.cppreference.com/w/cpp/filesystem/directory_iterator
	for(auto& file: std::filesystem::directory_iterator(filderPath)) {
		std::cout << file << std::endl;
	}
	*/

	// TODO: need to delete factory methods before closing the lib
	// close the library
	dlclose(algorithm);
}

