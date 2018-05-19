//
// Created by DELL on 27/04/2018.
//

#ifndef AT_EX2_GAMEJOKERCHANGED_H
#define AT_EX2_GAMEJOKERCHANGED_H
#include "Definitions.h"
#include "Position.h"
#include "JokerChange.h"
/***
 * class GameJokerChanged: a class for managing the joker changes within a move.
 */
class GameJokerChanged : public JokerChange{
    int player;
    bool isJokerChanged;
    Position jokerPos;
    char newJokerChar;

public:
    // --- constructors ---
    GameJokerChanged(): player(FIRST_PLAYER),isJokerChanged(false),jokerPos(-1,-1),newJokerChar(EMPTY_CHAR) { }

    GameJokerChanged(int currPlayer, bool isJokerNewRep, int x, int y,char c):
            player(currPlayer),isJokerChanged(isJokerNewRep),jokerPos(x,y),newJokerChar(c) { }

    GameJokerChanged(int curPlayer): player(curPlayer),isJokerChanged(false),jokerPos(-1,-1),newJokerChar(EMPTY_CHAR) { }

    // --- interface functions ---
    virtual const Point& getJokerChangePosition() const {return jokerPos;}
    virtual char getJokerNewRep() const {return newJokerChar;} // R, P, S or B (but NOT J and NOT F)nd NOT F)

    // --- getters ---
    bool getIsJokerChanged() const {return isJokerChanged;}
    int getPlayer() const { return player; }

    // --- setters ---
    void setNewJokerRep(char c){ newJokerChar = c;}
    void setIsJokerChanged(bool newVal){ isJokerChanged = newVal;}
    void setJokerPosition(const Point& pos){ jokerPos.setXposition(pos.getX()), jokerPos.setYposition(pos.getY());}
    void setJokerPosition(int x, int y) {jokerPos.setXposition(x); jokerPos.setYposition(y); }
    void setPlayer(int newPlayer) { player = newPlayer; }

    /***
    * Test if new joker representation is a valid representation for joker.
    * @return true if newJokerChar is a valid joker representation and false otherwise.
    * valid representation is: BOMB, SCISSORS, ROCK, PAPER.
    */
    bool isJokerValidChar() const;

    // --- Print info ---
    void printJokerInfo() const;
};

#endif //AT_EX2_GAMEJOKERCHANGED_H
