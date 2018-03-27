/*
 * Move.cpp
 *
 *  Created on: 26 במרץ 2018
 *      Author: DELL
 */
#include "Move.h"

Move::Move(int player):isJokerChanged(false), jokerPos(0,0),
	newJokerChar((char)0), player(player),src(0,0), dst(0,0) {}

bool Move::parseLine(std::string line){
	// try to get Joker Line
	int fromX,fromY,toX,toY, jokerX,jokerY;
	char newJokerRep;
	bool isJokerNewRep;
	// try to get Joker Line
	if(sscanf(line.c_str(), "<%d><%d><%d><%d>J<%d><%d><%c>",
			&fromX, &fromY,&toX, &toY, &jokerX, &jokerY, &newJokerRep) != 7){
		// try to get a regular line
		if(sscanf(line.c_str(), "<%d><%d><%d><%d>",
				&fromX, &fromY,&toX, &toY) != 4){
			// wrong format :(
			return false;
		}
		// line format is correct without joker update
		isJokerNewRep = false;
		jokerX = -1;
		jokerY = -1;
		newJokerRep = (char) 0;
	}
	// line format is correct with joker update
	else isJokerNewRep = true;

	// Update move data
	src.setXposition(fromX);
	src.setYposition(fromY);
	dst.setXposition(toX);
	dst.setYposition(toY);
	isJokerChanged = isJokerNewRep;
	newJokerChar = tolower(newJokerRep);
	jokerPos.setXposition(jokerX);
	jokerPos.setYposition(jokerY);

	return true;
}

void Move::printMove(){
	std::cout << "Source position: " << src.getXposition() << "," << src.getYposition()  << std::endl;
	std::cout << "Destination position: " << dst.getXposition() << "," << dst.getYposition()  << std::endl;
	std::cout << "Player: " << player << std::endl;
	std::cout << "Need to Update Joker? : " << isJokerChanged << std::endl;
	if(isJokerChanged){
		std::cout << "Joker position: " << jokerPos.getXposition() << "," << jokerPos.getYposition()  << std::endl;
		std::cout << "Joker new char: " << newJokerChar << std::endl;
	}

}
