#include <iostream>
#include <fstream>

class ParseBoard {
  int pieceCount = {R, P, S, B, J, F};
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

  //TODO:
  //1. update boards
  //2. verify that no 2 pieces of same player share a spot
};
