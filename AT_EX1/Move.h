/*
 * Move.h
 *
 *      Author: DELL
 */

#ifndef MOVE_H_
#define MOVE_H_

#include "Position.h"
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include "Definitions.h"

class Move{
	bool isJokerChanged;
	Position jokerPos;
	char newJokerChar;
	int player;
	Position src;
	Position dst;
public:
	Move(int player);
	bool parseLine(std::string line);
	// 0-based test
	int positionBoundaryTest(Position& pos);
	int boundaryTest(int index, bool isRowTest);
	bool isJokerValidChar(char newJokerChar);
	// Getters
	Position& getJokerPos(){ return jokerPos; }
	char getJokerNewChar()const{ return newJokerChar; }
	int getPlayer()const{ return player; }
	Position& getDst(){ return dst; }
	Position& getSrc(){ return src; }
	bool getIsJokerUpdated()const{ return isJokerChanged; }
	// Setters - for tests
	void setSrcPosition(Position& pos){src = pos;}
	void setDstPosition(Position& pos){dst = pos; }
	void setJokerPosition(Position& pos){jokerPos = pos;}
	void setJokerChar(char ch){newJokerChar = ch;}
	void setJokerUpdated(bool isUpdated){isJokerChanged = isUpdated;}
	void setPlayer(int curPlayer){player = curPlayer;}
	// For tests and debugging
	void printMove();


};
#endif /* MOVE_H_ */
