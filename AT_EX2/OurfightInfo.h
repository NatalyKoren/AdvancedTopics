/*
 * OurfightInfo.h
 *
 *  Created on: 25 Apr 2018
 *      Author: London
 */

#ifndef OURFIGHTINFO_H_
#define OURFIGHTINFO_H_

class OurFightInfo: public FightInfo {
	Point position;
	char opponentPiece;
	int winner;

public:
	virtual const Point& getPosition() const {return position;}
	virtual char getOpponentPiece() const {return opponentPiece;} // R, P, S, B or F (but NOT J)
	virtual int getWinner() const {return winner;}; // 0 - both lost / tie, 1 - player 1 won, 2 - player 2 won

};
#endif /* OURFIGHTINFO_H_ */
