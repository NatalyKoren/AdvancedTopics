/*
 * game_board_unit_test.h
 *
 *  Created on: 26 ���� 2018
 *      Author: DELL
 */

#ifndef GAMEBOARDUNITTEST_H_
#define GAMEBOARDUNITTEST_H_
#include "GameBoard.h"

int testFight();
bool fightTest(int x, int y, char first, char second, int shouldWin, GameBoard& board);

int testIsFight();
bool isFightTest(int x, int y, char first, char second, GameBoard& board);

int testVictory();

int testUpdateAfterMove(); // also tests updateAfterLoseFight
void createBoardAfterMove(Position& src, Position& dst, Position& jokerPos, char addToSrc,
		bool isJokerUpdated, char newJoker, char oldJoker, GameBoard& board, Move& move);
void createMove(Move& move, Position src, Position dst, bool isJokerUpdated,
		Position jokerPos, char jokerChar);
bool compareBoardExceptPos(Position& pos, GameBoard& board);


#endif /* GAMEBOARDUNITTEST_H_ */
