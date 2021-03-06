/*
 * game_board_unit_test.cpp
 *
 *      Author: DELL
 */

#include "GameBoardUnitTest.h"

int testFight(){
	GameBoard board;
	// TEST 1
	if(!fightTest(0,0,SCISSORS,ROCK,SECOND_PLAYER, board))
		return 1;
	// TEST 2
	if(!fightTest(3,4,SCISSORS,PAPER,FIRST_PLAYER, board))
		return 2;
	// TEST 3
	if(!fightTest(7,9,SCISSORS,SCISSORS,TIE, board))
		return 3;
	// TEST 4
	if(!fightTest(8,8,SCISSORS,FLAG,FIRST_PLAYER, board))
		return 4;
	// TEST 5
	if(!fightTest(6,5,SCISSORS,BOMB,TIE, board))
		return 5;
	// TEST 6
	if(!fightTest(3,3,ROCK,PAPER,SECOND_PLAYER, board))
		return 6;
	// TEST 7
	if(!fightTest(2,2,ROCK,'s',FIRST_PLAYER, board))
		return 7;
	// TEST 8
	if(!fightTest(3,5,PAPER,'s',SECOND_PLAYER, board))
		return 8;
	// TEST 9
	if(!fightTest(3,4,BOMB,'b',TIE, board))
		return 9;
	return 0;
}
bool fightTest(int x, int y, char first, char second, int shouldWin, GameBoard& board){
	int winner;
	Position pos(x,y);
	board.addPieceToGame(FIRST_PLAYER, first, pos);
	board.addPieceToGame(SECOND_PLAYER, second, pos);
	winner = board.fight(pos);
	if(winner != shouldWin) return false;
	else return true;
}

