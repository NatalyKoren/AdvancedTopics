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
    char firstPlayerPiece;
	char secondPlayerPiece;
	int winner;
	bool isFight;

public:
	// --- Constructors ---
    GameFightInfo(const Point& p, char firstPlayer, char secondPlayer, int win):
            position(p),firstPlayerPiece(firstPlayer),secondPlayerPiece(secondPlayer),winner(win),isFight(true) {}

    GameFightInfo(): position(-1,-1),firstPlayerPiece(EMPTY_CHAR),secondPlayerPiece(EMPTY_CHAR),winner(TIE),isFight(false) { }

    // --- interface functions ---
	virtual const Point& getPosition() const {return position;}
    // R, P, S, B or F (but NOT J)
    virtual char getPiece(int player) const{
        if(player==FIRST_PLAYER) return firstPlayerPiece;
        else return secondPlayerPiece;
    }
	virtual int getWinner() const {return winner;} // 0 - both lost / tie, 1 - player 1 won, 2 - player 2 won

    // --- Setters ---
    void setPosition(const Position& p){ position.setXposition(p.getX()); position.setYposition(p.getY());}
    void setPosition(int x, int y) {position.setXposition(x); position.setYposition(y);}
    void setPlayerPiece(int player, char piece){
        if(player==FIRST_PLAYER) firstPlayerPiece = piece;
        else secondPlayerPiece = piece;
    }
    void setWinner(int win) { winner = win;}
    void setIsFight(bool newVal){ isFight = newVal;}

    // --- Getters ---
    bool getIsFight()const { return isFight;}
};
#endif /* OURFIGHTINFO_H_ */
