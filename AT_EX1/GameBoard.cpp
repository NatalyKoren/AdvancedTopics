/*
 * game_board.cpp
 *
 *      Author: DELL
 */

#include "GameBoard.h"

GameBoard::GameBoard(): firstPlayerBoard{}, secondPlayerBoard{}, firstPlayerPieces(),secondPlayerPieces(),
winner(NONE), reason (0){}

char GameBoard::getPieceAtPosition(int player, Position& pos) const{
	// pos is a legal position
	if(player == FIRST_PLAYER){
		return firstPlayerBoard[pos.getXposition()][pos.getYposition()];
	}
	return secondPlayerBoard[pos.getXposition()][pos.getYposition()];
}

void GameBoard::setPieceAtPosition(int player, char piece, Position& pos){
	if(player == FIRST_PLAYER){
		firstPlayerBoard[pos.getXposition()][pos.getYposition()] = piece;
	}
	else{
		secondPlayerBoard[pos.getXposition()][pos.getYposition()] = piece;
	}
}

bool GameBoard::isFight(int playerToCheck, Position& pos) const{
	int x = pos.getXposition();
	int y = pos.getYposition();
	if(playerToCheck == FIRST_PLAYER)
		return (firstPlayerBoard[x][y] != (char) 0);
	else return (secondPlayerBoard[x][y] != (char) 0);
}


bool GameBoard::checkAndRunFight(int player, Position& dstPos) {
	int opponent = getOpponent(player);
	int winner;
	if(isFight(opponent, dstPos)){
		//Fight
		winner = fight(dstPos);
		// update opponent board
		if(winner == player)
			updateAfterLoseFight(opponent,dstPos);
		// the current player lose...
		else if(winner == opponent)
			updateAfterLoseFight(player,dstPos);
		else {
			// it is a tie - need to remove both players
			updateAfterLoseFight(player,dstPos);
			updateAfterLoseFight(opponent,dstPos);
		}
		return true;
	}
	return false;
}

void GameBoard::updateBoardAfterMove(Move& move){
	// assuming it is a vatestForJokerValidChangelid move
	int player = move.getPlayer();
	Position srcPos = move.getSrc(); // TODO check if it should be Position&
	Position dstPos = move.getDst();
	// get char to be updated.
	char charToUpdate = getPieceAtPosition(player, srcPos);
	// update player char
	setPieceAtPosition(player,charToUpdate, dstPos);

	// No fight- need only to update player's dest position
	if (!checkAndRunFight(player, dstPos)) {
		setPieceAtPosition(player,charToUpdate, dstPos);
	}
	// set source position to zero
	setPieceAtPosition(player,0, srcPos);

}

int GameBoard::updateJoker(Move& move) {
	// Joker tests
	if(testForJokerValidChange(move) == ILLEGAL_MOVE) {
		reason = BAD_MOVE;
		return ERROR;
	}
	int player = move.getPlayer();
	if(move.getIsJokerUpdated()) {
		char previousPiece = getPieceAtPosition(player, move.getJokerPos());
		setPieceAtPosition(player, move.getJokerNewChar(), move.getJokerPos());
		if(player == FIRST_PLAYER)
			firstPlayerPieces.updateJokerMovingCount(previousPiece, move.getJokerNewChar());
		else
			secondPlayerPieces.updateJokerMovingCount(previousPiece, move.getJokerNewChar());
	}
	return SUCCESS;
}


int GameBoard::fight(Position& pos) const{
	int firstPlayerPiece = getPieceAtPosition(FIRST_PLAYER,pos);
	int secondPlayerPiece = getPieceAtPosition(SECOND_PLAYER,pos);
	//For joker cases
	firstPlayerPiece = toupper(firstPlayerPiece);
	secondPlayerPiece = toupper(secondPlayerPiece);
	// Tie
	if(firstPlayerPiece == secondPlayerPiece) return TIE;

	switch(firstPlayerPiece){
	case BOMB:
		return TIE; // Need to remove bomb from board
	case FLAG:
		if(secondPlayerPiece == BOMB) return TIE;
		return SECOND_PLAYER;
	case ROCK:
		if(secondPlayerPiece == SCISSORS || secondPlayerPiece == FLAG) return FIRST_PLAYER;
		else if(secondPlayerPiece == BOMB) return TIE;
		else return SECOND_PLAYER;
	case PAPER:
		if(secondPlayerPiece == ROCK || secondPlayerPiece == FLAG) return FIRST_PLAYER;
		else if(secondPlayerPiece == BOMB) return TIE;
		else return SECOND_PLAYER;
	case SCISSORS:
		if(secondPlayerPiece == PAPER || secondPlayerPiece == FLAG) return FIRST_PLAYER;
		else if(secondPlayerPiece == BOMB) return TIE;
		else return SECOND_PLAYER;
	default:
		return NONE;

	}

}
void GameBoard::increasePieceNum(int player, char piece, int num){
	if(player == FIRST_PLAYER) firstPlayerPieces.incrementPieceNum(piece, num);
	else secondPlayerPieces.incrementPieceNum(piece, num);
}

