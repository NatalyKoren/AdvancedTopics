//
// Created by DELL on 25/04/2018.
//

#ifndef AT_EX2_GAMEMANAGER_H
#define AT_EX2_GAMEMANAGER_H

#include "GameBoard.h"
#include "PlayerAlgorithm.h"
#include "Definitions.h"
#include "PlayerPieces.h"


class GameManager{
    GameBoard game;
    int currentPlayer;
    std::unique_ptr<PlayerAlgorithm> firstPlayerAlgorithm;
    std::unique_ptr<PlayerAlgorithm> secondPlayerAlgorithm;
    int pieceCount[NUM_OF_DIFF_PIECES];
public:
    // --- Constructors ---
    GameManager(): game(), currentPlayer(FIRST_PLAYER) {initializePieceCount();}

	/***
	 * Initialises the field pieceCount according to the number of each piece provided in Definitions.h
	 */
	void initializePieceCount();

	 // --- Setters for the player algorithms ---
	void setFirstPlayerAlgorithm(std::unique_ptr<PlayerAlgorithm> firstAlgo) {firstPlayerAlgorithm = std::move(firstAlgo);}
	void setSecondPlayerAlgorithm(std::unique_ptr<PlayerAlgorithm> secondAlgo) {secondPlayerAlgorithm = std::move(secondAlgo);}

	/***
	 * Verifies that the number of each piece is legal
	 * @return SUCCESS if ok, ERROR otherwise
	 */
	int checkPieces();

	/***
	 * updates pieceCount, an array that counts the pieces
	 * @param piece - char parsed from line
	 * @return SUCCESS if piece is ok, ERROR if not one of the game's pieces.
	 */
	int checkAndUpdatePieceChar (const char& piece);

	/***
	 * Check if player can position pieceType at position posToCheck.
	 * Checks that pieceType is a valid piece representation and that posToCheck is not occupied on board.
	 * @param posToCheck - position for adding piece
	 * @param pieceType - the piece type player wishes to add.
	 * @param player - player that wants to add pieceType to posToCheck position
	 * @return ERROR in case of invalid char type or position occupied. SUCCESS otherwise.
	 */
	int checkInitialPosition(const Point& posToCheck, char pieceType, int player);

    /**
     * calls getInitialPositions of both players.
     * Then updates the PiecePosition vector in game board.
     * If there is an error in one or more of the initial positions, the function updates the game winner
     * and reason accordingly.
     * @return ERROR is case of an error in one of more positions vectors. SUCCESS otherwise.
     */
    int updateInitialPositions();

    /***
     * Update player board with vectorToUpdate data.
     * @param player - player board  to update
     * @param vectorToUpdate - the PiecePosition data
     * @return ERROR in case of an error in vectorToUpdate. SUCCESS in case of success.
     */
    int updatePositionsOnBoard(int player, std::vector<unique_ptr<PiecePosition>>& vectorToUpdate);

    /***
     * Performs all fights after initial boards. Updates fights vector with fights.
     * Return if there is a winner after the initial stage.
     * @param fights - vector to be updated after every fight.
     * @return TIE/FIRST_PLAYER/SECOND_PLAYER in case there is a winner ofter the initial stage.
     * Return NONE in case there is not a winner after this stage.
     */
    int performAllFightAfterInitBoards(std::vector<unique_ptr<FightInfo>>& fights);

    /***
     * After the initial stage starting to play the game.
     * The function runs the game until reaching a winner or a tie.
     */
    void playGame();

	/***
	 * Notify to player on fight.
	 * @param currentPlayer - player to notify.
	 * @param currentFight - the fight to notify player.
	 */
    void notifyToPlayerOnFightResults(int currentPlayer, const GameFightInfo& currentFight) const;

	/***
	 * Get the joker change from player.
	 * @param player - player to ask for joker change.
	 * @return the joker change of player on the current move.
	 * nullptr in case there is not a joker change.
	 */
    unique_ptr<JokerChange> getJokerChangeFromPlayer(int player) const;

	/***
	 * Get the next move from player.
	 * @param player - player to ask for the next move.
	 * @return next move of player to be performed.
	 */
    unique_ptr<Move> getMoveFromPlayer(int player) const;

	/***
	 * notify to player after his opponents move.
	 * @param playerToNotify - player to be notified.
	 * @param move - the move to be notified to player.
	 */
    void notifyToPlayerAfterOpponentsMove(int playerToNotify, const Move& move) const;

    /***
     * Run the entire game from the beginning. Does not write to output file.
     * @return The winner of the game.
     */
    int startAndRunGame();

    /***
     * Writes game results to output file.
     * @return ERROR in case an error occurred during the write. SUCCESS otherwise.
     */
    int writeToOutput() const;

    /***
    * Print reason to output file
    * The function assumes the output file is opened for writing
    * @param output - output file to write
    * @param reason - the reason to write to output file
    * @param winner - the winner of the game: first player, second player or a tie.
    * @return ERROR if an error occurred. SUCCESS otherwise.
    */
    int printReasonToOutputFile(std::ofstream& output, int reason, int winner) const;

};


#endif //AT_EX2_GAMEMANAGER_H
