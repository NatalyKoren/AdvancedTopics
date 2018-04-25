//
// Created by DELL on 25/04/2018.
//

#ifndef AT_EX2_GAMEMOVE_H
#define AT_EX2_GAMEMOVE_H

#include "Point.h"
#include <iostream>
#include <cstdio>
#include "Definitions.h"
#include "Move.h"
#include "JokerChange.h"
#include "Position.h"

class GameMove{
    bool isJokerChanged;
    Position jokerPos;
    char newJokerChar;
    int player;
    Position src;
    Position dst;
public:
    GameMove(int player);
    /***
     * Update fields data with move info.
     * @param moveData - move to be updated
     */

    void updateMoveFields(const Point& srcMove,const Point& dstMove);
    /***
     * Updates joker fields with data
     * @param jokerInfo - the data data to be updated
     */

    void updateJokerFields(const Point& pos, char newRep);
    /***
     * Test if pos is a valid position on board. Assuming pos contain 0-based indexes.
     * @param pos - position to be tested.
     * @return INDEX_OUT_OF_BOUND if position is not a valid position on board (out of bound).
     * Otherwise VALID_INDEX is returned.
     */
    int positionBoundaryTest (Position& pos) const;
    /***
     * Test if index is in row boundary or column boundary.
     * @param index - index to be tested. Assumed to be 0-based index.
     * @param isRowTest - true if index is a row index and false if index is a column index.
     * @return INDEX_OUT_OF_BOUND if index is out of bound. Otherwise VALID_INDEX is returned.
     */
    int boundaryTest (int index, bool isRowTest) const;
    /***
     * Test is new joker representation is a valid representation for joker.
     * @param newJokerRep - char to be tested.
     * @return true if newJokerChar is a valid joker representation and false otherwise.
     * valid representation is: BOMB, SCISSORS, ROCK, PAPER.
     */


    /***
     * Assuming move contain a valid positions on board ( not out of bound ).
     * Check if the step in move is a valid step: only one step forward, backward, lefd side or right side.
     * @param move - move to be checked.
     * @return ILLEGAL_MOVE if the step is not a valid step and VALID_MOVE otherwise.
     */
    int testForValidMovementOfBoard();
    bool isJokerValidChar (char newJokerRep) const;
    // Getters
    Position& getJokerPos(){ return jokerPos; }
    char getJokerNewChar()const{ return newJokerChar; }
    int getPlayer()const{ return player; }
    Position& getDst(){ return dst; }
    Position& getSrc(){ return src; }
    bool getIsJokerUpdated()const{ return isJokerChanged; }
    // Setters
    void setSrcPosition(Position& pos){src = pos;}
    void setDstPosition(Position& pos){dst = pos; }
    void setJokerPosition(Position& pos){jokerPos = pos;}
    void setJokerChar(char ch){newJokerChar = ch;}
    void setJokerUpdated(bool isUpdated){isJokerChanged = isUpdated;}
    void setPlayer(int curPlayer){player = curPlayer;}
    // For tests and debugging
    void printMove() const;


};




#endif //AT_EX2_GAMEMOVE_H
