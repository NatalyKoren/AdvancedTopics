//
// Created by DELL on 25/04/2018.
//

#ifndef AT_EX2_GAMEMANAGER_H
#define AT_EX2_GAMEMANAGER_H

#include "GameBoard.h"
#include "PlayerAlgorithm.h"
#include "Definitions.h"
#include "FilePlayerAlgorithm.h"
#include "AutoPlayerAlgorithm.h"

class GameManager{
    GameBoard game;
    int currentPlayer;
    std::unique_ptr<PlayerAlgorithm> firstPlayerAlgorithm;
    std::unique_ptr<PlayerAlgorithm> secondPlayerAlgorithm;
public:
    // --- Constructor ---
    GameManager(int firstPlayerType,int secondPlayerType);
    /**
     * calls getInitialPositions of both players.
     * Then updates the PiecePosition vector in game board.
     * If there is an error in one or more of the initial positions, the function updates the game winner
     * and reason accordingly.
     * @return ERROR is case of an error in one of more positions vectors. SUCCESS otherwise.
     */
    int updateInitialPositions();
    /***
     * Update player boards with vectorToUpdate data.
     * @param player - player board  to update
     * @param vectorToUpdate - the PiecePosition data
     * @return ERROR in case of an error in vectorToUpdate. It indicates an error in the parsing file.
     * SUCCESS in case of success.
     */
    int updatePositionsOnBoard(int player, std::vector<unique_ptr<PiecePosition>>& vectorToUpdate);
    //
    //
    /***
     * Perform all fights after initial boards. Updates fights vector with fights.
     * Return if there is a winner after the initial stage.
     * @param fights - vector to be updated after every fight.
     * @return TIE/FIRST_PLAYER/SECOND_PLAYER in case there is a winner ofter the initial stage.
     * Return NONE in case there is not a winner after this stage.
     */
    int performAllFightAfterInitBoards(std::vector<unique_ptr<FightInfo>>& fights);


    /***
     * After the initial stage starting to play the game.
     */
    void playGame();

    void notifyToPlayerOnFightResults(int currentPlayer, const GameFightInfo& currentFight) const;

    unique_ptr<JokerChange> getJokerChangeFromPlayer(int player) const;
    unique_ptr<Move> getMoveFromPlayer(int player) const;
    void notifyToPlayerAfterOpponentsMove(int playerToNotify, const Move& move) const;
    /***
     * Run the game from the baginning.
     * @return
     */
    int startAndRunGame();
    /***
     * Write game results to output file.
     * @return ERROR in case an error occured during the write. SUCCESS otherwise.
     */
    int writeToOutput();
    /***
    * Print reason to output file
    * The function assumes the output file is opened for writing
    * @param output - output file to write
    * @param reason - the reason to write to output file
    * @param winner - the winner of the game: first player, seconf player or a tie.
    * @return ERROR if an error occurred. SUCCESS otherwise.
    */
    int printReasonToOutputFile(std::ofstream& output, int reason, int winner) const;

	/***
	 * Test is new joker representation is a valid representation for joker.
	 * @param newJokerRep - char to be tested.
	 * @return true if newJokerChar is a valid joker representation and false otherwise.
	 * valid representation is: BOMB, SCISSORS, ROCK, PAPER.
	 */
	bool isJokerValidChar (char newJokerRep) const;


};


#endif //AT_EX2_GAMEMANAGER_H
