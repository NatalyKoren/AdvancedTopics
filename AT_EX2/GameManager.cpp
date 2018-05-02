//
// Created by DELL on 25/04/2018.
//

#include "GameManager.h"


GameManager::GameManager(int firstPlayerType, int secondPlayerType):game(),currentPlayer(FIRST_PLAYER){
/*
    firstPlayerAlgorithm = (firstPlayerType == FILE_PLAYER)?
                           std::make_unique<FilePlayerAlgorithm>():std::make_unique<AutoPlayerAlgorithm>();

    secondPlayerAlgorithm = (secondPlayerType == FILE_PLAYER)?
                           std::make_unique<FilePlayerAlgorithm>():std::make_unique<AutoPlayerAlgorithm>();
*/
    if(firstPlayerType == FILE_PLAYER)
        firstPlayerAlgorithm = std::make_unique<FilePlayerAlgorithm>(FIRST_PLAYER);
    else
        firstPlayerAlgorithm = std::make_unique<AutoPlayerAlgorithm>(FIRST_PLAYER);

    if(secondPlayerType == FILE_PLAYER)
        secondPlayerAlgorithm = std::make_unique<FilePlayerAlgorithm>(SECOND_PLAYER);
    else
        secondPlayerAlgorithm = std::make_unique<AutoPlayerAlgorithm>(SECOND_PLAYER);

}

int GameManager::updateInitialPositions(){
    // TODO: Check what about line number error and reason for error - need to see EX1 implementation for this.
    std::vector<unique_ptr<PiecePosition>> firstPlayerPositions;
    std::vector<unique_ptr<PiecePosition>> secondPlayerPositions;
    bool firstPlayerBadPositioningFile = false;
    bool secondPlayerBadPositioningFile = false;
    int reason = SUCCESS;
    // get players positions on boards
    firstPlayerAlgorithm->getInitialPositions(FIRST_PLAYER, firstPlayerPositions);
    secondPlayerAlgorithm->getInitialPositions(SECOND_PLAYER, secondPlayerPositions);
    // update boards with positioning lists
    int updateResult = updatePositionsOnBoard(FIRST_PLAYER, firstPlayerPositions);
    if(updateResult == ERROR){
        std::cout << "Error in first player positioning stage" << std::endl;
        firstPlayerBadPositioningFile = true;
    }

    updateResult = updatePositionsOnBoard(SECOND_PLAYER, secondPlayerPositions);
    if(updateResult == ERROR){
        std::cout << "Error in second player positioning stage" << std::endl;
        secondPlayerBadPositioningFile = true;
    }
    // check if some player failed in positioning file
    if(firstPlayerBadPositioningFile && secondPlayerBadPositioningFile){
        // Both players have bad positioning file
        game.setWinner(TIE);
        game.setReason(BOTH_PLAYERS_BAD_POSITIONING);
    }
    else if(firstPlayerBadPositioningFile){
        // first player has bad positioning file - second player wins
        game.setWinner(SECOND_PLAYER);
        game.setReason(BAD_POSITIONING);
    }
    else if(secondPlayerBadPositioningFile){
        // second player has bad positioning file - second player wins
        game.setWinner(FIRST_PLAYER);
        game.setReason(BAD_POSITIONING);
    }
    else return SUCCESS;
    return ERROR;
}

int GameManager::updatePositionsOnBoard(int player, std::vector<unique_ptr<PiecePosition>>& vectorToUpdate){
    char pieceType;
    for(unique_ptr<PiecePosition>& pieceInfo: vectorToUpdate){
        pieceType = pieceInfo->getPiece();
        if(pieceType == (char)0){
            // Indicating an error on positioning
            return ERROR;
        }
        // need to set lower case character in case of a joker
        if(pieceType == JOKER)
            pieceType = tolower(pieceInfo->getJokerRep());
        game.addPieceToGame(player,pieceType,pieceInfo->getPosition());
    }
    return SUCCESS;
}

int GameManager::performAllFightAfterInitBoards(std::vector<FightInfo>& fights){
    Position pos (0,0);
    GameFightInfo fightInfo;
    for (int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            pos.setXposition(i);
            pos.setYposition(j);
            if(!game.isEmpty(FIRST_PLAYER,pos))
                game.checkAndRunFight(FIRST_PLAYER, pos,fightInfo);
        }
    }
    return game.checkVictory(currentPlayer, true);
}