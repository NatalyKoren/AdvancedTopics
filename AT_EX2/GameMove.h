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
#include <fstream>

/***
 * Class GameMove: a class for representing a move in the game.
 */
extern void printPoint(const Point& p);
class GameMove : public Move{
    int player;
    Position src;
    Position dst;
public:
    // --- constructors ---
    GameMove(int player): player(player),src(-1,-1), dst(-1,-1) { }
    // this will be used is case there is a joker change in current move
    GameMove(int player, Position from, Position to):
            player(player),src(from.getX(),from.getY()), dst(to.getX(), to.getY()) { }
    // Copy from move interface
    GameMove(int movePlayer, Move& move):player(movePlayer),src(move.getFrom()), dst(move.getTo()) { }

    // --- interface functions ---
    virtual const Point& getFrom() const {return src;}
    virtual const Point& getTo() const {return dst;}
    // --- Getters ---
    int getPlayer()const{ return player; }

    // --- Setters ---
    // Set source position
    void setSrcPosition(const Position& pos){src.setXposition(pos.getX()); src.setYposition(pos.getY());}
    void setSrcPosition(int x,int y) { src.setXposition(x); src.setYposition(y);}
    // Set Destination position
    void setDstPosition(const Position& pos){dst.setXposition(pos.getX()); dst.setYposition(pos.getY());}
    void setDstPosition(int x,int y) { dst.setXposition(x); dst.setYposition(y);}
    // Set player
    void setPlayer(int curPlayer){player = curPlayer;}

    /***
     * Update fields data with move info. Changing them from 1-based to 0-based.
     * @param moveData - move to be updated
     */
    void updateMoveFields(Move& move);

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
     * Assuming move contain a valid positions on board (not out of bound - this function does not check for boundary).
     * Check if the step in move is a valid step: only one step forward, backward, left side or right side.
     * @param move - move to be checked.
     * @return ILLEGAL_MOVE if the step is not a valid step and VALID_MOVE otherwise.
     */
    int testForValidMovementOfBoard();

    // For tests and debugging
    void printMove(std::ostream* ostream) const;
};

// global function
void printPoint(const Point& p);


#endif //AT_EX2_GAMEMOVE_H
