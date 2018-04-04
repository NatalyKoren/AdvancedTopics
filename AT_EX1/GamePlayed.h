/*
 * GamePlayed.h
 *
 *      Author: DELL
 */

#ifndef GAMEPLAYED_H_
#define GAMEPLAYED_H_
#include <iostream>
#include <fstream>
#include "Definitions.h"
#include "GameBoard.h"
#include "Move.h"
#include "parse_board.h"

class Game {
	int curPlayer;
	GameBoard board;


public:

	/*
	 * constructor
	 */
	Game();

	/*
	 * calls the board file parser
	 * @return value: 0 if ok,
	 */
	int initBoard();

	/*
	 * Called after parsing the board files
	 * Checks if there's a fight at this stage and if so, runs it
	 * @return value: winner (player# or TIE) or NONE if game continues
	 */
	int firstTurn();

	/*
	 * after boards are parsed, parses move files
	 * runs the game
	 * returns SUCCESS or ERROR
	 */
	int playGame();

	/*
	 * Called by main
	 * calls all other game methods
	 * return value: 0 if ok, 1 otherwise
	 */
	int startGame();
};

#endif /* GAMEPLAYED_H_ */
