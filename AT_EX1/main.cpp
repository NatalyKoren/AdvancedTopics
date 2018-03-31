/*
 * main.cpp
 *
 *      Author: DELL
 */

#include "GameBoardUnitTest.h"
#include "MoveUnitTest.h"
#include <iostream>
int main(){
	// ~~~ Fight ~~~
	int result = testFight();
	if(result == 0)
		std::cout << "Passed test fight" << std::endl;
	else
		std::cout << "test fight failed test number: " << result << std::endl;
	// ~~~ Is Fight ~~~
	result = testIsFight();
	if(result == 0)
		std::cout << "Passed test isFight" << std::endl;
	else
		std::cout << "test isFight failed test number: " << result << std::endl;
	// ~~~ Update Board After Move ~~~
	result = testUpdateAfterMove();
	if(result == 0)
		std::cout << "Passed test update after move" << std::endl;
	else
		std::cout << "test update after move failed test number: " << result << std::endl;
	// ~~~ Victory ~~~
	result = testVictory();
	if(result == 0)
		std::cout << "Passed test victory" << std::endl;
	else
		std::cout << "test victory failed test number: " << result << std::endl;

	// ~~~~ Move
	result = testParseLine();
	if(result == 0)
		std::cout << "Passed test parse move " << std::endl;
	else
		std::cout << "test parse move failed test number: " << result << std::endl;

	result = testpositionBoundary();
	if(result == 0)
		std::cout << "Passed test position boundary " << std::endl;
	else
		std::cout << "test position boundary failed test number: " << result << std::endl;
	result = testJokerValidChange();
	if(result == 0)
		std::cout << "Passed test joker valid change " << std::endl;
	else
		std::cout << "test joker valid change failed test number: " << result << std::endl;
	result = testValidMove();
	if(result == 0)
		std::cout << "Passed test valid move " << std::endl;
	else
		std::cout << "test valid move failed test number: " << result << std::endl;
	return 0;
}
