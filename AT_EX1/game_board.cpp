/*
 * game_board.cpp
 *
 *  Created on: 26 במרץ 2018
 *      Author: DELL
 */
#include "game_board.h"
#include <ctype.h>

GameBoard::GameBoard(int firstNum, int secondNum):
	pieceNumFirstPlayer(firstNum),pieceNumSecondPlayer(secondNum),
	isFirstFlagEaten(false), isSecondFlagEaten(false) {}

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
void GameBoard::updateBoardAfterMove(int player, Move& move){
	// assuming it is a valid move
	int winner;
	char charToUpdate, charToRemove;
	int opponent = getOpponent(player);
	Position srcPos = move.getSrc(); // TODO check if it should be Position&
	Position dstPos = move.getDst();
	if(isFight(opponent, move.getDst())){
		//Fight
		winner = fight(move.getDst());
		if(winner == player){
			// get char to be updated.
			charToUpdate = getPieceAtPosition(player, srcPos);
			// update player char
			setPieceAtPosition(player,charToUpdate, dstPos);
			// update opponent char
			updateAfterLooseFight(opponent,dstPos);
		}
		// the current player lose...
		else updateAfterLooseFight(player,dstPos);
	}
	// No fight- need only to update player's dest position
	else setPieceAtPosition(player,charToUpdate, dstPos);
	// set source position to zero
	setPieceAtPosition(player,0, move.getSrc());
	//Update joker
	if(move.isJokerUpdated()){
		// TODO - this should be here or at the beginning of the function?
		// there is a question regarding this in the forum
		setPieceAtPosition(player, tolower(move.getJokerNewChar()), move.getJokerPos());
	}
}

int GameBoard::fight(Position& pos){
	char firstPlayerPiece = getPieceAtPosition(FIRST_PLAYER,pos);
	char secondPlayerPiece = getPieceAtPosition(SECOND_PLAYER,pos);
	//For joker cases
	firstPlayerPiece = toupper(firstPlayerPiece);
	secondPlayerPiece = toupper(secondPlayerPiece);
	// Tie
	if(firstPlayerPiece == secondPlayerPiece) return 0;

	switch(firstPlayerPiece){
	case 'B':
		return FIRST_PLAYER;
	case 'F':
		return SECOND_PLAYER;
	case 'R':
		if(secondPlayerPiece == 'S' || secondPlayerPiece == 'F') return FIRST_PLAYER;
		else return SECOND_PLAYER;
	case 'P':
		if(secondPlayerPiece == 'R' || secondPlayerPiece == 'F') return FIRST_PLAYER;
		else return SECOND_PLAYER;
	case 'S':
		if(secondPlayerPiece == 'P' || secondPlayerPiece == 'F') return FIRST_PLAYER;
		else return SECOND_PLAYER;
	default:
		return -1;

	}

}
void GameBoard::decreasePieceNum(int player, int num){
	if(player == FIRST_PLAYER) pieceNumFirstPlayer-=num;
	else pieceNumSecondPlayer-=num;
}

void GameBoard::updateAfterLooseFight(int player, Position& pos){
	char charToRemove = getPieceAtPosition(player, pos);
	setPieceAtPosition(player,0, pos);
	decreasePieceNum(player,1);
	if(charToRemove == 'F') setPlayerFlageEaten(player);
}
void GameBoard::setPlayerFlageEaten(int player){
	if(player==FIRST_PLAYER) isFirstFlagEaten = true;
	else isSecondFlagEaten = true;
}
int GameBoard::checkVictory(){
	//TODO
	return 0;
}

