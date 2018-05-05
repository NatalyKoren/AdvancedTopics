//
// Created by DELL on 27/04/2018.
//

#ifndef AT_EX2_GAMEJOKERCHANGED_H
#define AT_EX2_GAMEJOKERCHANGED_H
#include "Definitions.h"
#include "Position.h"
#include "JokerChange.h"

class GameJokerChanged : public JokerChange{
    bool isJokerChanged;
    Position jokerPos;
    char newJokerChar;

public:
    // --- constructors ---
    // if we pass all the parameters the joker have been changed
    GameJokerChanged(bool isJokernewRep, int x, int y,char c):
            isJokerChanged(isJokernewRep),jokerPos(x,y),newJokerChar(c) { }
    // empty ctor
    GameJokerChanged(): isJokerChanged(false),jokerPos(-1,-1),newJokerChar((char)0) { }
    // for readability
    GameJokerChanged(bool isJokerNewRep): isJokerChanged(isJokerNewRep),jokerPos(-1,-1),newJokerChar((char)0) { }

    // --- inteface functions ---
    virtual const Point& getJokerChangePosition() const {return jokerPos;}
    virtual char getJokerNewRep() const {return newJokerChar;} // R, P, S or B (but NOT J and NOT F)nd NOT F)
    // --- getters ---
    bool getIsJokerChanged() const {return isJokerChanged;}

    // --- setters ---
    void setNewJokerRep(char c){ newJokerChar = c;}
    void setIsJokerChanged(bool newVal){ isJokerChanged = newVal;}
    void setJokerPosition(const Point& pos){ jokerPos.setXposition(pos.getX()), jokerPos.setYposition(pos.getY());}


    // --- Print info ---
    void printJokerInfo() const{
        std::cout << "Need to Update Joker? : " << isJokerChanged << std::endl;
        std::cout << "Joker position: " << jokerPos.getX() << "," << jokerPos.getY()  << std::endl;
        std::cout << "Joker new char: " << newJokerChar << std::endl;
    }

};


#endif //AT_EX2_GAMEJOKERCHANGED_H
