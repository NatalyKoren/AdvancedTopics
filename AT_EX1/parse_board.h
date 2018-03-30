#ifndef PARSEBOARD_H_
#define PARSEBOARD_H_

#include <iostream>
#include <fstream>
#include "Position.h"
#include "Definitions.h"
#include "GameBoard.h"


class ParseBoard {
  int pieceCount[6] = {R, P, S, B, J, F};
  int curPlayer;
  int curLine;

public:
  // @param: board file
  // gets line, checks format, calls all aiding functions
  // @return value: 0 if correct, player# if error
  int parseBoardFile (std::string filename);

  // @param: line from file
  // checks the syntax (<>, length, etc.)
  // @return value: 0 if correct, line# if error
  int checkLine (std::string line);

  //@param: line from file
  // updates pieceCount, an array that counts the pieces
  void updatePieceCount (std::string line);

  //verifies that the number of each piece is legal
  // @return value: 0 if ok, player# otherwise
  int checkPieces();

  /*
   * @param: the game board, line from file
   *  verifies that the position specified is within index and free
   *  @return value: 0 if ok, player# otherwise
   */
  int checkPos(GameBoard& board, std::string line);

  /*
   * @param: game board, cur player, piece, position
   * assumes that the update request is valid
   * updates the board
   */
  void updateBoard(GameBoard& board, int player, char piece, Position& pos);
};

#endif /* PARSEBOARD_H_ */
