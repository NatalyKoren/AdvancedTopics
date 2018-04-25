//
// Created by DELL on 25/04/2018.
//

#ifndef AT_EX2_POSITION_H
#define AT_EX2_POSITION_H

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
    void printPosition()const{ std::cout << "(" << y+1 << "," << x+1 << ")";}
    bool isEqual(Position& other) {return (other.x == x) && (other.y == y);}
};



#endif //AT_EX2_POSITION_H
