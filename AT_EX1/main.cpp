/*
 * main.cpp
 *
 *  Created on: 27 במרץ 2018
 *      Author: DELL
 */

#include "GameBoardUnitTest.h"
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
	return 0;
}
