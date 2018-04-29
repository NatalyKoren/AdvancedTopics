//
// Created by DELL on 25/04/2018.
//

#ifndef AT_EX2_GAMEMANAGER_H
#define AT_EX2_GAMEMANAGER_H

#include "GameBoard.h"
#include "PlayerAlgorithm.h"
#include "Definitions.h"
#include "FilePlayerAlgorithm.h"

class GameManager{
    GameBoard game;
    int currentPlayer;
    //std::unique_ptr<PlayerAlgorithm> firstPlayerAlgorithm;
    PlayerAlgorithm* firstPlayerAlgorithm = new FilePlayerAlgorithm();
    //std::unique_ptr<PlayerAlgorithm> secondPlayerAlgorithm;
public:
    GameManager(int firstPlayerType,int secondPlayerType);
    void updateInitialPositions();
    void performAllFightAfterInitBoards();
    void createBoardInfoAfterInit();



};


#endif //AT_EX2_GAMEMANAGER_H
