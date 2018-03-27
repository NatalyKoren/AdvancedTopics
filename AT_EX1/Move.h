/*
 * Move.h
 *
 *  Created on: 26 ���� 2018
 *      Author: DELL
 */

#ifndef MOVE_H_
#define MOVE_H_

#include "Position.h"
#include <iostream>
#include "GameBoard.h"
class GameBoard;

class Move{
	bool isJokerChanged;
	Position jokerPos;
	char newJokerChar;
	int player;
	Position src;
	Position dst;
public:
	Move(int player);
	int parseLine(std::string line);
	int checkMove(GameBoard*);
	void updateMove(GameBoard*);
	Position& getJokerPos(){ return jokerPos; }
	char getJokerNewChar()const{ return newJokerChar; }
	int getPlayer(){ return player; }
	Position& getDst(){ return dst; }
	Position& getSrc(){ return src; }
	bool isJokerUpdated(){ return isJokerChanged; }
	// Setters - for tests
	void setSrcPosition(Position& pos){src = pos;}
	void setDstPosition(Position& pos){dst = pos; }
	void setJokerPosition(Position& pos){jokerPos = pos;}
	void setJokerChar(char ch){newJokerChar = ch;}
	void setJokerUpdated(bool isUpdated){isJokerChanged = isUpdated;}

};
#endif /* MOVE_H_ */
