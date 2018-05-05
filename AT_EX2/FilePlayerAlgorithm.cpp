//
// Created by DELL on 25/04/2018.
//
#include "FilePlayerAlgorithm.h"



FilePlayerAlgorithm::FilePlayerAlgorithm(int playerNum):player(playerNum),
jokerChanged(), curPos(-1, -1){
	if (playerNum == 1) {
		movesFile = std::ifstream(MOVES1);
	} else {
		movesFile = std::ifstream(MOVES2);
	}
	initializePieceCount();
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

	}
    if (pieceCount[pieceCountSize-1] > 0) {
        std::cout << "Board file format error: flag not placed on board." << std::endl;
        return ERROR;
    }
	return SUCCESS;
}

int FilePlayerAlgorithm::checkAndUpdatePieceChar (const char& piece) {
	switch(piece) {
	case ROCK: pieceCount[0]--;
	return SUCCESS;
	case PAPER: pieceCount[1]--;
	return SUCCESS;
	case SCISSORS: pieceCount[2]--;
	return SUCCESS;
	case BOMB: pieceCount[3]--;
	return SUCCESS;
	case JOKER: pieceCount[4]--;
	return SUCCESS;
	case FLAG: pieceCount[5]--;
	return SUCCESS;
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

unique_ptr<InterfacePiecePosition> FilePlayerAlgorithm::parseBoardLine (const char* line) {
	char piece;
	int x;
	int y;
	char jokerRep;
	char garbage;
	// check format:
	int scanned = sscanf(line, " %c %i %i %c %c", &piece, &y, &x, &jokerRep, &garbage);
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
	Position pos(x-1, y-1);
	InterfacePiecePosition piecePos(pos, piece, jokerRep);
	return std::make_unique<InterfacePiecePosition>(piecePos);
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


std::string FilePlayerAlgorithm::getMovesLine() {
	std::string stringLine;
	if(getline (movesFile, stringLine)) {
		return stringLine;
	}
	return NULL;
}

void FilePlayerAlgorithm::notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights) {
	// File Player does not support this method
}

void FilePlayerAlgorithm::notifyOnOpponentMove(const Move& move){
	// File Player does not support this method
}

void FilePlayerAlgorithm::notifyFightResult(const FightInfo& fightInfo){
	// File Player does not support this method
}

unique_ptr<Move> FilePlayerAlgorithm::getMove(){
	const char* curLine = getMovesLine().c_str();
	// try to get Joker Line
	int fromX,fromY,toX,toY, jokerX,jokerY;
	int dummyInt;
	char newJokerRep,lineEnd, dummyChar;
    bool isJokerCurChange = true;

    if(curLine==NULL){
        // EOF reached - return illegal move
        fromX = -1;
        fromY = -1;
    }

	// try to get Joker Line
    else if(sscanf(curLine, "%d %d %d %d J: %d %d %c",
			&fromY, &fromX,&toY, &toX, &jokerY, &jokerX, &newJokerRep) != 7) {
		// try to get a regular line
		if(sscanf(curLine, "%d %d %d %d", &fromY, &fromX,&toY, &toX) != 4) {
			// wrong format - return an illegal move
			fromY = 0;
			fromX = 0;
		}
		// line format is correct without joker update
		// test for line length
		else if(sscanf(curLine, "%d %d %d %d %c",
				&dummyInt, &dummyInt,&dummyInt, &dummyInt, &lineEnd) == 5) {
			// wrong format - return an illegal move
			fromY = 0;
			fromX = 0;
		}
        isJokerCurChange = false;
	}
	// line format is correct with joker update
	else{
		// test for line length
		if(sscanf(curLine, "%d %d %d %d J: %d %d %c %c",
				&dummyInt, &dummyInt,&dummyInt, &dummyInt,
				&dummyInt, &dummyInt, &dummyChar, &lineEnd) == 8) {
			jokerY = 0;
			jokerX = 0;
		}
	}

	// Update move data
	Position srcPos(fromX-1, fromY-1);
	Position dstPos(toX-1, toY-1);
	GameMove curMove(player, srcPos, dstPos);

	Position jokerPos(jokerX-1, jokerY-1);
	jokerChanged.setIsJokerChanged(isJokerCurChange);
	jokerChanged.setJokerPosition(jokerPos);
	jokerChanged.setNewJokerRep(newJokerRep);
	return std::make_unique<GameMove>(curMove);
}

unique_ptr<JokerChange> FilePlayerAlgorithm::getJokerChange() {
	if (jokerChanged.getIsJokerChanged())
		return std::make_unique<GameJokerChanged>(player, jokerChanged.getIsJokerChanged(), jokerChanged.getJokerChangePosition().getX(), jokerChanged.getJokerChangePosition().getY(), jokerChanged.getJokerNewRep());
	return nullptr;
}