int testIsFight(){
	GameBoard board;
	// TEST 1
	if(!isFightTest(0,0,SCISSORS,ROCK, board))
		return 1;
	// TEST 2
	if(!isFightTest(1,1,'s',PAPER, board))
		return 2;
	// TEST 3
	if(isFightTest(2,2,char(0),ROCK, board))
		return 3;
	// TEST 4
	if(isFightTest(3,3,char(0),char(0), board))
		return 4;
	return 0;
}
bool isFightTest(int x, int y, char first, char second, GameBoard& board){
	Position pos(x,y);
	board.addPieceToGame(FIRST_PLAYER, first, pos);
	board.addPieceToGame(SECOND_PLAYER, second, pos);
	return board.isFight(FIRST_PLAYER, pos) && board.isFight(SECOND_PLAYER, pos);
}
int testUpdateAfterMove(){
	Move move(FIRST_PLAYER);
	GameBoard board;
	Position src(0,0);
	Position dst(1,1);
	Position jokerPos(3,3);
	int numOfMovingJoker;
	board.addPieceToGame(SECOND_PLAYER, PAPER, dst);
	numOfMovingJoker = createBoardAfterMove(src, dst, jokerPos,SCISSORS, true,'r', 's', board, move);

	if(board.getPieceAtPosition(FIRST_PLAYER, src) != (char) 0)
		return 1;
	if(board.getPieceAtPosition(FIRST_PLAYER, dst) != SCISSORS)
		return 2;
	if(board.getPieceAtPosition(SECOND_PLAYER, dst) != (char) 0)
		return 3;
	if(board.getPieceAtPosition(FIRST_PLAYER, jokerPos) != 'r')
		return 4;
	if(numOfMovingJoker != board.getJokerMovingPiece(FIRST_PLAYER))
		return 5;

	Position src2(3,3);
	Position dst2(5,7);
	Position jokerPos2(9,9);
	numOfMovingJoker = createBoardAfterMove(src2, dst2, jokerPos2,(char)0,true,'b', 'r', board, move);
	if(board.getPieceAtPosition(FIRST_PLAYER, dst2) != 'r')
		return 6;
	if(board.getPieceAtPosition(FIRST_PLAYER, src2) != (char) 0)
		return 7;
	if(board.getPieceAtPosition(FIRST_PLAYER, jokerPos2) != 'b')
		return 8;
	if(numOfMovingJoker != board.getJokerMovingPiece(FIRST_PLAYER)+1)
		return 9;

	Position src3(5,7); // there is a joker rock in here
	Position dst3(7,7);
	board.addPieceToGame(SECOND_PLAYER, PAPER, dst3);
	numOfMovingJoker = createBoardAfterMove(src3, dst3, jokerPos,(char)0,false,(char)0,(char)0, board, move);
	if(board.getPieceAtPosition(FIRST_PLAYER, dst3) != (char)0)
		return 10;
	if(board.getPieceAtPosition(FIRST_PLAYER, src3) != (char) 0)
		return 11;
	if(board.getPieceAtPosition(SECOND_PLAYER, dst3) != PAPER)
		return 12;
	if(!compareBoardExceptPos(src3,board))
		return 13;
	if(numOfMovingJoker != board.getJokerMovingPiece(FIRST_PLAYER)+1)
		return 14;

	Move move2(SECOND_PLAYER);
	Position src4(7,7);
	Position dst4(4,9);
	Position jok(3,4);
	board.addPieceToGame(FIRST_PLAYER, ROCK, dst3);
	numOfMovingJoker = createBoardAfterMove(src4, dst4, jok,(char)0,true,'p','s', board, move2);
	if(board.getPieceAtPosition(SECOND_PLAYER, dst4) != PAPER)
		return 15;
	if(board.getPieceAtPosition(SECOND_PLAYER, src4) != (char) 0)
		return 16;
	if(board.getPieceAtPosition(FIRST_PLAYER, dst4) != (char) 0)
		return 17;
	if(board.getPieceAtPosition(SECOND_PLAYER, jok) != 'p')
		return 18;
	if(numOfMovingJoker != board.getJokerMovingPiece(SECOND_PLAYER))
		return 19;


	return 0;
}
int createBoardAfterMove(Position& src, Position& dst, Position& jokerPos, char addToSrc,
		bool isJokerUpdated, char newJoker, char oldJoker, GameBoard& board, Move& move){
	int numOfMovingJoker;
	if(addToSrc != (char)0)
		board.addPieceToGame(move.getPlayer(), addToSrc, src);
	if(isJokerUpdated)
		board.addPieceToGame(move.getPlayer(), oldJoker, jokerPos);
	createMove(move, src, dst, isJokerUpdated, jokerPos, newJoker);
	numOfMovingJoker = board.getJokerMovingPiece(move.getPlayer());
	board.updateBoardAfterMove(move);
	return numOfMovingJoker;
}
void createMove(Move& move, Position src, Position dst, bool isJokerUpdated, Position jokerPos, char jokerChar){
	move.setSrcPosition(src);
	move.setDstPosition(dst);
	move.setJokerChar(jokerChar);
	move.setJokerPosition(jokerPos);
	move.setJokerUpdated(isJokerUpdated);
}

bool compareBoardExceptPos(Position& pos, GameBoard& board){
	int i,j;
	char first,second;
	for(i=0; i< N; i++){
		for(j=0; j< M; j++){
			if(i != pos.getXposition() || j != pos.getYposition()){
				first = board.getPieceAtPosition(FIRST_PLAYER, pos);
				second = board.getPieceAtPosition(SECOND_PLAYER, pos);
				if(first != second)
					return false;
			}
		}
	}
	return true;
}

