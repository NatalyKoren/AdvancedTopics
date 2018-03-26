/*
 * game_board_unit_test.h
 *
 *  Created on: 26 במרץ 2018
 *      Author: DELL
 */

#ifndef GAMEBOARDUNITTEST_H_
#define GAMEBOARDUNITTEST_H_
#include "GameBoard.h"

int testFight();
bool fightTest(int x, int y, char first, char second, int shouldWin, GameBoard& board);

int testIsFight();
int testVictory();
int testUpdateAfterMove();
int testUpdateAfterLose();

#endif /* GAMEBOARDUNITTEST_H_ */
