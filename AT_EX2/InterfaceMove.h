/*
 * OurMove.h
 *
 *  Created on: 25 Apr 2018
 *      Author: admin
 */

#ifndef OURMOVE_H_
#define OURMOVE_H_

#include "InterfacePoint.h"
#include <iostream>
#include <cstdio>
#include "Definitions.h"

class InterfaceMove{
	Point from;
	Point to;
public:
	InterfaceMove(Point src, Point dst):from(src),to(dst) {}
	// Getters
	virtual const Point& getFrom() const {return from;}
	virtual const Point& getTo() const {return to;}
};

#endif /* OURMOVE_H_ */
