#ifndef PARSEBOARD_H_
#define PARSEBOARD_H_

#include <iostream>
#include <fstream>
#include <cstring>
#include <cerrno>
#include <cctype>
#include "Position.h"
#include "Definitions.h"
#include "GameBoard.h"


class ParseBoard {
	int pieceCount[6];
	int curPlayer;
	int curLine;
	Position curPos;
	char curPiece;


public:
    ParseBoard();
	// @param: board file, board object
	// gets line, checks format, calls all aiding functions
	// @return value: 0 if correct, line# if error
	int parseBoardFile (const char* filename, GameBoard& board);

	// @param: game board, line from file
	// checks the syntax (length, types etc.)
	// @return value: 0 if correct, line# if error
	int checkLine (GameBoard& board, const char* line);

	//@param: piece char parsed from line
	// updates pieceCount, an array that counts the pieces
	// @return value: 0 if piece is ok, 1 if not one of the game's pieces
	int validatePieceChar (const char& piece);


	// verifies that the number of each piece is legal
	// @return value: 0 if ok, player# otherwise
	int checkPieces();

	/*
	 * @param: the game board, parsed piece and (x,y) from file
	 *  verifies that the position specified is within index and free
	 *  if so - updates the board
	 *  @return value: 0 if ok, player# otherwise
	 */
	int checkPos(GameBoard& board, const char& piece, int x, int y);

	void initializePieceCount();
};

#endif /* PARSEBOARD_H_ */
