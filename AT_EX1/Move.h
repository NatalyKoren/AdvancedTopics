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


class Move{
	bool isJokerChanged;
	char newJokerChar;
	int player;
	Position src;
	Position dst;
public:
	Move(int player);
	int parseLine(std::string line);
	bool isValidMove(GameBoard&);
	void updateMoveAfterFight();
	void setMove(GameBoard&);

};
#endif /* MOVE_H_ */
