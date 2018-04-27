/*
 * OurfightInfo.h
 *
 *  Created on: 25 Apr 2018
 *      Author: London
 */

#ifndef OURFIGHTINFO_H_
#define OURFIGHTINFO_H_
#include "Position.h"
#include "FightInfo.h"

class GameFightInfo: public FightInfo {
	Position position;
	char opponentPiece;
	int winner;
	bool isFight;

public:
	GameFightInfo(const Point& p, char opponent, int win): position(p),opponentPiece(opponent),winner(win),isFight(true) {}
	GameFightInfo(): position(-1,-1),opponentPiece((char)0),winner(TIE),isFight(false) { }

    // --- inteface functions ---
	virtual const Point& getPosition() const {return position;}
	virtual char getOpponentPiece() const {return opponentPiece;} // R, P, S, B or F (but NOT J)
	virtual int getWinner() const {return winner;} // 0 - both lost / tie, 1 - player 1 won, 2 - player 2 won

    // --- Setters ---
    void setPosition(const Position& p){ position.setXposition(p.getX()), position.setYposition(p.getY());}
    void setOpponentPiece(char opponent) { opponentPiece = opponent;}
    void setWinner(int win) { winner = win;}
    void setIsFight(bool newVal){ isFight = newVal;}

};
#endif /* OURFIGHTINFO_H_ */
