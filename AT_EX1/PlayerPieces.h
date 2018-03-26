/*
 * game_piece.h
 *
 *  Created on: 26 במרץ 2018
 *      Author: DELL
 */

#ifndef PLAYERPIECES_H_
#define PLAYERPIECES_H_
#include "Definitions.h"
class PlayerPieces{
	int scissors;
	int rock;
	int paper;
	int bomb;
	int flag;
	int joker;

public:
	PlayerPieces(): scissors(0), rock(0), paper(0), bomb(0), flag(0), joker(0) { }
	// --- Setters
	void setScissorsNum(int num){ scissors = num; }
	void setRockNum(int num){ rock = num; }
	void setPaperNum(int num){paper = num; }
	void setBombNum(int num){bomb = num; }
	void setFlagNum(int num){flag = num; }
	void setJokerNum(int num){joker = num; }
	// --- Getters
	int getScissorsNum(){ return scissors; }
	int getRockNum(){ return rock; }
	int getPaperNum(){ return paper; }
	int getBombNum(){ return bomb; }
	int getFlagNum(){ return flag; }
	int getJokerNum(){ return joker; }
	// --- Move pieces number
	int getMovePiecesNum() { return (scissors+ rock + paper + joker); }
	// set piece to player
	void incrementPieceNum(char piece, int num);

};

#endif /* PLAYERPIECES_H_ */
