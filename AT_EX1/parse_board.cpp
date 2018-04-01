#include <iostream>
#include <fstream>
#include <string.h>
#include "parse_board.h"


// gets line, checks format, calls all aiding functions
int ParseBoard::parseBoardFile (std::string filename) {
	std::string line;
	int res = -1;
	std::ifstream myfile (filename);
	if (!myfile.is_open()) {
		std::cout << "Unable to open file " << filename << std::endl;
		return 1;
	}
	curPlayer = filename[6] - '0'; // gets the int value of the char
	GameBoard board;

	while (getline (myfile,line)) {     //getline returns a reference to myfile
		curLine++;
		const char* charLine = line.c_str(); //convert string to const char*
		res = checkLine(board, charLine);
	}
	myfile.close();
	if (res != 0) {
		std::cout << "Error in file format of player" << curPlayer << std::endl;
		return curPlayer;
	}
	if (checkPieces() != 0) {
		return curPlayer;
	}
	updateBoard(board, curPlayer, curPiece, curPos);
	std::cout << "res is: " << res << std::endl;
	return res;
}


int ParseBoard::checkPieces() {
	int pieceCountSize = sizeof(pieceCount) / sizeof(pieceCount[0]);
	for (int i = 0; i < pieceCountSize; i++) {
		if (pieceCount[i] < 0) {
			std::cout << "Board file format error: too many pieces of same type." << std::endl;
			std::cout << "Index: " << i << " Count: " << pieceCount[i] << std::endl;
			return curPlayer;
		}
		if (pieceCount[pieceCountSize-1] > 0) {
			std::cout << "Board file format error: flag not placed on board." << std::endl;
			return curPlayer;
		}
	}
	return 0;
}

int ParseBoard::validatePieceChar (const char& piece) {
	switch(piece) {
	case 'R': pieceCount[0]--;
	return 0;
	case 'P': pieceCount[1]--;
	return 0;
	case 'S': pieceCount[2]--;
	return 0;
	case 'B': pieceCount[3]--;
	return 0;
	case 'J': pieceCount[4]--;
	return 0;
	case 'F': pieceCount[5]--;
	return 0;
	default:
		std::cout << "Error in board file: undefined piece in line " << curLine << std::endl;
		return 1;
	}
}

int ParseBoard::checkLine (GameBoard& board, const char* line) {
	char piece;
	int x;
	int y;
	char residue;
	// check format:
	int scanned = sscanf(line, "%c %i %i %s", &piece, &x, &y, &residue);
	std::cout << "line: " << curLine << " piece: " << piece << " x: " << x << " y: " << y << std::endl;
	if ((piece == 'J' && scanned != 4) || (piece != 'J' && scanned != 3)) {
		std::cout << "Error in board file: wrong format in line " << curLine << std::endl;
		return curLine;
	}

	// check char and update piece count:
	if (validatePieceChar(piece) != 0) {
		return curLine;
	}

	// check position:
	if (checkPos(board, piece, x, y) != 0) {
		return curLine;
	}

	return 0;
}


int ParseBoard::checkPos(GameBoard& board, const char& piece, int x, int y) {
	if (x > N || y > N || x < 0 || y < 0) {
		std::cout << "Error in board file: piece location out of bounds in line " << curLine << std::endl;
		return curPlayer;
	}
	Position pos = {x, y};
	char occupied = board.getPieceAtPosition(curPlayer, pos);
	std::cout << "In checkPos: received " << occupied << std::endl;
	if (occupied > 0) {
		std::cout << "Error in board file: double positioning at line " << curLine << std::endl;
		return curPlayer;
	}
	curPos = pos;
	return 0;
}


void ParseBoard::updateBoard(GameBoard& board, int player, char piece, Position& pos) {
	board.addPieceToGame(player, piece, pos);
}

