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
#include "GameJokerChanged.h"
#include "Position.h"
extern void printPoint(const Point& p);
class GameMove : public Move{
    int player;
    Position src;
    Position dst;
    GameJokerChanged jokerInfo;
public:
    // --- constructors ---
    GameMove(int player): player(player),src(-1,-1), dst(-1,-1), jokerInfo() { }
    // this will be used is case there is a joker change in current move
    GameMove(int player, Position from, Position to, bool isJokerChange, Position jokerPos, char newJokerChar):
            player(player),src(from.getX(),from.getY()), dst(to.getX(), to.getY()),
            jokerInfo(isJokerChange, jokerPos.getX(), jokerPos.getY(), newJokerChar) { }

    // In case there is not a joker change
    GameMove(int player, Position from, Position to):
            player(player),src(from.getX(),from.getY()), dst(to.getX(), to.getY()),
            jokerInfo() { }



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
    int positionBoundaryTest (const Point& pos) const;
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
    // --- inteface functions ---
    virtual const Point& getFrom() const {return src;}
    virtual const Point& getTo() const {return dst;}
    bool isJokerValidChar (char newJokerRep) const;
    // Getters
    const Point& getJokerPos(){ return jokerInfo.getJokerChangePosition(); }
    // this suppose to be const.. because of the interface const qualifier needs to be removed.
    char getJokerNewChar(){ return jokerInfo.getJokerNewRep(); }
    int getPlayer()const{ return player; }

    bool getIsJokerUpdated()const{ return jokerInfo.getIsJokerChanged(); }
    // Setters
    void setSrcPosition(Position& pos){src = pos;}
    void setDstPosition(Position& pos){dst = pos; }
    void setJokerPosition(Position& pos){jokerInfo.setJokerPosition(pos);}
    void setJokerChar(char ch){jokerInfo.setNewJokerRep(ch);}
    void setJokerUpdated(bool isUpdated){jokerInfo.setIsJokerChanged(isUpdated);}
    void setPlayer(int curPlayer){player = curPlayer;}
    // For tests and debugging
    void printMove() const;

    // only for unit test!!
    bool parseLine(std::string line);


};

// global function
void printPoint(const Point& p);


#endif //AT_EX2_GAMEMOVE_H
