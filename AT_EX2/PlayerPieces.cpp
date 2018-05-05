//
// Created by DELL on 25/04/2018.
//

#include "PlayerPieces.h"

PlayerPieces::PlayerPieces(): scissors(0), rock(0), paper(0), bomb(0), flag(0),
                              joker(0), numOfMovingJokers(0) { }

void PlayerPieces::incrementPieceNum(char piece, int num){
    bool isMovingPiece = false;
    if(islower(piece)){
        // It is a joker piece
        isMovingPiece = (toupper(piece) != BOMB);
        piece = JOKER;
    }
    switch(piece){
        case SCISSORS:
            scissors+= num;
            break;
        case ROCK:
            rock+= num;
            break;
        case PAPER:
            paper+= num;
            break;
        case JOKER:
            joker+= num;
            if(isMovingPiece)
                numOfMovingJokers+=num;
            break;
        case BOMB:
            bomb+= num;
            break;
        case FLAG:
            flag+= num;
            break;
        default:
            break;
    }
}
void PlayerPieces::updateJokerMovingCount(char previousPiece, char newPiece){
    if(newPiece != previousPiece){
        // the joker got new representation
        previousPiece = toupper(previousPiece);
        newPiece = toupper(newPiece);
        if(newPiece == BOMB && previousPiece != (char) 0)
            // the joker changed from moving piece to non moving piece
            incrementJokerMovingPieces(-1);
        if(newPiece != BOMB && (previousPiece == BOMB || previousPiece == (char) 0 ))
            // the joker changed from non moving piece to moving piece
            incrementJokerMovingPieces(1);
    }
}