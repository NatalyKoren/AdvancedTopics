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

// only for unit testss!!!1
bool GameMove::parseLine(std::string line){
    // try to get Joker Line
    int fromX,fromY,toX,toY, jokerX,jokerY;
    int dummyInt;
    char newJokerRep,lineEnd, dummyChar;
    bool isJokerNewRep;

    // try to get Joker Line
    if(sscanf(line.c_str(), "%d %d %d %d J: %d %d %c",
              &fromX, &fromY,&toX, &toY, &jokerX, &jokerY, &newJokerRep) != 7){
        // try to get a regular line
        if(sscanf(line.c_str(), "%d %d %d %d",
                  &fromX, &fromY,&toX, &toY) != 4){
            // wrong format :(
            return ILLEGAL_LINE_FORMAT;
        }
        // line format is correct without joker update
        // test for line length
        if(sscanf(line.c_str(), "%d %d %d %d %c",
                  &dummyInt, &dummyInt,&dummyInt, &dummyInt, &lineEnd) == 5)
            return ILLEGAL_LINE_FORMAT;
        isJokerNewRep = false;
        jokerX = 0;
        jokerY = 0;
        newJokerRep = (char) 0;
    }
        // line format is correct with joker update
    else{
        // test for line length
        if(sscanf(line.c_str(), "%d %d %d %d J: %d %d %c %c",
                  &dummyInt, &dummyInt,&dummyInt, &dummyInt,
                  &dummyInt, &dummyInt, &dummyChar, &lineEnd) == 8)
            return ILLEGAL_LINE_FORMAT;
        if(!isupper(newJokerRep)){
            std::cout << "Illegal new representation for joker: " << newJokerRep << std::endl;
            return ILLEGAL_LINE_FORMAT;
        }

        isJokerNewRep = true;
    }

    // Update move data
    src.setXposition(fromY-1);
    src.setYposition(fromX-1);
    dst.setXposition(toY-1);
    dst.setYposition(toX-1);
    jokerInfo.setIsJokerChanged(isJokerNewRep);
    jokerInfo.setNewJokerRep(tolower(newJokerRep));
    jokerInfo.setJokerPosition(Position(jokerY-1, jokerX-1));


    return VALID_LINE_FORMAT;
}