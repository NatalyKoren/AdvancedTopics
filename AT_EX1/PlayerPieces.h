/*
 * game_piece.h
 *
 *      Author: DELL
 */

#ifndef PLAYERPIECES_H_
#define PLAYERPIECES_H_
#include "Definitions.h"
#include <ctype.h>
class PlayerPieces{
	int scissors;
	int rock;
	int paper;
	int bomb;
	int flag;
	int joker;
	int numOfMovingJokers;

public:
	PlayerPieces();
	// --- Setters
	void setScissorsNum(int num){ scissors = num; }
	void setRockNum(int num){ rock = num; }
	void setPaperNum(int num){paper = num; }
	void setBombNum(int num){bomb = num; }
	void setFlagNum(int num){flag = num; }
	void setJokerNum(int num){joker = num; }
	void setNumOfMovingJoker(int num){numOfMovingJokers = num; }
	// --- Getters
	int getScissorsNum(){ return scissors; }
	int getRockNum(){ return rock; }
	int getPaperNum(){ return paper; }
	int getBombNum(){ return bomb; }
	int getFlagNum(){ return flag; }
	int getJokerNum(){ return joker; }
	int getNumOfMovingJoker(){return numOfMovingJokers; }
	// --- Move pieces number
	int getMovePiecesNum() { return (scissors+ rock + paper + numOfMovingJokers); }
	// set piece to player
	void incrementPieceNum(char piece, int num);
	void incrementJokerMovingPieces(int num) { numOfMovingJokers+=num; }
	void updateJokerMovingCount(char previousPiece, char newPiece);

};

#endif /* PLAYERPIECES_H_ */
