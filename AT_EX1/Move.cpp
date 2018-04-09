/*
 * Move.cpp
 *
 *      Author: DELL
 */
#include "Move.h"

Move::Move(int player):isJokerChanged(false), jokerPos(0,0),
	newJokerChar((char)0), player(player),src(0,0), dst(0,0) {}

bool Move::parseLine(std::string line){
	// try to get Joker Line
	int fromX,fromY,toX,toY, jokerX,jokerY;
	int dummyInt;
	char newJokerRep,lineEnd, dummyChar;
	bool isJokerNewRep;

	// try to get Joker Line
	if(sscanf(line.c_str(), "%d %d %d %d J: %d %d %c",
			&fromX, &fromY,&toX, &toY, &jokerX, &jokerY, &newJokerRep) != 7){
		// try to get a regular line
		if(sscanf(line.c_str(), "%d %d %d %d",
				&fromX, &fromY,&toX, &toY) != 4){
			// wrong format :(
			return ILLEGAL_LINE_FORMAT;
		}
		// line format is correct without joker update
		// test for line length
		if(sscanf(line.c_str(), "%d %d %d %d %c",
						&dummyInt, &dummyInt,&dummyInt, &dummyInt, &lineEnd) == 5)
			return ILLEGAL_LINE_FORMAT;
		isJokerNewRep = false;
		jokerX = 0;
		jokerY = 0;
		newJokerRep = (char) 0;
	}
	// line format is correct with joker update
	else{
		// test for line length
		if(sscanf(line.c_str(), "%d %d %d %d J: %d %d %c %c",
					&dummyInt, &dummyInt,&dummyInt, &dummyInt,
					&dummyInt, &dummyInt, &dummyChar, &lineEnd) == 8)
			return ILLEGAL_LINE_FORMAT;
		if(!isupper(newJokerRep)){
			std::cout << "Illegal new representation for joker: " << newJokerRep << std::endl;
			return ILLEGAL_LINE_FORMAT;
		}

		isJokerNewRep = true;
	}

	// Update move data
	src.setXposition(fromX-1);
	src.setYposition(fromY-1);
	dst.setXposition(toX-1);
	dst.setYposition(toY-1);
	isJokerChanged = isJokerNewRep;
	newJokerChar = tolower(newJokerRep);
	jokerPos.setXposition(jokerX-1);
	jokerPos.setYposition(jokerY-1);

	return VALID_LINE_FORMAT;
}

void Move::printMove() const{
	std::cout << "Source position: " << src.getXposition() << "," << src.getYposition()  << std::endl;
	std::cout << "Destination position: " << dst.getXposition() << "," << dst.getYposition()  << std::endl;
	std::cout << "Player: " << player << std::endl;
	std::cout << "Need to Update Joker? : " << isJokerChanged << std::endl;
	if(isJokerChanged){
		std::cout << "Joker position: " << jokerPos.getXposition() << "," << jokerPos.getYposition()  << std::endl;
		std::cout << "Joker new char: " << newJokerChar << std::endl;
	}

}

int Move::boundaryTest(int index, bool isRowTest) const{
	char rowOrColBound = (isRowTest)? N:M;
	if(index < 0 || index >= rowOrColBound)
		return INDEX_OUT_OF_BOUND;
	else return VALID_INDEX;


}
int Move::positionBoundaryTest(Position& pos) const{
	int xPos = pos.getXposition();
	int yPos = pos.getYposition();
	if(boundaryTest(xPos, true) == INDEX_OUT_OF_BOUND)
		return INDEX_OUT_OF_BOUND;
	if(boundaryTest(yPos, false) == INDEX_OUT_OF_BOUND)
		return INDEX_OUT_OF_BOUND;
	return VALID_INDEX;
}


bool Move::isJokerValidChar(char newJokerChar) const{
	newJokerChar = toupper(newJokerChar);
	if(newJokerChar == SCISSORS || newJokerChar == ROCK ||
			newJokerChar == PAPER || newJokerChar == BOMB)
		return true;
	else return false;
}
