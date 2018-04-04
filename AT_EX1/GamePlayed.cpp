/*
 * GamePlayed.cpp
 *
 *      Author: DELL
 */
#include <iostream>
#include <fstream>
#include "GamePlayed.h"

Game::Game(): curPlayer (FIRST_PLAYER), board(){}

int Game::initBoard() {
	ParseBoard parser = ParseBoard();
	int boards = parser.parseBoardFile(BOARD1, board);
	if (boards == ERROR) {
		std::cout << "Error in parsing player one's board." << std::endl;
	}
	boards = parser.parseBoardFile(BOARD2, board);
	if (boards == ERROR) {
		std::cout << "Error in parsing player two's board." << std::endl;
	}
	return SUCCESS;
}


int Game::firstTurn() {
	Position pos (0,0);
	for (int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			pos.setXposition(i);
			pos.setYposition(j);
			board.checkAndRunFight(FIRST_PLAYER, pos);
		}
	}
	return board.checkVictory();
}

int Game::playGame() {
	std::string line1;
	std::string line2;
	std::ifstream movesFile1 (MOVES1);
	if (!movesFile1.is_open()) {
		std::cout << "Unable to open file " << MOVES1 << std::endl;
		return ERROR;
	}
	std::ifstream movesFile2 (MOVES1);
	if (!movesFile2.is_open()) {
		std::cout << "Unable to open file " << MOVES2 << std::endl;
		return ERROR;
	}

	Move move;
	bool MOVES1_EMPTY = false;
	bool MOVES2_EMPTY = false;
	while (!MOVES1_EMPTY || !MOVES2_EMPTY) {
		if (!MOVES1_EMPTY) {
			getline(movesFile1,line1);
			if(!line1)
				MOVES1_EMPTY = true;
			else {
				move.setPlayer(FIRST_PLAYER);
				board.execMove(line1, move);
				winner = board.checkVictory();
				if (winner != NONE) {
					break;
				}
			}

		}

		if (!MOVES2_EMPTY) {
			getline (movesFile2,line2);
			if(!line2)
				MOVES2_EMPTY = true;
			else {
				move.setPlayer(SECOND_PLAYER);
				board.execMove(line2, move);
				winner = board.checkVictory();
				if (winner != NONE) {
					break;
				}
			}

		}

	}
	movesFile1.close();
	movesFile2.close();
}


