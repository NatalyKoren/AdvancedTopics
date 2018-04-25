//
// Created by DELL on 25/04/2018.
//

#ifndef AT_EX2_GAMEMANAGER_H
#define AT_EX2_GAMEMANAGER_H

#include "GameBoard.h"
#include "PlayerAlgorithm.h"

class GameManager{
    GameBoard game;
    int currentPlayer;
    PlayerAlgorithm *firstPlayerAlgorithm;
    PlayerAlgorithm *secondPlayerAlgorithm;
public:
    GameManager(int firtPlayerType,int secondPlayerType);
    void updateInitialPositions();
    void performAllFightAfterInitBoards();
    void createBoardInfoAfterInit();



};


#endif //AT_EX2_GAMEMANAGER_H
