/*
 * Move.cpp
 *
 *  Created on: 26 במרץ 2018
 *      Author: DELL
 */
#include "Move.h"

Move::Move(int player):isJokerChanged(false), jokerPos(0,0),
	newJokerChar((char)0), player(player),src(0,0), dst(0,0) {}
