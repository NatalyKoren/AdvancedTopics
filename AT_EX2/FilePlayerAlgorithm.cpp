//
// Created by DELL on 25/04/2018.
//
#include "FilePlayerAlgorithm.h"


void FilePlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill){

}


void FilePlayerAlgorithm::notifyOnOpponentMove(const Move& move){

}

void FilePlayerAlgorithm::notifyFightResult(const FightInfo& fightInfo){

}

unique_ptr<Move> FilePlayerAlgorithm::getMove(){
    return std::make_unique<GameMove>(FIRST_PLAYER);
}

unique_ptr<JokerChange> FilePlayerAlgorithm::getJokerChange(){
    return std::make_unique<GameJokerChanged>();
}
