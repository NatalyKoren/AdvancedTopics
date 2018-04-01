/*
 * MoveUnitTest.cpp
 *
 *      Author: DELL
 */
#include "MoveUnitTest.h"

int testParseLine(){
	bool result;
	Move move(FIRST_PLAYER);
	std:: string line = "1 2 3 4 J 5 6 S \n";
	result = move.parseLine(line);
	move.printMove();
	if(!result)
		return 1;
	std:: string line2 =  " 10 9	8 7 ";
	result = move.parseLine(line2);
	move.printMove();
	if(!result)
		return 2;
	std:: string line3 =  "1 2 3 4 5 6 7";
	result = move.parseLine(line3);
	if(result)
		return 3;
	std:: string line4 =  "10 9 8 7 6";
	result = move.parseLine(line4);
	if(result)
		return 4;
	return 0;
}
int testpositionBoundary(){
	Position pos(0,0);
	Move move(FIRST_PLAYER);
	if(move.positionBoundaryTest(pos) != VALID_INDEX)
		return 1;
	pos.setXposition(1);
	pos.setYposition(-1);
	if(move.positionBoundaryTest(pos) == VALID_INDEX)
		return 2;
	pos.setXposition(10);
	pos.setYposition(5);
	if(move.positionBoundaryTest(pos) == VALID_INDEX)
		return 3;
	pos.setXposition(9);
	pos.setYposition(9);
	if(move.positionBoundaryTest(pos) != VALID_INDEX)
		return 4;
	return 0;

}
int testJokerValidChange(){
	Move move(FIRST_PLAYER);
	GameBoard board;
	board.addPieceToGame(FIRST_PLAYER, 'b', Position(4,5));
	move.parseLine("1 2 3 4 J 5 6 S \n");
	if(move.testForJokerValidChange(&board)!= VALID_MOVE)
		return 1;
	move.parseLine("1 2 3 4 J 5 6 B \n");
	if(move.testForJokerValidChange(&board)!= VALID_MOVE)
		return 2;
	move.parseLine("1 2 3 4 J 5 6 N \n");
	if(move.testForJokerValidChange(&board)== VALID_MOVE)
		return 3;
	move.parseLine("1 2 3 4 J 5 6 K \n");
	if(move.testForJokerValidChange(&board)== VALID_MOVE)
		return 3;

	board.addPieceToGame(SECOND_PLAYER, 's', Position(6,6));
	move.parseLine("1 2 3 4 J 7 7 S \n");
	if(move.testForJokerValidChange(&board)== VALID_MOVE)
		return 4;
	// joker position does not contain a joker piece
	board.addPieceToGame(FIRST_PLAYER, 'B', Position(0,0));
	move.parseLine("1 2 3 4 J 1 1 R \n");
	if(move.testForJokerValidChange(&board)== VALID_MOVE)
		return 5;

	return 0;
}
int testValidMove(){
	// try to move empty position
	Move move(FIRST_PLAYER);
	GameBoard board;
	if(move.parseLine("1 2 3 4 \n") == ILLEGAL_LINE_FORMAT)
		return 1;
	if(move.checkMove(&board) == VALID_MOVE)
		return 2;
	board.addPieceToGame(SECOND_PLAYER, ROCK, Position(0,1));
	if(move.checkMove(&board) == VALID_MOVE)
		return 3;
	if(move.parseLine("7 8 9 9 \n") == ILLEGAL_LINE_FORMAT)
		return 4;
	board.addPieceToGame(FIRST_PLAYER, ROCK, Position(6,7));
	if(move.checkMove(&board) != VALID_MOVE)
		return 5;
	// try to move to occupied position
	board.addPieceToGame(FIRST_PLAYER, ROCK, Position(8,8));
	if(move.checkMove(&board) == VALID_MOVE)
		return 6;
	if(move.parseLine("1 1 5 5 \n") == ILLEGAL_LINE_FORMAT)
		return 7;
	// try to move a non moving piece
	board.addPieceToGame(FIRST_PLAYER, BOMB, Position(0,0));
	if(move.checkMove(&board) == VALID_MOVE)
		return 8;
	if(move.parseLine("2 2 5 5 \n") == ILLEGAL_LINE_FORMAT)
		return 9;
	// try to move a non moving piece
	board.addPieceToGame(FIRST_PLAYER, FLAG, Position(1,1));
	if(move.checkMove(&board) == VALID_MOVE)
		return 10;
	return 0;
}
