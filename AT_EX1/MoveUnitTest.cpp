/*
 * MoveUnitTest.cpp
 *
 *  Created on: 27 במרץ 2018
 *      Author: DELL
 */
#include "MoveUnitTest.h"

int testParseLine(){
	bool result;
	Move move(FIRST_PLAYER);
	std:: string line = "<1><2><3><4>J<5><6><S>";
	result = move.parseLine(line);
	move.printMove();
	if(!result)
		return 1;
	std:: string line2 =  "<10><9><8><7>";
	result = move.parseLine(line2);
	move.printMove();
	if(!result)
		return 2;
	return 0;
}
