/*
 * Position.h
 *
 *      Author: London
 */

#ifndef POSITION_H_
#define POSITION_H_
#include "Point.h"
#include <iostream>

class GamePoint : public Point {
	int x;
	int y;
public:
	GamePoint(int x,int y):x(x),y(y){}
	// --- Getters ---
	virtual int getX() const {return x;}
	int getY() const {return y;}
};

#endif /* POSITION_H_ */
