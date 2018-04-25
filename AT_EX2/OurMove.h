/*
 * OurMove.h
 *
 *  Created on: 25 Apr 2018
 *      Author: admin
 */

#ifndef OURMOVE_H_
#define OURMOVE_H_

#include "Point.h"
#include <iostream>
#include <cstdio>
#include "Definitions.h"

class Move{
	bool isJokerChanged;
	Position jokerPos;
	char newJokerChar;
	int player;
	Position from;
	Position to;
public:
	Move(int player);
	/***
	 * Parse a line from moves file.
	 * @param line - line from moves file
	 * @return ILLEGAL FORMAT if line format is incorrect or joker char is not upper case char.
	 * Otherwise return VALID_LINE_FORMAT and update move fields with line data.
	 */
	bool parseLine(std::string line);
	/***
	 * Test if pos is a valid position on board. Assuming pos contain 0-based indexes.
	 * @param pos - position to be tested.
	 * @return INDEX_OUT_OF_BOUND if position is not a valid position on board (out of bound).
	 * Otherwise VALID_INDEX is returned.
	 */
	int positionBoundaryTest (Position& pos) const;
	/***
	 * Test if index is in row boundary or column boundary.
	 * @param index - index to be tested. Assumed to be 0-based index.
	 * @param isRowTest - true if index is a row index and false if index is a column index.
	 * @return INDEX_OUT_OF_BOUND if index is out of bound. Otherwise VALID_INDEX is returned.
	 */
	int boundaryTest (int index, bool isRowTest) const;
	/***
	 * Test is new joker representation is a valid representation for joker.
	 * @param newJokerRep - char to be tested.
	 * @return true if newJokerChar is a valid joker representation and false otherwise.
	 * valid representation is: BOMB, SCISSORS, ROCK, PAPER.
	 */
	bool isJokerValidChar (char newJokerRep) const;
	// Getters
	Position& getJokerPos(){ return jokerPos; }
	char getJokerNewChar()const{ return newJokerChar; }
	int getPlayer()const{ return player; }
	Position& getDst(){ return dst; }
	Position& getSrc(){ return src; }
	bool getIsJokerUpdated()const{ return isJokerChanged; }
	// Setters
	void setSrcPosition(Position& pos){src = pos;}
	void setDstPosition(Position& pos){dst = pos; }
	void setJokerPosition(Position& pos){jokerPos = pos;}
	void setJokerChar(char ch){newJokerChar = ch;}
	void setJokerUpdated(bool isUpdated){isJokerChanged = isUpdated;}
	void setPlayer(int curPlayer){player = curPlayer;}
	// For tests and debugging
	void printMove() const;


};

#endif /* OURMOVE_H_ */
