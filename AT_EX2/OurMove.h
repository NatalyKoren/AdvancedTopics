/*
 * OurMove.h
 *
 *  Created on: 25 Apr 2018
 *      Author: admin
 */

#ifndef OURMOVE_H_
#define OURMOVE_H_

#include "Point.h"
#include <iostream>
#include <cstdio>
#include "Definitions.h"

class Move{
	Position from;
	Position to;
public:
	Move();
	// Getters
	Position& getDst(){ return from; }
	Position& getSrc(){ return to; }
};

#endif /* OURMOVE_H_ */
