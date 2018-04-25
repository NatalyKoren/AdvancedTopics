/*
 * Position.h
 *
 *      Author: London
 */

#ifndef POSITION_H_
#define POSITION_H_
#include "Point.h"
#include <iostream>

class InterfacePoint : public Point {
	int x;
	int y;
public:
    InterfacePoint(int x,int y):x(x),y(y){}
	// --- Getters ---
	virtual int getX() const {return x;}
	int getY() const {return y;}
};

#endif /* POSITION_H_ */
