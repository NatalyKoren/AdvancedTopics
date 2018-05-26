//
// Created by DELL on 26/05/2018.
//

#include "GameTournamentManager.h"

TournamentManager TournamentManager::theTournamentManager;

AlgorithmRegistration::AlgorithmRegistration(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod) {
    TournamentManager::getTournamentManager().registerAlgorithm(id, factoryMethod);
}

void TournamentManager::registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod) {
    // TODO: should warn if id is already registered
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