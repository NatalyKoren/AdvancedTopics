/*
 * MoveUnitTest.cpp
 *
 *      Author: DELL
 */
#include "MoveUnitTest.h"

int testParseLine(){
	bool result;
	Move move(FIRST_PLAYER);
	std:: string line = "1 2 3 4 J: 5 6 S \n";
	result = move.parseLine(line);
	move.printMove();
	if(!result)
		return 1;
	std:: string line2 =  " 10 9	8 7 ";
	result = move.parseLine(line2);
	move.printMove();
	if(!result)
		return 2;
	std:: string line3 =  "1 2 3 4 5 6 7";
	result = move.parseLine(line3);
	if(result)
		return 3;
	std:: string line4 =  "10 9 8 7 6";
	result = move.parseLine(line4);
	if(result)
		return 4;
	return 0;
}
int testpositionBoundary(){
	Position pos(0,0);
	Move move(FIRST_PLAYER);
	if(move.positionBoundaryTest(pos) != VALID_INDEX)
		return 1;
	pos.setXposition(1);
	pos.setYposition(-1);
	if(move.positionBoundaryTest(pos) == VALID_INDEX)
		return 2;
	pos.setXposition(10);
	pos.setYposition(5);
	if(move.positionBoundaryTest(pos) == VALID_INDEX)
		return 3;
	pos.setXposition(9);
	pos.setYposition(9);
	if(move.positionBoundaryTest(pos) != VALID_INDEX)
		return 4;
	return 0;

}





