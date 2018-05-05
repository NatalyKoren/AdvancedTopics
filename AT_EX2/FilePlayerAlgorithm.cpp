//
// Created by DELL on 25/04/2018.
//
#include "FilePlayerAlgorithm.h"

FilePlayerAlgorithm::FilePlayerAlgorithm(int playerNum) {
	player = playerNum;
	if (playerNum == 1) {
		movesFile = std::ifstream(MOVES1);
	} else {
		movesFile = std::ifstream(MOVES2);
	}
	initializePieceCount();
	curPos = Position(-1, -1);
}

void FilePlayerAlgorithm::initializePieceCount() {
	pieceCount[0] = R;
	pieceCount[1] = P;
	pieceCount[2] = S;
	pieceCount[3] = B;
	pieceCount[4] = J;
	pieceCount[5] = F;
}

int FilePlayerAlgorithm::checkPieces() {
	int pieceCountSize = sizeof(pieceCount) / sizeof(pieceCount[0]);
	for (int i = 0; i < pieceCountSize; i++) {
		if (pieceCount[i] < 0) {
			std::cout << "Board file format error: too many pieces of same type." << std::endl;
			//std::cout << "Index: " << i << " Count: " << pieceCount[i] << std::endl;
			return ERROR;
		}
		if (pieceCount[pieceCountSize-1] > 0) {
			std::cout << "Board file format error: flag not placed on board." << std::endl;
			return ERROR;
		}
	}
	return SUCCESS;
}

int FilePlayerAlgorithm::checkAndUpdatePieceChar (const char& piece) {
	switch(piece) {
	case ROCK: pieceCount[0]--;
	return checkPieces();
	case PAPER: pieceCount[1]--;
	return checkPieces();
	case SCISSORS: pieceCount[2]--;
	return checkPieces();
	case BOMB: pieceCount[3]--;
	return checkPieces();
	case JOKER: pieceCount[4]--;
	return checkPieces();
	case FLAG: pieceCount[5]--;
	return checkPieces();
	default:
		std::cout << "Error in board file: undefined piece " << std::endl;
		return ERROR;
	}
}

int FilePlayerAlgorithm::checkPos(int x, int y) {
	if (x > M || y > N || x < 0 || y < 0) {
		std::cout << "Error in board file: piece location out of bounds " << std::endl;
		return ERROR;
	}
	return SUCCESS;
}

InterfacePiecePosition FilePlayerAlgorithm::parseBoardLine (const char* line) {
	InterfacePiecePosition piecePos;
	char piece;
	int x;
	int y;
	char jokerRep;
	char garbage;
	// check format:
	int scanned = sscanf(line, " %c %i %i %c %c", &piece, &x, &y, &jokerRep, &garbage);
	//std::cout << "line: " << curLine << " piece: " << piece << " x: " << x << " y: " << y << std::endl;
	if ((piece == 'J' && scanned != 4) || (piece != 'J' && scanned != 3)) {
		std::cout << "Error in board file: wrong format " << std::endl;
		x = -1;
		y = -1;
	}

	// check char and update piece count:
	if (checkAndUpdatePieceChar(piece) == ERROR) {
		x = -1;
		y = -1;
	}

	// check position:
	if (piece == 'J') {
		piece = tolower(jokerRep);
	}
	if (checkPos(x-1, y-1) == ERROR) {
		x = -1;
		y = -1;
	}

	return new InterfacePiecePosition(new Position(x, y), piece, jokerRep);
}

bool FilePlayerAlgorithm::isLineContainWhiteSpaceOnly(std::string line){
	char tmp;
	if(sscanf(line.c_str()," %c", &tmp) != 1)
		return true;
	return false;
}


void FilePlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill){
	std::ifstream boardFile;
	if (player == FIRST_PLAYER) {
		boardFile.open(BOARD1);
	} else {
		boardFile.open(BOARD2);
	}
	if (!boardFile.is_open()) {
		std::cout << "Unable to open player " << player <<"'s board file: " << std::strerror(errno) << std::endl;
	}
	std::string line;
	int res = SUCCESS;
	while (getline (boardFile,line) && res <= 0 && !isLineContainWhiteSpaceOnly(line)) {     //getline returns a reference to myfile
		const char* charLine = line.c_str(); //convert string to const char*
		vectorToFill.push_back(parseBoardLine(charLine));
	}
	boardFile.close();
}

unique_ptr<Move> FilePlayerAlgorithm::parseMoveLine() {

}

void FilePlayerAlgorithm::notifyOnOpponentMove(const Move& move){
	// File Player does not support this method
}

void FilePlayerAlgorithm::notifyFightResult(const FightInfo& fightInfo){
	// File Player does not support this method
}

unique_ptr<Move> FilePlayerAlgorithm::getMove(){
	return std::make_unique<GameMove>(FIRST_PLAYER);
}

unique_ptr<JokerChange> FilePlayerAlgorithm::getJokerChange(){
	return std::make_unique<GameJokerChanged>();
}
