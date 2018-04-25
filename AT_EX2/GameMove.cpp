//
// Created by DELL on 25/04/2018.
//

#include "GameMove.h"

GameMove::GameMove(int player):isJokerChanged(false), jokerPos(0,0),
                       newJokerChar((char)0), player(player),src(0,0), dst(0,0) {}


void GameMove::printMove() const{
    std::cout << "Source position: " << src.getXposition() << "," << src.getYposition()  << std::endl;
    std::cout << "Destination position: " << dst.getXposition() << "," << dst.getYposition()  << std::endl;
    std::cout << "Player: " << player << std::endl;
    std::cout << "Need to Update Joker? : " << isJokerChanged << std::endl;
    if(isJokerChanged){
        std::cout << "Joker position: " << jokerPos.getXposition() << "," << jokerPos.getYposition()  << std::endl;
        std::cout << "Joker new char: " << newJokerChar << std::endl;
    }

}

int GameMove::boundaryTest(int index, bool isRowTest) const{
    char rowOrColBound = (isRowTest)? N:M;
    if(index < 0 || index >= rowOrColBound)
        return INDEX_OUT_OF_BOUND;
    else return VALID_INDEX;


}
int GameMove::positionBoundaryTest(Position& pos) const{
    int xPos = pos.getXposition();
    int yPos = pos.getYposition();
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
    jokerPos.setXposition(pos.getX());
    jokerPos.setYposition(pos.getY());
    newJokerChar = newRep;
}

void GameMove::updateMoveFields(const Point& srcMove,const Point& dstMove){
    src.setXposition(srcMove.getX());
    src.setYposition(srcMove.getY());
    dst.setXposition(srcMove.getX());
    dst.setYposition(srcMove.getY());
}

int GameMove::testForValidMovementOfBoard(){
    int delta;
    int srcX = src.getXposition();
    int srcY = src.getYposition();
    int dstX = dst.getXposition();
    int dstY = dst.getYposition();
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