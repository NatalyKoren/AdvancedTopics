/*
 * PlayerPieces.cpp
 *
 *  Created on: 26 במרץ 2018
 *      Author: DELL
 */
#include "PlayerPieces.h"

bool PlayerPieces::incrementPieceNum(char piece, int num){
	bool isRemoved = true;
	switch(piece){
	case SCISSORS:
		scissors+= num;
		break;
	case ROCK:
		rock+= num;
		break;
	case PAPER:
		paper+= num;
		break;
	case JOKER:
		joker+= num;
		break;
	case BOMB:
		bomb+= num;
		break;
	case FLAG:
		flag+= num;
		break;
	default:
		isRemoved = false;
	}
	return isRemoved;
}
