/*
 * game_board.h
 *
 *      Author: DELL
 */

#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_
#include "Move.h"
#include "Position.h"
#include "Definitions.h"
#include "PlayerPieces.h"
class Move;
class GameBoard{
	char firstPlayerBoard[N][M] = { {0} };
	char secondPlayerBoard[N][M] = { {0} };
	PlayerPieces firstPlayerPieces;
	PlayerPieces secondPlayerPieces;
public:
	/***
	 * Constructor
	 * Init first player pieces and second player pieces to zero.
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
	 * Check if first player or second player won the game.
	 * return:
	 *  TIE - in case of a tie,
	 *  FIRST_PLAYER - first player wins
	 *  SECOND_PLAYER - second  player wins
	 */
	int checkVictory();
	/***
	 * The function receives a valid move and updates the boards accordingly.
	 * In a case of a fight - the function will update the boards and players pieces
	 * according to the fight result.
	 * If the move is updating a joker piece, then the function will also update the new
	 * joker representation on player's board.
	 */
	void updateBoardAfterMove(int player, Move* move);
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
		return (player == FIRST_PLAYER)? SECOND_PLAYER:FIRST_PLAYER;
	}
	/***
	 * increase pieces char number of player by num.
	 * num can be a negative number.
	 */
	void increasePieceNum(int player, char piece, int num);
	/***
	 * update game board after player is loosing a fight.
	 * Updated data:
	 * player's game board at position pos will be set to zero.
	 * Player's piece that was eaten would be decreased from player pieces.
	 */
	void updateAfterLoseFight(int player, Position& pos);
	/***
	 * Add piece to game board of a player.
	 * Char piece - assuming that regular piece is upper case piece
	 * and a joker piece is lower case piece.
	 * Updated data:
	 * update position on player's board with 'piece'
	 * increase player 'piece' by 1.
	 */
	void addPieceToGame(int player, char piece, Position pos);
	/***
	 * return true if pos doesn't contain a player piece.
	 */
	bool isEmpty(int player, Position& pos);
	/**
	 * for tests
	 */
	int getJokerMovingPiece(int player);

	int testForJokerValidChange(Move& move);

	int checkMove(Move& move);

	/*
	 * return True if there was a fight
	 * updates the board if necessary
	 */
	bool checkAndRunFight(int player, Position& dstPos);

};


#endif /* GAMEBOARD_H_ */
