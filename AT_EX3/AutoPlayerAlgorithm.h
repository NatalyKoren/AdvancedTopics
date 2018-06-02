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
#include <time.h>
#include <memory>
#include "AlgorithmRegistration.h"


class RSPPlayer_222222222 : public PlayerAlgorithm {
	int player;
	GameBoard game;
	int opponent;
	int opponentPieceCount;
	//counts how many pieces of each type we have: R,P,S,B,J,F
	int pieceCount[NUM_OF_DIFF_PIECES];
	// contains positions of the opponent player with UNKNOWN_PIECE.
	std::vector<unique_ptr<Position>> nonMovingPositions;
	// contains moving pieces of player.
	std::vector<unique_ptr<Position>> playerMovingPositions;
	// for debugging
	std::ofstream autoFilePlayer;

	void init();

public:
	// --- Constructor ---
	RSPPlayer_222222222(int playerNum);
	RSPPlayer_222222222(): player(FIRST_PLAYER), opponent(game.getOpponent(FIRST_PLAYER)),
			opponentPieceCount(0),pieceCount{R,P,S,B,J,F}
			{init();}

	//--- Destructor ---
	~RSPPlayer_222222222() { if(autoFilePlayer.is_open()) autoFilePlayer.close();}
	// --- Interface functions ---
	virtual void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) override;
	virtual void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights) override;
	virtual void notifyOnOpponentMove(const Move& move) override; // called only on opponents move
	virtual void notifyFightResult(const FightInfo& fightInfo) override; // called only if there was a fight
	virtual unique_ptr<Move> getMove() override;
	virtual unique_ptr<JokerChange> getJokerChange() override; // nullptr if no change is requested

	/***
	 * Calculate the best next move for player
	 * @param move - move will be updated at the end of the function with the best move for the player.
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
	 * @param moveToCheck - the move to be scored
	 * @return scoring value for moveToCheck
	 */
	float scoreMoveOnBoard(const GameMove& moveToCheck);
	/**
	 * Return the winner of the fight if we can know it from opponentChar.
	 * Assuming ourChar is a moving piece
	 * @param ourChar - player char to check
	 * @param opponentChar - to opponent char that is known to auto player.
	 * @return the winner of the fight - current player, opponent player, TIE or NONE.
	 */
	int getWinnerOfFight(char ourChar, char opponentChar) const;
	/***
	 * Calculate the minimum distance between fromPos from all the arguments at verctorToCompare vector.
	 * @param fromPos - position for calculating the distance.
	 * @param vectorToCompare - vector to calculate minimum distance from.
	 * @return the minimum distance between fromPos to vectorToCompare
	 */
	int calculateMinDistance(const Point& fromPos, const std::vector<unique_ptr<Position>>& vectorToCompare) const;
	/***
	 * Update moving vector of player after performing a move. Replace the move source position inside the
	 * vector to move destination position.
	 * @param move - move to be updated on vector
	 */
	void updateMovingPiecesVector(const GameMove& move);
};



#endif //AT_EX2_AUTOPLAYERALGORITHM_H
