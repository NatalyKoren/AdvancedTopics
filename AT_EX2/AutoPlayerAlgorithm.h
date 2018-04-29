//
// Created by DELL on 29/04/2018.
//

#ifndef AT_EX2_AUTOPLAYERALGORITHM_H
#define AT_EX2_AUTOPLAYERALGORITHM_H

#include "PlayerAlgorithm.h"
#include "GameMove.h"
class AutoPlayerAlgorithm : public PlayerAlgorithm {
    int player;
public:
    AutoPlayerAlgorithm(int playerNum):player(playerNum) {}
    virtual void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill);
    virtual void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights);
    virtual void notifyOnOpponentMove(const Move& move); // called only on opponents move
    virtual void notifyFightResult(const FightInfo& fightInfo); // called only if there was a fight
    virtual unique_ptr<Move> getMove();
    virtual unique_ptr<JokerChange> getJokerChange(); // nullptr if no change is requested

};


#endif //AT_EX2_AUTOPLAYERALGORITHM_H