int testVictory(){
	GameBoard board;
	// first player
	board.addPieceToGame(FIRST_PLAYER, ROCK, Position(1,1));
	board.addPieceToGame(FIRST_PLAYER, SCISSORS, Position(1,2));
	board.addPieceToGame(FIRST_PLAYER, PAPER, Position(1,3));
	board.addPieceToGame(FIRST_PLAYER, FLAG, Position(1,4));
	board.addPieceToGame(FIRST_PLAYER, BOMB, Position(1,5));
	board.addPieceToGame(FIRST_PLAYER, ROCK, Position(1,6));
	// second player
	board.addPieceToGame(SECOND_PLAYER, ROCK, Position(2,1));
	board.addPieceToGame(SECOND_PLAYER, PAPER, Position(2,2));
	board.addPieceToGame(SECOND_PLAYER, PAPER, Position(2,3));
	board.addPieceToGame(SECOND_PLAYER, FLAG, Position(2,4));
	board.addPieceToGame(SECOND_PLAYER, BOMB, Position(2,5));
	board.addPieceToGame(SECOND_PLAYER, ROCK, Position(2,6));
	if(board.checkVictory(FIRST_PLAYER, false) != NONE)
		return 1;
	// second player wins - flag piece
	Position pos(1,4);
	board.updateAfterLoseFight(FIRST_PLAYER, pos);
	if(board.checkVictory(FIRST_PLAYER, false) != SECOND_PLAYER)
		return 2;
	board.addPieceToGame(FIRST_PLAYER, FLAG, pos);
	// first player wins -flag piece
	Position pos1(2,4);
	board.updateAfterLoseFight(SECOND_PLAYER, pos1);
	if(board.checkVictory(FIRST_PLAYER, false) != FIRST_PLAYER)
		return 3;
	board.addPieceToGame(SECOND_PLAYER, FLAG, pos1);
	// second player wins - moving pieces
	pos.setYposition(1);
	board.updateAfterLoseFight(FIRST_PLAYER, pos);
	pos.setYposition(2);
	board.updateAfterLoseFight(FIRST_PLAYER, pos);
	pos.setYposition(3);
	board.updateAfterLoseFight(FIRST_PLAYER, pos);
	if(board.checkVictory(FIRST_PLAYER, false) != NONE)
		return 4;
	pos.setYposition(6);
	board.updateAfterLoseFight(FIRST_PLAYER, pos);
	if(board.checkVictory(FIRST_PLAYER, false) != SECOND_PLAYER)
		return 5;
	board.addPieceToGame(FIRST_PLAYER, ROCK, Position(1,6));
	if(board.checkVictory(FIRST_PLAYER, false) != NONE)
		return 5;
	// first player wins - moving pieces
	pos.setXposition(2);
	pos.setYposition(1);
	board.updateAfterLoseFight(SECOND_PLAYER, pos);
	pos.setYposition(2);
	board.updateAfterLoseFight(SECOND_PLAYER, pos);
	pos.setYposition(3);
	board.updateAfterLoseFight(SECOND_PLAYER, pos);
	if(board.checkVictory(FIRST_PLAYER, false) != NONE)
		return 6;
	pos.setYposition(6);
	board.updateAfterLoseFight(SECOND_PLAYER, pos);
	if(board.checkVictory(FIRST_PLAYER, false) != FIRST_PLAYER)
		return 7;
	return 0;
}

