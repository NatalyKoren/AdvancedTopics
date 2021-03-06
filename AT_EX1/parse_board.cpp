#include <iostream>
#include <fstream>
#include <string.h>
#include "parse_board.h"

ParseBoard::ParseBoard(): curPlayer(0), curLine(0),curPos(0,0), curPiece('J'){
	initializePieceCount();
}

void ParseBoard::initializePieceCount() {
	pieceCount[0] = R;
	pieceCount[1] = P;
	pieceCount[2] = S;
	pieceCount[3] = B;
	pieceCount[4] = J;
	pieceCount[5] = F;
}
// gets line, checks format, calls all aiding functions
int ParseBoard::parseBoardFile (const char* filename, GameBoard& board) {
	std::string line;
	int res = SUCCESS;
	curLine = 0;
	initializePieceCount();
	std::ifstream myfile (filename);
	if (!myfile.is_open()) {
		std::cout << "Usage: Unable to open file " << filename << ": " << std::strerror(errno) << std::endl;
		return MISSING_INPUT_FILE;
	}
	curPlayer = filename[6] - '0'; // gets the int value of the char

	while (getline (myfile,line) && res <= 0 && !isLineContainWhiteSpaceOnly(line)) {     //getline returns a reference to myfile
        curLine++;
		const char* charLine = line.c_str(); //convert string to const char*
		res = checkLine(board, charLine);
	}
	myfile.close();
	if (res != 0) {
		std::cout << "Error in file format of player " << curPlayer << std::endl;
		return curLine;
	}
	if (checkPieces() != 0) {
		return curLine;
	}
	return res;
}


int ParseBoard::checkPieces() {
	int pieceCountSize = sizeof(pieceCount) / sizeof(pieceCount[0]);
	for (int i = 0; i < pieceCountSize; i++) {
		if (pieceCount[i] < 0) {
			std::cout << "Board file format error: too many pieces of same type." << std::endl;
			//std::cout << "Index: " << i << " Count: " << pieceCount[i] << std::endl;
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
	case ROCK: pieceCount[0]--;
	return 0;
	case PAPER: pieceCount[1]--;
	return 0;
	case SCISSORS: pieceCount[2]--;
	return 0;
	case BOMB: pieceCount[3]--;
	return 0;
	case JOKER: pieceCount[4]--;
	return 0;
	case FLAG: pieceCount[5]--;
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
	char jokerRep;
	char garbage;
	// check format:
	int scanned = sscanf(line, " %c %i %i %c %c", &piece, &x, &y, &jokerRep, &garbage);
	//std::cout << "line: " << curLine << " piece: " << piece << " x: " << x << " y: " << y << std::endl;
	if ((piece == 'J' && scanned != 4) || (piece != 'J' && scanned != 3)) {
		std::cout << "Error in board file: wrong format in line " << curLine << std::endl;
		return curLine;
	}

	// check char and update piece count:
	if (validatePieceChar(piece) != 0) {
		return curLine;
	}

	// check position:
	if (piece == 'J') {
		piece = tolower(jokerRep);
	}
	if (checkPos(board, piece, x-1, y-1) != 0) {
		return curLine;
	}

	return SUCCESS;
}


int ParseBoard::checkPos(GameBoard& board, const char& piece, int x, int y) {
	if (x > M || y > N || x < 0 || y < 0) {
		std::cout << "Error in board file: piece location out of bounds in line " << curLine << std::endl;
		return curPlayer;
	}
	Position pos(y,x);
	char occupied = board.getPieceAtPosition(curPlayer, pos);
	if (occupied > 0) {
		std::cout << "Error in board file: double positioning at line " << curLine << std::endl;
		return curPlayer;
	}
	curPos = pos;
	board.addPieceToGame(curPlayer, piece, pos);
	return 0;
}

bool isLineContainWhiteSpaceOnly(std::string line){
	char tmp;
	if(sscanf(line.c_str()," %c", &tmp) != 1)
		return true;
	return false;
}
