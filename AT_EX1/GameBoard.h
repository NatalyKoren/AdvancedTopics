/*
 * game_board.h
 *
 *  Created on: 26 ���� 2018
 *      Author: DELL
 */

#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_
#include "Move.h"
#include "Position.h"
#include "Definitions.h"
#include "PlayerPieces.h"

class GameBoard{
	char firstPlayerBoard[N][M] = { {0} };
	char secondPlayerBoard[N][M] = { {0} };
	PlayerPieces firstPlayerPieces;
	PlayerPieces secondPlayerPieces;
public:
	/***
	 * Constructor
	 */
	GameBoard();
	/***
	 * The function assumes that at pos there is a fight.
	 * params:
	 * Position& pos - the fight position.
	 * return:
	 * 0 - Tie
	 * FIRST_PLAYER if first player wins.
	 * Else return SECOND_PLAYER.
	 */
	int fight(Position& pos);
	/***
	 * Check if there is a fight for playerToCheck.
	 * The function need to check if pos is occupied by playerToCheck piece.
	 * params:
	 * int playerToCheck - the player that we want to check if there is a fight againts him.
	 * Position& pos - the position to check.
	 *return: true if there is a fight and false otherwise.
	 */
	bool isFight(int playerToCheck, Position& pos);
	/***
	 * TODO
	 * return 0 - tie, 1- first player wins, 2 - second wins, -1 - no body wins.
	 */
	int checkVictory();
	/***
	 * The function receives a valid move and update the boards accordingly.
	 * If there is a fight - the function will update to boards according to
	 * the fight result.
	 * The function will update player's board according to move.
	 * In a case of a fight the opponent move will be updated as well if necessary.
	 * If the move is updating a joker piece, then the function will also update the new
	 * joker representation on player's board.
	 */
	void updateBoardAfterMove(int player, Move& move);
	/***
	 * return player piece at position.
	 */
	char getPieceAtPosition(int player, Position& pos);
	/***
	 * set player's piece at position with 'piece' character.
	 */
	void setPieceAtPosition(int player, char piece, Position& pos);
	/***
	 * return the opponent of a player.
	 */
	int getOpponent(int player){
		return (player == FIRST_PLAYER)? FIRST_PLAYER:SECOND_PLAYER;
	}
	/***
	 * increase pieces char number of player by num.
	 */
	void increasePieceNum(int player, char piece, int num);
	/***
	 * update game board after player is loosing a fight.
	 * Updated data:
	 * game board at position pos will be set to zero.
	 * TODO
	 */
	void updateAfterLoseFight(int player, Position& pos);
	/***
	 *TODO
	 */
	void addPieceToGame(int player, char piece, Position& pos);



};


#endif /* GAMEBOARD_H_ */
