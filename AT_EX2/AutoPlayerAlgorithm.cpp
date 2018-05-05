//
// Created by DELL on 29/04/2018.
//

#include "AutoPlayerAlgorithm.h"

void AutoPlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill){

}

void AutoPlayerAlgorithm::notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights){
    int opponent = game.getOpponent(player);
    Position pos(0,0);
    int winner;
    // update opponent pieces on board
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            pos.setXposition(i);
            pos.setYposition(j);
            if(b.getPlayer(pos) == opponent)
                game.setPieceAtPosition(opponent,UNKNOWN_PIECE,pos);
        }
    }
    // now check for fights...
    for(const unique_ptr<FightInfo>& fight: fights){
        winner = fight->getWinner();
        // current player wins the fight
        // need to update opponents board
        if(winner == player){
            // delete the char from opponents board
            game.setPieceAtPosition(opponent, (char)0, fight->getPosition());
        }
        else if(winner == opponent){
            // need to update player board
            game.updateAfterLoseFight(player,fight->getPosition());
            // it is a moving piece of the opponent
            game.setPieceAtPosition(opponent, MOVING_PIECE,fight->getPosition());
        }
    }


}

void AutoPlayerAlgorithm::notifyOnOpponentMove(const Move& move){

}

void AutoPlayerAlgorithm::notifyFightResult(const FightInfo& fightInfo){

}

unique_ptr<Move> AutoPlayerAlgorithm::getMove(){
    return std::make_unique<GameMove>(FIRST_PLAYER);
}

unique_ptr<JokerChange> AutoPlayerAlgorithm::getJokerChange(){
    return nullptr;
}

int AutoPlayerAlgorithm::scoringFunction() const{
    return 0;
}