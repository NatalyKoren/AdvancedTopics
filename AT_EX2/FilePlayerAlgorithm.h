//
// Created by DELL on 25/04/2018.
//

#ifndef AT_EX2_FILEPLAYERALGORITHM_H
#define AT_EX2_FILEPLAYERALGORITHM_H

#include <vector>
#include <memory> // for unique_ptr
#include "Point.h"
#include "PiecePosition.h"
#include "Board.h"
#include "FightInfo.h"
#include "Move.h"
#include "JokerChange.h"
#include "PlayerAlgorithm.h"

using std::unique_ptr;
class FilePlayerAlgorithm : public PlayerAlgorithm{
public:
    // should parse a file? or inside the constructor or in getInitialPositions
    FilePlayerAlgorithm() {}
    virtual void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill);
    // don't need implementation for file player - Does not important
    virtual void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights) {}
    virtual void notifyOnOpponentMove(const Move& move); // called only on opponents move
    virtual void notifyFightResult(const FightInfo& fightInfo); // called only if there was a fight
    virtual unique_ptr<Move> getMove();
    virtual unique_ptr<JokerChange> getJokerChange(); // nullptr if no change is requested
};



#endif //AT_EX2_FILEPLAYERALGORITHM_H
