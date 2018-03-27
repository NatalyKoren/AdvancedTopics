/*
 * game_board.cpp
 *
 *  Created on: 26 במרץ 2018
 *      Author: DELL
 */
#include <ctype.h>
#include "GameBoard.h"

GameBoard::GameBoard():firstPlayerPieces(),secondPlayerPieces() { }

char GameBoard::getPieceAtPosition(int player, Position& pos){
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

bool GameBoard::isFight(int playerToCheck, Position& pos){
	int x = pos.getXposition();
	int y = pos.getYposition();
	if(playerToCheck == FIRST_PLAYER)
		return (firstPlayerBoard[x][y] != (char) 0);
	else return (secondPlayerBoard[x][y] != (char) 0);
}
void GameBoard::updateBoardAfterMove(int player, Move* move){
	// assuming it is a valid move
	int winner;
	int opponent = getOpponent(player);
	Position srcPos = move->getSrc(); // TODO check if it should be Position&
	Position dstPos = move->getDst();
	// get char to be updated.
	char charToUpdate = getPieceAtPosition(player, srcPos);
	// update player char
	setPieceAtPosition(player,charToUpdate, dstPos);
	if(isFight(opponent, move->getDst())){
		//Fight
		winner = fight(move->getDst());
		if(winner == player){
			// update opponent char
			updateAfterLoseFight(opponent,dstPos);
		}
		// the current player lose...
		else updateAfterLoseFight(player,dstPos);
	}
	// No fight- need only to update player's dest position
	else setPieceAtPosition(player,charToUpdate, dstPos);
	// set source position to zero
	setPieceAtPosition(player,0, move->getSrc());
	//Update joker
	if(move->getIsJokerUpdated()){
		// TODO - this should be here or at the beginning of the function?
		// there is a question regarding this in the forum
		setPieceAtPosition(player, tolower(move->getJokerNewChar()), move->getJokerPos());
	}
}

int GameBoard::fight(Position& pos){
	char firstPlayerPiece = getPieceAtPosition(FIRST_PLAYER,pos);
	char secondPlayerPiece = getPieceAtPosition(SECOND_PLAYER,pos);
	//For joker cases
	firstPlayerPiece = toupper(firstPlayerPiece);
	secondPlayerPiece = toupper(secondPlayerPiece);
	// Tie
	if(firstPlayerPiece == secondPlayerPiece) return TIE;

	switch(firstPlayerPiece){
	case BOMB:
		return FIRST_PLAYER;
	case FLAG:
		return SECOND_PLAYER;
	case ROCK:
		if(secondPlayerPiece == SCISSORS || secondPlayerPiece == FLAG) return FIRST_PLAYER;
		else return SECOND_PLAYER;
	case PAPER:
		if(secondPlayerPiece == ROCK || secondPlayerPiece == FLAG) return FIRST_PLAYER;
		else return SECOND_PLAYER;
	case SCISSORS:
		if(secondPlayerPiece == PAPER || secondPlayerPiece == FLAG) return FIRST_PLAYER;
		else return SECOND_PLAYER;
	default:
		return -1;

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

int GameBoard::checkVictory(){
	int firstPlayerMoovinNum = firstPlayerPieces.getMovePiecesNum();
	int secondPlayerMoovinNum = secondPlayerPieces.getMovePiecesNum();
	if(firstPlayerMoovinNum==0 || firstPlayerPieces.getFlagNum() == 0)
		return SECOND_PLAYER;
	if(secondPlayerMoovinNum == 0 || secondPlayerPieces.getFlagNum() == 0)
		return FIRST_PLAYER;
	return TIE;
}
void GameBoard::addPieceToGame(int player, char piece, Position pos){
	setPieceAtPosition(player,piece,pos);
	if(islower(piece))
		piece = JOKER;
	increasePieceNum(player, piece, 1);
}

