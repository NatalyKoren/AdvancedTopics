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
	int pieceCount[NUM_OF_DIFF_PIECES];
	Position curPos;
	char curPiece;

public:
	///-----------Board file--------------



	//Initialises the field pieceCount according to the number of each piece provided in Definitions.h
	void initializePieceCount();

	// verifies that the number of each piece is legal
	// @return value: SUCCESS if ok, ERROR otherwise
	int checkPieces();

	//@param: piece char parsed from line
	// updates pieceCount, an array that counts the pieces
	// calls checkPieces to verify that there aren't too many pieces of one type
	// @return value: SUCCESS if piece is ok, ERROR if not one of the game's pieces
	int checkAndUpdatePieceChar (const char& piece);

	/*
	 * @param: (x,y) from file
	 *  verifies that the position specified is within index
	 *  @return value: SUCCESS if ok, ERROR otherwise
	 */
	int checkPos(int x, int y);

	//checks if there's a whitespace line in the file
	bool isLineContainWhiteSpaceOnly(std::string line);

	// @param: line from file
	// checks the syntax (length, types etc.)
	// @return value: a valid PiecePosition if ok, an invalid one otherwise
	unique_ptr<InterfacePiecePosition> parseBoardLine (const char* line);

	///-----------End of board file parsing--------------


	///-----------Move file--------------

	/*
	 * gets the line from the moves file to parse move and joker change
	 * returns an empty line if can't read from the file
	 */
	const char* getMovesLine();

	///-----------End of Move file parsing--------------

	/*
	 * Interface methods
	 */
    // should parse a file? or inside the constructor or in getInitialPositions
    FilePlayerAlgorithm(int playerNum);
    // In case of an error in positioning file: put (char)0 in 'piece' field of InterfacePiecePosition class.
    virtual void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill);
    // don't need implementation for file player - Does not important
    virtual void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights);
    virtual void notifyOnOpponentMove(const Move& move); // called only on opponents move
    virtual void notifyFightResult(const FightInfo& fightInfo); // called only if there was a fight
    virtual unique_ptr<Move> getMove();
    virtual unique_ptr<JokerChange> getJokerChange(); // nullptr if no change is requested
};



#endif //AT_EX2_FILEPLAYERALGORITHM_H
