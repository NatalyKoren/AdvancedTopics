//
// Created by DELL on 25/04/2018.
//

#include "GameMove.h"


void GameMove::printMove() const{
    std::cout << "Source position: " << src.getX() << "," << src.getY()  << std::endl;
    std::cout << "Destination position: " << dst.getX() << "," << dst.getY()  << std::endl;
    std::cout << "Player: " << player << std::endl;
    jokerInfo.printJokerInfo();

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


bool GameMove::isJokerValidChar(char newJokerChar) const{
    newJokerChar = toupper(newJokerChar);
    if(newJokerChar == SCISSORS || newJokerChar == ROCK ||
       newJokerChar == PAPER || newJokerChar == BOMB)
        return true;
    else return false;
}

void GameMove::updateJokerFields(const Point& pos, char newRep){
    jokerInfo.setJokerPosition(pos);
    jokerInfo.setNewJokerRep(newRep);
}

void GameMove::updateMoveFields(const Point& srcMove,const Point& dstMove){
    src.setXposition(srcMove.getX());
    src.setYposition(srcMove.getY());
    dst.setXposition(srcMove.getX());
    dst.setYposition(srcMove.getY());
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

void printPoint(const Point& p) { std::cout << "(" << p.getY()+1 << "," << p.getX()+1 << ")";}