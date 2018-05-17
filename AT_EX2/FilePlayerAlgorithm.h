//
// Created by DELL on 25/04/2018.
//

#ifndef AT_EX2_FILEPLAYERALGORITHM_H
#define AT_EX2_FILEPLAYERALGORITHM_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <cerrno>
#include "Definitions.h"
#include "PlayerAlgorithm.h"
#include "GameMove.h"
#include "InterfacePiecePosition.h"
#include <memory.h>

using std::unique_ptr;

class FilePlayerAlgorithm : public PlayerAlgorithm{
    int player;
    GameJokerChanged jokerChanged;
    std::ifstream movesFile;
	Position curPos;
	char curPiece;

public:
	// --- Constructor ---
	FilePlayerAlgorithm(int playerNum);

	//-----------Board file parsing methods--------------
	/***
	 * verifies that the position specified is within index
	 * @param x - x coordinate from file
	 * @param y - y coordinate from file
	 * @return SUCCESS if ok, ERROR otherwise
	 */
	int checkPos(int x, int y);

	/***
	 * checks if there's a whitespace line in the file
	 * @param line - line to check
	 * @return true if line contains whitespaces only and false otherwise.
	 */
	bool isLineContainWhiteSpaceOnly(std::string line);

	/***
	 * checks the syntax of a line in input file (length, types, format, bounds etc.)
	 * @param line - line from input file
	 * @return a valid PiecePosition if ok, an invalid one otherwise
	 */
	unique_ptr<InterfacePiecePosition> parseBoardLine (const char* line);

	///-----------End of board file parsing--------------

	///-----------Move file parsing methods--------------

	/***
	 * gets the line from the moves file to parse move and joker change
	 * @return an empty line if can't read from the file. Otherwise returns next line from file.
	 */
    std::string getMovesLine();

	///-----------End of Move file parsing--------------

    // --- interface methods ---
    virtual void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) override;
    // don't need implementation for file player - Does not important
    virtual void notifyOnInitialBoard(const Board& /*b*/, const std::vector<unique_ptr<FightInfo>>& /*fights*/) override { }
    virtual void notifyOnOpponentMove(const Move& /*move*/) override { } // called only on opponents move
    virtual void notifyFightResult(const FightInfo& /*fightInfo*/) override { } // called only if there was a fight
    virtual unique_ptr<Move> getMove() override;
    virtual unique_ptr<JokerChange> getJokerChange() override; // nullptr if no change is requested
};



#endif //AT_EX2_FILEPLAYERALGORITHM_H
