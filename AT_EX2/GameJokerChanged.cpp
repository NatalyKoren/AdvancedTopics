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