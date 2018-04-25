#ifndef OURPIECEPOSITION_H_
#define OURPIECEPOSITION_H_

// an instance is created for each of the pieces of the board

class OurPiecePosition : public PiecePosition {
    Point pos;
	char piece;
	char jokerRep;

public:
	OurPiecePosition(Point& point, char newPiece, char newJokerRep):
		pos(point),piece(newPiece), jokerRep(newJokerRep){}
	virtual const Point& getPosition() const {return pos;}
	virtual char getPiece() const {return piece;} // R, P, S, B, J or F
	virtual char getJokerRep() const {return jokerRep;} // ONLY for Joker: R, P, S or B -- non-Joker may return '#'
};

#endif /* OURPIECEPOSITION_H_ */
