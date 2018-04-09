/*
 * Position.h
 *
 *      Author: DELL
 */

#ifndef POSITION_H_
#define POSITION_H_

#include <iostream>

class Position{
	int x;
	int y;
public:
	Position(int x,int y):x(x),y(y){}
	// --- Getters ---
	int getXposition()const{return x;}
	int getYposition()const{return y;}
	// --- Setters ---
	void setXposition(int pos){x=pos;}
	void setYposition(int pos){y=pos;}
	// Print Position
	void printPosition()const{ std::cout << "(" << x+1 << "," << y+1 << ")";}
};

#endif /* POSITION_H_ */
