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
	char firstPlayerBoard[N][M] = {0};
	char secondPlayerBoard[N][M] = {0};
	int pieceNumFirstPlayer;
	int pieceNumSecondPlayer;
	bool isFirstFlagEaten;
	bool isSecondFlagEaten;
public:
	// --- Constructor ---
	GameBoard();
	// --- Game rules related ---
	int fight(Position& pos);
	bool isFight(Position& pos);
	int checkVictory(int player);
	// --- Getters and Setters ---
	void setMove(int player, Position& src,Position& dst);
	char getPieceAtPosition(int player, Position& pos);
	void setPieceAtPosition(int player, char piece, Position& pos);

};


#endif /* GAME_BOARD_H_ */
