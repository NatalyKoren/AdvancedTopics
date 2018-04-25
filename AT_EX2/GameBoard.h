/*
 * game_board.h
 *
 *      Author: DELL
 */

#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_
#include <fstream>
#include <cctype>
#include <cerrno>
#include <cstring>
#include "Move.h"
#include "Position.h"
#include "Definitions.h"
#include "PlayerPieces.h"

class GameBoard{
	char firstPlayerBoard[N][M];
	char secondPlayerBoard[N][M];
	PlayerPieces firstPlayerPieces;
	PlayerPieces secondPlayerPieces;
	int winner;
	int reason;

public:
	/***
	 * Constructor
	 * Init first player pieces and second player pieces to zero.
	 */
	GameBoard();
	/***
	 * The function assumes that at pos there is a fight.
	 * Returns the winner of the fight or tie, without changing the board game.
	 * @param pos - the fight position.
	 * @return 0 - Tie, FIRST_PLAYER if first player wins, else return SECOND_PLAYER.
	 */
	int fight(Position& pos) const;
	/***
	 * Check if there is a fight for playerToCheck.
	 * The function need to check if pos is occupied by playerToCheck piece.
	 *return: true if there is a fight and false otherwise.
	 * @param playerToCheck - the player that we want to check if there is a fight against him.
	 * @param pos - the position to check.
	 * @return - true if there is a fight and false otherwise.
	 */
	bool isFight(int playerToCheck, Position& pos) const;
	/***
	 * Check the board for a winner.
	 * @param curPlayer - determines the order of checking if moving pieces are gone
	 * @param initStage - true if we check victory after the init boards stage and false otherwise
	 * @return FIRST_PLAYER - first player wins - eat all opponents flags or all moving pieces.
	 * SECOND_PLAYER - second  player wins.
	 * TIE - both flags eaten, non moving pieces to both players.
	 * NONE - there is no winner.
	 * In case of a winner or a TIE, winner and reason are updated accordingly.
	 */
	int checkVictory(int curPlayer, bool initStage);
	/***
	 * The function receives a valid move and updates the boards accordingly.
	 * In a case of a fight - the function will update the boards and players pieces
	 * according to the fight result.
	 * If the move is updating a joker piece, then the function will also update the new
	 * joker representation on player's board.
	 * @param move - the move to be updated on board.
	 */
	void updateBoardAfterMove(Move& move);
	/***
	 * Return player piece at position.
	 * @param player -  the player that we want his piece on board.
	 * @param pos - the position on board
	 * @return the char at position pos at player's board.
	 */
	char getPieceAtPosition(int player, Position& pos) const;
	/***
	 * set player's piece at position with 'piece' character.
	 * @param player  - player's board to be updated.
	 * @param piece - piece to update
	 * @param pos - position on player's board.
	 */
	void setPieceAtPosition(int player, char piece, Position& pos);
	/***
	 * return the opponent of a player.
	 * @param player
	 * @return SECOND_PLAYER if player is FIRST_PLAYER and FIRST_PLAYER otherwise.
	 */
	int getOpponent(int player) const{
		return (player == FIRST_PLAYER)? SECOND_PLAYER:FIRST_PLAYER;
	}
	/***
	 * increase pieces char number of player by num.
	 * num can be a negative number.
	 * @param player - the player to be updated.
	 * @param piece - the piece count that we want to update
	 * @param num - increase piece count by num
	 */
	void increasePieceNum(int player, char piece, int num);
	/***
	 * update game board after player is loosing a fight.
	 * Updated data:
	 * player's game board at position pos will be set to zero.
	 * Player's piece that was eaten would be decreased from player pieces.
	 * @param player - the player that looses the fight.
	 * @param pos - the position of the fight.
	 */
	void updateAfterLoseFight(int player, Position& pos);
	/***
	 * Add piece to game board of a player.
	 * Updated data:
	 * update position on player's board with 'piece'
	 * increase player 'piece' by 1.
	 * @param player
	 * @param piece - piece to add to game board of player. Assuming that regular piece is upper case piece,
	 * and a joker piece is lower case piece.
	 * @param pos - position that contains the piece.
	 */
	void addPieceToGame(int player, char piece, Position pos);
	/***
	 * Check if position on board contains a player piece.
	 * @param player - player to check
	 * @param pos - position to check
	 * @return - true if pos doesn't contain a player piece
	 */
	bool isEmpty(int player, Position& pos) const;
	/**
	 * for tests
	 */
	int getJokerMovingPiece(int player) const;
	/***
	 * If move contains a joker change, then the function will test is the change is a valid change.
	 * Tests: position contains a joker piece, new representation is a valid representation.
	 * @param move - move to be tested
	 * @return ILLEGAL_MOVE if the joker change is illegal change and VALID_MOVE otherwise.
	 */
	int testForJokerValidChange(Move& move) const;
	/***
	 * Test if a move is a valid move.
	 * Tests: boundary tests for src position and dst position, test if dst contains same player piece,
	 * move step is legal (only one step forward/backward/sides), src contain a moving piece, joker test.
	 * Helper function: testForJokerValidChange.
	 * @param move - the move to be tested.
	 * @return ILLEGAL_MOVE is the move is not a valid move and VALID_MOVE otherwise.
	 */
	int checkMove(Move& move);

	/***
	 * The function assumes that dstPos contains player piece. It check is dstPos also contains the opponent piece.
	 * If so, there is a fight between them. The function will run the fight and update to board accordingly.
	 * The function will only update dstPos on players boards and the pieces count.
	 * @param player - player that has a piece at dstPos
	 * @param dstPos - contains player piece.
	 * @return true if there was a fight and false otherwise.
	 */
	bool checkAndRunFight(int player, Position& dstPos);

	/***
	 * Get a move line to be parsed and execute the move on board if the move is a valid move.
	 * @param line - line containing a move to be parsed.
	 * @param move - move to bu updated according to line.
	 * @return ERROR if the move is not a valid move and SUCCESS otherwise.
	 * In case of an ERROR- move is not a valid move, winner and reason are updated accordingly.
	 */
	int execMove(std::string line, Move& move);
	// Setters
	void setWinner(int newWinner) {winner = newWinner;}
	void setReason(int newReason) {reason = newReason;}
	// Getters
	int getWinner() const{return winner;}
	int getReason() const{return reason;}
	/***
	 * Assuming move contain a valid positions on board ( not out of bound ).
	 * Check if the step in move is a valid step: only one step forward, backward, lefd side or right side.
	 * @param move - move to be checked.
	 * @return ILLEGAL_MOVE if the step is not a valid step and VALID_MOVE otherwise.
	 */
	int testForValidMovementOfBoard(Move& move);

	/***
	 * prints the state of the board to output
	 * assumes the output file is already open for writing
	 * @param output - an open file for writing
	 * @return SUCCESS if writing to file succeeded and ERROR otherwise.
	 */
	int printBoard(std::ofstream& output)const;

	/*
	 * updates the joker's params
	 * returns ERROR if invalid attempt to change joker, SUCCESS otherwise
	 */
	int updateJoker(Move& move);

};


#endif /* GAMEBOARD_H_ */
