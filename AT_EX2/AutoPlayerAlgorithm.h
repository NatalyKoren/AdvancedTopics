//
// Created by DELL on 29/04/2018.
//

#ifndef AT_EX2_AUTOPLAYERALGORITHM_H
#define AT_EX2_AUTOPLAYERALGORITHM_H

#include "PlayerAlgorithm.h"
#include "GameBoard.h"
#include <algorithm>

class AutoPlayerAlgorithm : public PlayerAlgorithm {
    int player;
    GameBoard game;
    int opponent;
    int opponentPieceCount;
    std::vector<unique_ptr<Position>> nonMovingPositions;
    std::vector<unique_ptr<Position>> playerMovingPositions;
public:
    AutoPlayerAlgorithm(int playerNum):player(playerNum), game(), opponent(game.getOpponent(playerNum)),
                                       opponentPieceCount(0),nonMovingPositions(), playerMovingPositions(){}
    virtual void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill);
    virtual void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights);
    virtual void notifyOnOpponentMove(const Move& move); // called only on opponents move
    virtual void notifyFightResult(const FightInfo& fightInfo); // called only if there was a fight
    virtual unique_ptr<Move> getMove();
    virtual unique_ptr<JokerChange> getJokerChange(); // nullptr if no change is requested
    // it will calculate the scoring of the two vectors
    int scoringFunction() const;
    int getOpponentPieceScore() const;
    char getPieceFromWinningFight(char losingPiece) const;
    void getBestMoveForPlayer(GameMove& move) const;
    void removePieceFromVector(int vectorType,const Position& posToRemove);

};



#endif //AT_EX2_AUTOPLAYERALGORITHM_H
