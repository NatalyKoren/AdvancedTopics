/*
 * game_board.h
 *
 *  Created on: 26 במרץ 2018
 *      Author: DELL
 */

#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_
#include "Move.h"
#define ROWS_NUM      (10)
#define COLS_NUM      (10)
#define PIECE_COUNT   (13)
#define FIRST_PLAYER  (1)
#define SECOND_PLAYER (2)
# define TIE          (0)

class GameBoard{
	char firstPlayerBoard[ROWS_NUM][COLS_NUM] = {0};
	char secondPlayerBoard[ROWS_NUM][COLS_NUM] = {0};
	int pieceNumFirstPlayer;
	int pieceNumSecondPlayer;
	bool isFirstFlagEaten;
	bool isSecondFlagEaten;

	GameBoard();
	bool isValidMove(int player, Move& move);
	int checkVictory(int player);
	void setMove(Move& move);


};


#endif /* GAME_BOARD_H_ */
