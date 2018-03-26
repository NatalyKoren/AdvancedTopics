/*
 * game_board.h
 *
 *  Created on: 26 במרץ 2018
 *      Author: DELL
 */

#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_
#include "Move.h"
#include "Position.h"
#include "Definitions.h"

class GameBoard{
	char firstPlayerBoard[N][M] = { {0} };
	char secondPlayerBoard[N][M] = { {0} };
	int pieceNumFirstPlayer;
	int pieceNumSecondPlayer;
	bool isFirstFlagEaten;
	bool isSecondFlagEaten;
public:
	// --- Constructor ---
	GameBoard(int firstNum, int secondNum);
	// --- Game rules related ---
	int fight(Position& pos);
	bool isFight(int playerToCheck, Position& pos);
	int checkVictory(); // return 0 - tie, 1- first player wins, 2 - second wins, -1 - no body wins.
	// --- Getters and Setters ---
	void updateBoardAfterMove(int player, Move& move);
	char getPieceAtPosition(int player, Position& pos);
	void setPieceAtPosition(int player, char piece, Position& pos);
	int getOpponent(int player){
		return (player == FIRST_PLAYER)? FIRST_PLAYER:SECOND_PLAYER;
	}
	void decreasePieceNum(int player, int num);
	void updateAfterLooseFight(int player, Position& pos);
	void setPlayerFlageEaten(int player);


};


#endif /* GAME_BOARD_H_ */
