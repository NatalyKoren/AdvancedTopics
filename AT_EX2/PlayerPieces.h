//
// Created by DELL on 25/04/2018.
//

#ifndef AT_EX2_PLAYERPIECES_H
#define AT_EX2_PLAYERPIECES_H

#include "Definitions.h"
#include <ctype.h>
class PlayerPieces{
    int scissors;
    int rock;
    int paper;
    int bomb;
    int flag;
    int joker;
    int numOfMovingJokers;

public:
    /***
     * The class represents the amount of a player's pieces in the game.
     */
    PlayerPieces();
    // --- Setters
    void setScissorsNum(int num){ scissors = num; }
    void setRockNum(int num){ rock = num; }
    void setPaperNum(int num){paper = num; }
    void setBombNum(int num){bomb = num; }
    void setFlagNum(int num){flag = num; }
    void setJokerNum(int num){joker = num; }
    void setNumOfMovingJoker(int num){numOfMovingJokers = num; }
    // --- Getters
    int getScissorsNum()const{ return scissors; }
    int getRockNum()const{ return rock; }
    int getPaperNum()const { return paper; }
    int getBombNum()const { return bomb; }
    int getFlagNum()const { return flag; }
    int getJokerNum()const { return joker; }
    int getNumOfMovingJoker()const {return numOfMovingJokers; }
    // --- Move pieces number
    int getMovePiecesNum() const{ return (scissors+ rock + paper + numOfMovingJokers); }
    int getPieceCount() const {return scissors+rock+paper+bomb+flag+joker;}
    // set piece to player
    /***
     * Increment piece number of a player by num. Num can be a negative num.
     * In a case of a joker, we will increment the joker num and numOfMovingJokers if necessary.
     * @param piece - the piece we want to update it's number (the amount of pieces)
     * @param num - increment piece count by num
     */
    void incrementPieceNum(char piece, int num);
    /***
     * increment the amount of joker moving pieces.
     * Usually using when the joker chnages its representation (with num = 1 or -1)
     * @param num - the amount of pieces we will add to joker amount of moving pieces.
     */
    void incrementJokerMovingPieces(int num) { numOfMovingJokers+=num; }
    /***
     * Maintain the joker moving piece amount when the joker changes its representation.
     * If the joker changes from a moving piece to non moving piece, we will decrement numOfMovingJokers
     * by 1. If the joker changes from a non moving piece to a moving piece, we will increment
     * numOfMovingJokers by 1. Otherwise, numOfMovingJokers wouldn't be changed.
     * Helper function: incrementJokerMovingPieces
     * @param previousPiece - previous joker representation
     * @param newPiece - the new joker representation
     */
    void updateJokerMovingCount(char previousPiece, char newPiece);

};





#endif //AT_EX2_PLAYERPIECES_H