void GameBoard::updateAfterLoseFight(int player, Position& pos){
	char charToRemove = getPieceAtPosition(player, pos);
	setPieceAtPosition(player,(char)0, pos);
	increasePieceNum(player,charToRemove,-1);
}

int GameBoard::checkVictory(int curPlayer){
//	int curPlayerMovingNum = 0;
	int opponentMovingNum = 0;
	if (curPlayer == FIRST_PLAYER) {
//		curPlayerMovingNum = firstPlayerPieces.getMovePiecesNum();
		opponentMovingNum = secondPlayerPieces.getMovePiecesNum();
	} else {
//		curPlayerMovingNum = secondPlayerPieces.getMovePiecesNum();
		opponentMovingNum = firstPlayerPieces.getMovePiecesNum();
	}
	//	int firstPlayerMovinNum = firstPlayerPieces.getMovePiecesNum();
	//	int secondPlayerMovinNum = secondPlayerPieces.getMovePiecesNum();
	if(firstPlayerPieces.getFlagNum() == 0) {
		if(secondPlayerPieces.getFlagNum() == 0) {
			winner = TIE;
			reason = TIE_BOTH_FLAGS_CAPTURED;
		}
		else{
			// second player wins
			winner = SECOND_PLAYER;
			reason = FLAG_CAPTURED;
		}
	}
	else if(secondPlayerPieces.getFlagNum() == 0){
		// first player wins - flag num of first player is not 0.
		winner = FIRST_PLAYER;
		reason = FLAG_CAPTURED;
	}
	// flags number of both players is not 0.
	else if (opponentMovingNum == 0) {
		winner = curPlayer;
		reason = ALL_MOVING_PIECES_EATEN;
	}

	else {
		winner = NONE;
		reason = TIE_GAME_OVER;
	}
	return winner;
}

void GameBoard::addPieceToGame(int player, char piece, Position pos){
	setPieceAtPosition(player,piece,pos);
	increasePieceNum(player, piece, 1);
}
bool GameBoard::isEmpty(int player, Position& pos) const{
	return (getPieceAtPosition(player,pos) == (char) 0);
}

int GameBoard::getJokerMovingPiece(int player) const{
	if(player== FIRST_PLAYER)
		return firstPlayerPieces.getNumOfMovingJoker();
	else return secondPlayerPieces.getNumOfMovingJoker();
}

int GameBoard::checkMove(Move& move){
	char charToMove;
	// (1) boundary tests
	// test src boundary
	if(move.positionBoundaryTest(move.getSrc()) == INDEX_OUT_OF_BOUND){
		std::cout << "Illegal source position. Player: " << move.getPlayer() << " insert out of bound source position: ";
		move.getSrc().printPosition();
		std::cout << std::endl;
		return INDEX_OUT_OF_BOUND;
	}
	// test dst boundary
	if(move.positionBoundaryTest(move.getDst()) == INDEX_OUT_OF_BOUND){
		std::cout << "Illegal destination position. Player: " << move.getPlayer() << " insert out of bound source position: ";
		move.getDst().printPosition();
		std::cout << std::endl;
		return INDEX_OUT_OF_BOUND;
	}
	// boundary is valid
	// (2) moving to position contain same player piece
	if(!(isEmpty(move.getPlayer(),move.getDst()))){
		std::cout << "Illegal move. Player: " << move.getPlayer() << " try to move to destination position occupied by him. Destination position: ";
		move.getDst().printPosition();
		std::cout << std::endl;
		return ILLEGAL_MOVE;
	}
	if(testForValidMovementOfBoard(move) == ILLEGAL_MOVE){
		std::cout << "Illegal movement on board. Player: " << move.getPlayer() << " try to move from: ";
		move.getSrc().printPosition();
		std::cout << " to: ";
		move.getDst().printPosition();
		std::cout << std::endl;
		return ILLEGAL_MOVE;
	}
	// (3) try to move non moving piece
	charToMove = getPieceAtPosition(move.getPlayer(),move.getSrc());
	if(charToMove == (char)0){
		std::cout << "Illegal source position for Player: " << move.getPlayer() << ". Position ";
		move.getSrc().printPosition();
		std::cout << " does not contain a player piece." << std::endl;
		return ILLEGAL_MOVE;
	}

	if(charToMove == BOMB || charToMove == FLAG){
		std::cout << "Illegal source position for Player: " << move.getPlayer() << ". Position ";
		move.getSrc().printPosition();
		std::cout << " contains non moving piece: " << charToMove << std::endl;
		return ILLEGAL_MOVE;
	}

	// Seems OK ...
	return VALID_MOVE;
}

