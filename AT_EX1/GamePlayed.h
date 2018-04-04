/*
 * GamePlayed.h
 *
 *      Author: DELL
 */

#ifndef GAMEPLAYED_H_
#define GAMEPLAYED_H_
#include <iostream>
#include <fstream>
#include "Position.h"
#include "Definitions.h"
#include "GameBoard.h"
#include "Move.h"

class Game {
	int curPlayer;
	GameBoard board;

public:

	/*
	 * @param: the game board object
	 * Called after parsing the board files
	 * Checks if there's a fight at this stage and if so, runs it
	 * @return value: 0 if tie, player# otherwise
	 */
	int firstTurn(GameBoard board);

	/*
	 * @param: filename
	 * calls parseBoardFile and firstTurn
	 */
	int startGame(std::string fileName);
};

#endif /* GAMEPLAYED_H_ */
