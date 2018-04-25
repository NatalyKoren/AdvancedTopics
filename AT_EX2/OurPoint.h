/*
 * Position.h
 *
 *      Author: London
 */

#ifndef POSITION_H_
#define POSITION_H_
#include "Point.h"
#include <iostream>

class OurPoint : public Point {
	int x;
	int y;
public:
	OurPoint(int x,int y):x(x),y(y){}
	// --- Getters ---
	virtual int getX() const {return x;}
	int getY() const {return y;}
private:
	// --- Setters ---
	void setX(int pos){x=pos;}
	void setY(int pos){y=pos;}
	// Print OurPoint
	void printOurPoint()const{ std::cout << "(" << y+1 << "," << x+1 << ")";}
	bool isEqual(OurPoint& other) {return (other.x == x) && (other.y == y);}
};

#endif /* POSITION_H_ */
