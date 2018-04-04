/*
 * Definitions.h
 *
 *      Author: DELL
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
#define PIECE_COUNT   (13)
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
#define BOARD1	"player1.rps_board"
#define BOARD2	"player2.rps_board"
#define MOVES1	"player1.rps_moves"
#define MOVES2	"player2.rps_moves"
#define OUTPUT	"rps.output"

#define ERROR (1)
#define SUCCESS (0)

enum GameMessage {ILLEGAL_LINE_FORMAT,
				  VALID_LINE_FORMAT,
				  INDEX_OUT_OF_BOUND,
				  VALID_INDEX,
				  ILLEGAL_MOVE,
				  VALID_MOVE};



#endif /* DEFINITIONS_H_ */