int testValidMove(){
    // try to move empty position
    Move move(FIRST_PLAYER);
    GameBoard board;
    if(move.parseLine("1 2 1 3 \n") == ILLEGAL_LINE_FORMAT)
        return 1;
    if(board.checkMove(move) == VALID_MOVE)
        return 2;
    board.addPieceToGame(SECOND_PLAYER, ROCK, Position(0,1));
    if(board.checkMove(move) == VALID_MOVE)
        return 3;
    if(move.parseLine("9 8 9 9 \n") == ILLEGAL_LINE_FORMAT)
        return 4;
    board.addPieceToGame(FIRST_PLAYER, ROCK, Position(8,7));
    if(board.checkMove(move) != VALID_MOVE)
        return 5;
    // try to move to occupied position
    board.addPieceToGame(FIRST_PLAYER, ROCK, Position(8,8));
    if(board.checkMove(move) == VALID_MOVE)
        return 6;
    if(move.parseLine("1 1 1 2 \n") == ILLEGAL_LINE_FORMAT)
        return 7;
    // try to move a non moving piece
    board.addPieceToGame(FIRST_PLAYER, BOMB, Position(0,0));
    if(board.checkMove(move) == VALID_MOVE)
        return 8;
    if(move.parseLine("2 2 2 3 \n") == ILLEGAL_LINE_FORMAT)
        return 9;
    // try to move a non moving piece
    board.addPieceToGame(FIRST_PLAYER, FLAG, Position(1,1));
    if(board.checkMove(move) == VALID_MOVE)
        return 10;
	board.addPieceToGame(FIRST_PLAYER, SCISSORS, Position(5,5));
	board.addPieceToGame(FIRST_PLAYER, 's', Position(3,3));
	if(move.parseLine("6 6 6 7 J: 4 4 R\n") == ILLEGAL_LINE_FORMAT)
		return 11;
	if(board.checkMove(move) != VALID_MOVE)
		return 12;


    return 0;
}
int testJokerValidChange(){
	Move move(FIRST_PLAYER);
	GameBoard board;
	board.addPieceToGame(FIRST_PLAYER, 'b', Position(4,5));
	move.parseLine("1 2 3 4 J: 5 6 S \n");
	if(board.testForJokerValidChange(move)!= VALID_MOVE)
		return 1;
	move.parseLine("1 2 3 4 J: 5 6 B \n");
	if(board.testForJokerValidChange(move)!= VALID_MOVE)
		return 2;
	move.parseLine("1 2 3 4 J: 5 6 N \n");
	if(board.testForJokerValidChange(move)== VALID_MOVE)
		return 3;
	move.parseLine("1 2 3 4 J: 5 6 K \n");
	if(board.testForJokerValidChange(move)== VALID_MOVE)
		return 4;

	board.addPieceToGame(SECOND_PLAYER, 's', Position(6,6));
	move.parseLine("1 2 3 4 J: 7 7 S \n");
	if(board.testForJokerValidChange(move)== VALID_MOVE)
		return 5;
	// joker position does not contain a joker piece
	board.addPieceToGame(FIRST_PLAYER, 'B', Position(0,0));
	move.parseLine("1 2 3 4 J: 1 1 R \n");
	if(board.testForJokerValidChange(move)== VALID_MOVE)
		return 6;

	return 0;
}
int testExecMove(){
	std::string line = "1 1 1 2 J: 3 3 R";
	GameBoard board;
	Position pos(0,0);
	Move move(FIRST_PLAYER);
	board.addPieceToGame(FIRST_PLAYER, SCISSORS, Position(0,0));
	board.addPieceToGame(SECOND_PLAYER, PAPER, Position(0,1));
	board.addPieceToGame(FIRST_PLAYER, 'p', Position(2,2));
	if(board.execMove(line, move) != SUCCESS)
		return 1;
	if(board.getPieceAtPosition(FIRST_PLAYER, pos)!=(char)0)
		return 2;
	pos.setYposition(1);
	if(board.getPieceAtPosition(FIRST_PLAYER, pos)!=SCISSORS)
		return 3;
	if(board.getPieceAtPosition(SECOND_PLAYER, pos)!=(char)0)
		return 4;
	pos.setXposition(2);
	pos.setYposition(2);
	if(board.getPieceAtPosition(FIRST_PLAYER, pos)!='r')
		return 5;

	board.addPieceToGame(FIRST_PLAYER, ROCK, Position(5,5));
	board.addPieceToGame(SECOND_PLAYER, BOMB, Position(5,6));
	board.addPieceToGame(FIRST_PLAYER, 'r', Position(4,4));
	std::string line2 = "6 6 6 7 J: 5 5 B";
	if(board.execMove(line2, move) != SUCCESS)
		return 6;
	pos.setXposition(5);
	pos.setYposition(5);
	if(board.getPieceAtPosition(FIRST_PLAYER, pos)!=(char)0)
		return 7;
	pos.setYposition(6);
	if(board.getPieceAtPosition(FIRST_PLAYER, pos)!=(char)0)
		return 8;
	if(board.getPieceAtPosition(SECOND_PLAYER, pos)!=(char)0)
		return 9;
	pos.setXposition(4);
	pos.setYposition(4);
	if(board.getPieceAtPosition(FIRST_PLAYER, pos)!='b')
		return 10;
    return 0;

}