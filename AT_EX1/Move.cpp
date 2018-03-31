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
	int dummyInt;
	char newJokerRep,lineEnd, dummyChar;
	bool isJokerNewRep;

	// try to get Joker Line
	if(sscanf(line.c_str(), "%d %d %d %d J %d %d %c",
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
		if(sscanf(line.c_str(), "%d %d %d %d J %d %d %c %c",
					&dummyInt, &dummyInt,&dummyInt, &dummyInt,
					&dummyInt, &dummyInt, &dummyChar, &lineEnd) == 8)
			return ILLEGAL_LINE_FORMAT;
		if(!isupper(newJokerRep))
			return ILLEGAL_LINE_FORMAT;
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
int Move::checkMove(GameBoard* board){
	char charToMove;
	// (1) boundary tests
	// test src boundary
	if(positionBoundaryTest(src) == INDEX_OUT_OF_BOUND)
		return INDEX_OUT_OF_BOUND;
	// test dst boundary
	if(positionBoundaryTest(dst) == INDEX_OUT_OF_BOUND)
		return INDEX_OUT_OF_BOUND;
	// boundary is valid
	// (2) moving to position contain same player piece
	if(!(board->isEmpty(player,dst)))
		return ILLEGAL_MOVE;
	// (3) try to move non moving piece
	charToMove = board->getPieceAtPosition(player,src);
	if(charToMove == (char)0)
		return ILLEGAL_MOVE;
	if(charToMove == BOMB || charToMove == FLAG)
		return ILLEGAL_MOVE;
	// (4) Joker tests
	if(testForJokerValidChange(board) == ILLEGAL_MOVE)
		return ILLEGAL_MOVE;
	// Seems OK ...
	return VALID_MOVE;
}
int Move::boundaryTest(int index, bool isRowTest){
	char rowOrColBound = (isRowTest)? N:M;
	if(index < 0 || index >= rowOrColBound)
		return INDEX_OUT_OF_BOUND;
	else return VALID_INDEX;


}
int Move::positionBoundaryTest(Position& pos){
	int xPos = pos.getXposition();
	int yPos = pos.getYposition();
	if(boundaryTest(xPos, true) == INDEX_OUT_OF_BOUND)
		return INDEX_OUT_OF_BOUND;
	if(boundaryTest(yPos, false) == INDEX_OUT_OF_BOUND)
		return INDEX_OUT_OF_BOUND;
	return VALID_INDEX;
}

int Move::testForJokerValidChange(GameBoard* board){
	if(isJokerChanged){
		// joker position is empty
		if(board->isEmpty(player, jokerPos))
			return ILLEGAL_MOVE;
		// joker position doesn't contain a joker piece
		if(!islower(board->getPieceAtPosition(player,jokerPos)))
				return ILLEGAL_MOVE;
		// test if joker new char is a valid char: S,R,P,B
		if(!isJokerValidChar(newJokerChar))
			return ILLEGAL_MOVE;
	}
	return VALID_MOVE;
}
bool Move::isJokerValidChar(char newJokerChar){
	newJokerChar = toupper(newJokerChar);
	if(newJokerChar == SCISSORS || newJokerChar == ROCK ||
			newJokerChar == PAPER || newJokerChar == BOMB)
		return true;
	else return false;
}
