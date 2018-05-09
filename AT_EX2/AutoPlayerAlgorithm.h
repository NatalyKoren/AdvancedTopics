//
// Created by DELL on 29/04/2018.
//

#ifndef AT_EX2_AUTOPLAYERALGORITHM_H
#define AT_EX2_AUTOPLAYERALGORITHM_H

#include "PlayerAlgorithm.h"
#include "GameBoard.h"
#include "InterfacePiecePosition.h"
#include <algorithm>
#include <stdlib.h>
#include <memory>

class AutoPlayerAlgorithm : public PlayerAlgorithm {
    int player;
    GameBoard game;
    int opponent;
    int opponentPieceCount;
    int pieceCount[NUM_OF_DIFF_PIECES]; //counts how many pieces of each type we have: RPSBJF
    // contains positions of the opponent player with UNKNOWN_PIECE.
    std::vector<unique_ptr<Position>> nonMovingPositions;
    // contains moving pieces of player.
    std::vector<unique_ptr<Position>> playerMovingPositions;
public:
    AutoPlayerAlgorithm(int playerNum):player(playerNum), game(), opponent(game.getOpponent(playerNum)),
                                       opponentPieceCount(0),nonMovingPositions(), playerMovingPositions(){}
    // --- Interface functions ---
    virtual void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill);
    virtual void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights);
    virtual void notifyOnOpponentMove(const Move& move); // called only on opponents move
    virtual void notifyFightResult(const FightInfo& fightInfo); // called only if there was a fight
    virtual unique_ptr<Move> getMove();
    virtual unique_ptr<JokerChange> getJokerChange(); // nullptr if no change is requested

    /***
     * Calculates opponent pieces score.
     * Non - Moving pieces get more points then moving pieces.
     * @return score for the opponent pieces
     */

    int getOpponentPieceScore() const;
    /***
     * Calculate the best next move for player
     * @param move - move will be updated at the end of the function with the best move.
     */
    void getBestMoveForPlayer(GameMove& move);
    /***
     * Remove posToRemove from vectorType vector.
     * @param vectorType - NON_MOVING_VECTOR for the nonMovingPositions vector. MOVING_VECTOR for the playerMovingPositions.
     * @param posToRemove - remove from the vectorType the position posToRemove if exists.
     */
    void removePieceFromVector(int vectorType,const Position& posToRemove);
    /***
     * Update move destination position according to direction.
     * @param moveToCheck - the move to be updated.
     * @param moveDirection - UP/DOWN/LEFT/RIGHT.
     */
    void updateMoveWithDirection(GameMove& moveToCheck, int moveDirection) const;
    /***
     * Return the scoring for moveToCheck
     * @param moveToCheck - move to be scored
     * @return scoring value for move
     */
    float scoreMoveOnBoard(GameMove& moveToCheck);
    /**
     * Return the winner of the fight if we can know it from opponentChar
     * assuming ourChar is a moving piece
     * @param ourChar
     * @param opponentChar
     * @return
     */
    int getWinnerOfFight(char ourChar, char opponentChar) const;

};



#endif //AT_EX2_AUTOPLAYERALGORITHM_H
