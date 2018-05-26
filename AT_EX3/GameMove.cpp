//
// Created by DELL on 25/04/2018.
//

#include "GameMove.h"

void GameMove::printMove(std::ostream* ostream) const{
    *ostream << "Source position: " << src.getX()+1 << "," << src.getY()+1 << std::endl;
    *ostream << "Destination position: " << dst.getX()+1 << "," << dst.getY()+1 << std::endl;
    *ostream << "Player: " << player << std::endl;

}

int GameMove::boundaryTest(int index, bool isRowTest) const{
    char rowOrColBound = (isRowTest)? N:M;
    if(index < 0 || index >= rowOrColBound)
        return INDEX_OUT_OF_BOUND;
    else return VALID_INDEX;


}
int GameMove::positionBoundaryTest(const Point& pos) const{
    int xPos = pos.getX();
    int yPos = pos.getY();
    if(boundaryTest(xPos, true) == INDEX_OUT_OF_BOUND)
        return INDEX_OUT_OF_BOUND;
    if(boundaryTest(yPos, false) == INDEX_OUT_OF_BOUND)
        return INDEX_OUT_OF_BOUND;
    return VALID_INDEX;
}



void GameMove::updateMoveFields(Move& move){
    Position srcPos(move.getFrom());
    Position toPos(move.getTo());
    src.setXposition(srcPos.getX()-1);
    src.setYposition(srcPos.getY()-1);
    dst.setXposition(toPos.getX()-1);
    dst.setYposition(toPos.getY()-1);
}

int GameMove::testForValidMovementOfBoard(){
    int delta;
    int srcX = src.getX();
    int srcY = src.getY();
    int dstX = dst.getX();
    int dstY = dst.getY();
    if(srcX == dstX)
        delta = dstY - srcY;
    else if(srcY == dstY)
        delta = dstX - srcX;
    else return ILLEGAL_MOVE;
    // moving on same row or on same column
    if(delta == -1 || delta == 1)
        return VALID_MOVE;
    else return ILLEGAL_MOVE;
}

void printPoint(const Point& p) { std::cout << "(" << p.getX()+1 << "," << p.getY()+1 << ")";}