int GameBoard::testForJokerValidChange(Move& move) const{
	char newJokerChar;
	if(move.getIsJokerUpdated()){
		// joker position is empty
		if(isEmpty(move.getPlayer(), move.getJokerPos())){
			std::cout << "Joker position for Player: " << move.getPlayer() << " is empty. Position ";
			move.getJokerPos().printPosition();
			std::cout << std::endl;
			return ILLEGAL_MOVE;
		}

		// joker position doesn't contain a joker piece
		if(!islower(getPieceAtPosition(move.getPlayer(),move.getJokerPos()))){
			std::cout << "Joker position for Player: " << move.getPlayer() << " doesn't contain a joker's piece. Position ";
			move.getJokerPos().printPosition();
			std::cout << std::endl;
			return ILLEGAL_MOVE;
		}

		// test if joker new char is a valid char: S,R,P,B
		newJokerChar = move.getJokerNewChar();
		if(!move.isJokerValidChar(newJokerChar)){
			std::cout << "Joker new representation for player" << move.getPlayer() << " is invalid: " << toupper(newJokerChar) << std::endl;
			return ILLEGAL_MOVE;
		}

	}
	return VALID_MOVE;
}

int GameBoard::execMove(std::string line, Move& move) {
	int currentPlayer = move.getPlayer();
	int opponentPlayer = getOpponent(currentPlayer);
	// Parse line format
	if(move.parseLine(line) != VALID_LINE_FORMAT){
		std::cout << "Current line is not at the right format: <" << line << ">" << std::endl;
		winner = opponentPlayer;
		reason = BAD_MOVE;
		return ERROR;
	}
	// check if move is a valid move
	if(checkMove(move) != VALID_MOVE){
		std::cout << "Bad move for player " << currentPlayer << std::endl;
		winner = opponentPlayer;
		reason = BAD_MOVE;
		return ERROR;
	}
	updateBoardAfterMove(move);
	if (updateJoker(move) == ERROR) {
		//std::cout << "Bad move for player " << currentPlayer << ": illegal attempt to change Joker" << std::endl;
		reason = BAD_MOVE;
		return ERROR;

	}
	return SUCCESS;

}

int GameBoard::testForValidMovementOfBoard(Move& move){
	int delta;
	int srcX = move.getSrc().getXposition();
	int srcY = move.getSrc().getYposition();
	int dstX = move.getDst().getXposition();
	int dstY = move.getDst().getYposition();
	// todo check if src == dst is a valid move
	if(srcX == dstX)
		delta = dstY - srcY;
	else if(srcY == dstY)
		delta = dstX - srcX;
	else return ILLEGAL_MOVE;
	// moving on same row or on same column
	if(delta == -1 || delta == 1)
		return VALID_MOVE;
	else return ILLEGAL_MOVE;
}


int GameBoard::printBoard(std::ofstream& output) const{
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < M; y++) {
			Position pos (x,y);
			if (isEmpty(FIRST_PLAYER, pos)) {
				if (isEmpty(SECOND_PLAYER, pos)) {
					output << " ";
				} else {
					if(islower(secondPlayerBoard[x][y]))
						output << 'j';
					else
						output << (char)tolower(secondPlayerBoard[x][y]);
				}
			}
			else {
				if(islower(firstPlayerBoard[x][y]))
					output << 'J';
				else
					output << (char)toupper(firstPlayerBoard[x][y]);
			}
			if(output.bad()){
				std::cout << "Failed writing to output file" << std::strerror(errno) << std::endl;
				return ERROR;
			}
		}
		output << std::endl;
	}
	return SUCCESS;
}

