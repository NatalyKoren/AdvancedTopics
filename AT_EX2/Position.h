//
// Created by DELL on 25/04/2018.
//

#ifndef AT_EX2_POSITION_H
#define AT_EX2_POSITION_H

#include <iostream>
#include "Point.h"

class Position: public Point{
    int x;
    int y;
public:
    Position(int x,int y):x(x),y(y){}
    Position(const Point& p):x(p.getX()),y(p.getY()){}
    // --- inteface functions ---
    virtual int getX()const{return x;}
    virtual int getY()const{return y;}
    // --- Setters ---
    void setXposition(int pos){x=pos;}
    void setYposition(int pos){y=pos;}
    // Print Position
    void printPosition()const{ std::cout << "(" << y+1 << "," << x+1 << ")";}
    bool isEqual(const Point& other) {return (other.getX() == x) && (other.getY() == y);}
};



#endif //AT_EX2_POSITION_H
