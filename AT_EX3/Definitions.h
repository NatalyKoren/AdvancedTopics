/*
 * Definitions.h
 *
 *  Created on: 25 Apr 2018
 *      Author: admin
 */

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#define M (10)
#define N (10)
#define R (2)
#define P (5)
#define S (1)
#define B (2)
#define J (2)
#define F (1)

#define FIRST_PLAYER  (1)
#define SECOND_PLAYER (2)
# define TIE          (0)
# define NONE (-1)
// Pieces chars
#define ROCK     'R'
#define SCISSORS 'S'
#define PAPER    'P'
#define BOMB     'B'
#define JOKER    'J'
#define FLAG     'F'
#define EMPTY_CHAR ((char)0)
#define UNKNOWN_PIECE 'X'
#define MOVING_PIECE 'M'
#define NUM_OF_DIFF_PIECES (6)
#define BOARD1	"player1.rps_board"
#define BOARD2	"player2.rps_board"
#define MOVES1	"player1.rps_moves"
#define MOVES2	"player2.rps_moves"
#define OUTPUT	"rps.output"

#define ERROR (1)
#define SUCCESS (0)
#define MISSING_INPUT_FILE (-1)

#define DEFAULT_THREADS_NUM (4)
#define GAMES_COUNT (30)
#define WINNING_POINTS (3)
#define TIE_POINTS (1)

enum GameMessage {ILLEGAL_LINE_FORMAT,
				  VALID_LINE_FORMAT,
				  INDEX_OUT_OF_BOUND,
				  VALID_INDEX,
				  ILLEGAL_MOVE,
				  VALID_MOVE,
	              FILE_PLAYER,
				  AUTO_PLAYER,
				  MOVING_VECTOR,
				  NON_MOVING_VECTOR};

enum Reason {	FLAG_CAPTURED,
				ALL_MOVING_PIECES_EATEN,
				TIE_GAME_OVER,
				TIE_BOTH_FLAGS_CAPTURED,
				BAD_POSITIONING,
				BOTH_PLAYERS_BAD_POSITIONING,
				BAD_MOVE};

enum MoveDirection{
	UP=0, DOWN=1, LEFT=2, RIGHT=3
};

#endif /* DEFINITIONS_H_ */
