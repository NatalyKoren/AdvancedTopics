//
// Created by DELL on 25/04/2018.
//

#ifndef AT_EX2_POSITION_H
#define AT_EX2_POSITION_H

#include <iostream>
#include "Point.h"

/***
 * Class Position: Represents position on game board.
 */

class Position: public Point{
    int x;
    int y;
public:
    // --- Constructors ---
    Position(int x,int y):x(x),y(y){}
    Position(const Point& p):x(p.getX()),y(p.getY()){}
    // --- interface functions ---
    virtual int getX()const{return x;}
    virtual int getY()const{return y;}
    // --- Setters ---
    void setXposition(int pos){x=pos;}
    void setYposition(int pos){y=pos;}
    // Print Position
    void printPosition()const{ std::cout << "(" << x+1 << "," << y+1 << ")";}
    bool isEqual(const Point& other) {return (other.getX() == x) && (other.getY() == y);}
};



#endif //AT_EX2_POSITION_H
