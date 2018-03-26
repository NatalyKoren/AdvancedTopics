/*
 * game_board_unit_test.cpp
 *
 *  Created on: 26 במרץ 2018
 *      Author: DELL
 */

#include "GameBoardUnitTest.h"

int testFight(){
	GameBoard board;
	// TEST 1
	if(!fightTest(0,0,SCISSORS,ROCK,SECOND_PLAYER, board))
		return 1;
	// TEST 2
	if(!fightTest(3,4,SCISSORS,PAPER,FIRST_PLAYER, board))
		return 2;
	// TEST 3
	if(!fightTest(7,9,SCISSORS,SCISSORS,TIE, board))
		return 3;
	// TEST 4
	if(!fightTest(8,8,SCISSORS,FLAG,FIRST_PLAYER, board))
		return 4;
	// TEST 5
	if(!fightTest(6,5,SCISSORS,BOMB,SECOND_PLAYER, board))
		return 5;
	// TEST 6
	if(!fightTest(3,3,ROCK,PAPER,SECOND_PLAYER, board))
		return 6;
	// TEST 7
	if(!fightTest(2,2,ROCK,'s',FIRST_PLAYER, board))
		return 7;
	// TEST 8
	if(!fightTest(3,5,PAPER,'s',SECOND_PLAYER, board))
		return 8;
	// TEST 9
	if(!fightTest(3,4,BOMB,'b',TIE, board))
		return 9;
	return 0;
}
bool fightTest(int x, int y, char first, char second, int shouldWin, GameBoard& board){
	int winner;
	Position pos(x,y);
	board.addPieceToGame(FIRST_PLAYER, first, pos);
	board.addPieceToGame(SECOND_PLAYER, second, pos);
	winner = board.fight(pos);
	if(winner != shouldWin) return false;
	else return true;
}



