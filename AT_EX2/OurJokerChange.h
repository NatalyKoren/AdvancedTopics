/*
 * OurJokerChange.h
 *
 *  Created on: 25 Apr 2018
 *      Author: London
 */

#ifndef OURJOKERCHANGE_H_
#define OURJOKERCHANGE_H_

#include "JokerChange.h"

class OurJokerChange: public JokerChange {
	Point jokerChangePosition;
	char jokerNewRep;

public:
	OurJokerChange();
	virtual const Point& getJokerChangePosition() {return jokerChangePosition;}
	virtual char getJokerNewRep() {return jokerNewRep;}
};

#endif /* OURJOKERCHANGE_H_ */
