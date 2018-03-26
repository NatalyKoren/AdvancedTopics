/*
 * Move.h
 *
 *  Created on: 26 במרץ 2018
 *      Author: DELL
 */

#ifndef MOVE_H_
#define MOVE_H_

#include "Position.h"
#include <iostream>
#include "GameBoard.h"


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
	//int checkMove(GameBoard*); - compilation error
	//void updateMove(GameBoard&, );
	Position& getJokerPos(){ return jokerPos; }
	char getJokerNewChar()const{ return newJokerChar; }
	Position& getDst(){ return dst; }
	Position& getSrc(){ return src; }
	bool isJokerUpdated(){ return isJokerChanged; }

};
#endif /* MOVE_H_ */
