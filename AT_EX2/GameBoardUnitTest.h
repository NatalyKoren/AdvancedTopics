//
// Created by DELL on 29/04/2018.
//

#ifndef AT_EX2_GAMEBOARDUNITTEST_H
#define AT_EX2_GAMEBOARDUNITTEST_H
#include "GameBoard.h"
#include <iostream>
int testFight();
bool fightTest(int x, int y, char first, char second, int shouldWin, GameBoard& board);

int testIsFight();
bool isFightTest(int x, int y, char first, char second, GameBoard& board);

int testVictory();

int testUpdateAfterMove(); // also tests updateAfterLoseFight
int createBoardAfterMove(Position& src, Position& dst, Position& jokerPos, char addToSrc,
                         bool isJokerUpdated, char newJoker, char oldJoker, GameBoard& board, GameMove& move,
                            GameFightInfo& fightInfo);
void createMove(GameMove& move, Position src, Position dst, bool isJokerUpdated,
                Position jokerPos, char jokerChar);
bool compareBoardExceptPos(Position& pos, GameBoard& board);
int testJokerValidChange();
int testValidMove();
int testExecMove();

int masterTestGameBoard();
#endif //AT_EX2_GAMEBOARDUNITTEST_H
