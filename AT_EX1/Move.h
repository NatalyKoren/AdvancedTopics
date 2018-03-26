/*
 * Move.h
 *
 *  Created on: 26 במרץ 2018
 *      Author: DELL
 */

#ifndef MOVE_H_
#define MOVE_H_

#include "game_board.h"
#include "Position.h"
#include <iostream>


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
	Position& getDst()const;
	Position& getSrc()const;
	bool isJokerUpdated(){ return isJokerChanged; }
	//void updateMove(GameBoard&, );
	Position& getJokerPos()const{ return jokerPos; }
	char getJokerNewChar()const{ return newJokerChar; }

};
#endif /* MOVE_H_ */
