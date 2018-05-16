//
// Created by DELL on 02/05/2018.
//

#include "GameJokerChanged.h"

bool GameJokerChanged::isJokerValidChar() const{
    if(newJokerChar == SCISSORS || newJokerChar == ROCK ||
       newJokerChar == PAPER || newJokerChar == BOMB)
        return true;
    else return false;
}

void GameJokerChanged::printJokerInfo() const{
    std::cout << "Need to Update Joker? : " << isJokerChanged << std::endl;
    std::cout << "Joker position: " << jokerPos.getX() << "," << jokerPos.getY()  << std::endl;
    std::cout << "Joker new char: " << newJokerChar << std::endl;
}