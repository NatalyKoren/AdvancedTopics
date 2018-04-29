//
// Created by DELL on 29/04/2018.
//

#include "AutoPlayerAlgorithm.h"

void AutoPlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill){

}

void AutoPlayerAlgorithm::notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights){

}

void AutoPlayerAlgorithm::notifyOnOpponentMove(const Move& move){

}

void AutoPlayerAlgorithm::notifyFightResult(const FightInfo& fightInfo){

}

unique_ptr<Move> AutoPlayerAlgorithm::getMove(){
    return std::make_unique<GameMove>(FIRST_PLAYER);
}

unique_ptr<JokerChange> AutoPlayerAlgorithm::getJokerChange(){
    return std::make_unique<GameJokerChanged>();
}