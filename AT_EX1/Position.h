/*
 * Position.h
 *
 *  Created on: 26 ���� 2018
 *      Author: DELL
 */

#ifndef POSITION_H_
#define POSITION_H_

class Position{
	int x;
	int y;

	Position(int x,int y):x(x),y(y){}
	// --- Getters ---
	int getXposition()const{return x;}
	int getYposition()const{return y;}
	// --- Setters ---
	void setXposition(int pos){x=pos;}
	void setYposition(int pos){y=pos;}
};

#endif /* POSITION_H_ */
