/*
 * GamePlayed.cpp
 *
 *      Author: DELL
 */

#include "GamePlayed.h"

Game::Game(): curPlayer (FIRST_PLAYER), board(), firstPlayerLine(1), secondPlayerLine(1){}

int Game::initBoard() {
	ParseBoard parser = ParseBoard();
	bool firstPlayerBadPositioningFile = false;
	bool secondPlayerBadPositioningFile = false;
    int reason = SUCCESS;
	int boards = parser.parseBoardFile(BOARD1, board);
	if (boards != SUCCESS) {
		std::cout << "Error in parsing player one's board." << std::endl;
		firstPlayerBadPositioningFile = true;
        firstPlayerLine = boards;
        reason = boards;
	}
	boards = parser.parseBoardFile(BOARD2, board);
	if (boards != SUCCESS) {
		std::cout << "Error in parsing player two's board." << std::endl;
		secondPlayerBadPositioningFile = true;
        secondPlayerLine = boards;
        if(reason != MISSING_INPUT_FILE)
            reason = boards;
	}
	//std::cout << "finished initBoard" << std::endl;
	if(firstPlayerBadPositioningFile && secondPlayerBadPositioningFile){
		// Both players have bad positioning file
		board.setWinner(TIE);
		board.setReason(BOTH_PLAYERS_BAD_POSITIONING);
	}
	else if(firstPlayerBadPositioningFile){
		// first player has bad positioning file - second player wins
		board.setWinner(SECOND_PLAYER);
		board.setReason(BAD_POSITIONING);
	}
	else if(secondPlayerBadPositioningFile){
		// second player has bad positioning file - second player wins
		board.setWinner(FIRST_PLAYER);
		board.setReason(BAD_POSITIONING);
	}
	else return SUCCESS;
    if(reason == MISSING_INPUT_FILE)
        return reason;
	else return ERROR;
}


int Game::firstTurn() {
	// std::cout << "started firstTurn" << std::endl;
	Position pos (0,0);
	for (int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			pos.setXposition(i);
			pos.setYposition(j);
			if(!board.isEmpty(FIRST_PLAYER,pos))
				board.checkAndRunFight(FIRST_PLAYER, pos);
		}
	}
	// std::cout << "finished firstTurn" << std::endl;
    return board.checkVictory(curPlayer, true);
}

void Game::playGame() {
	std::string line1;
	std::string line2;
	std::ifstream movesFile1 (MOVES1);
	Move move(FIRST_PLAYER);
	bool MOVES1_EMPTY = false;
	bool MOVES2_EMPTY = false;


	if (!movesFile1.is_open()) {
		std::cout << "Unable to open file " << MOVES1 << ": " << std::strerror(errno) << std::endl;
		MOVES1_EMPTY = true;
	}
	std::ifstream movesFile2 (MOVES2);
	if (!movesFile2.is_open()) {
		std::cout << "Unable to open file " << MOVES2 << ": " << std::strerror(errno) << std::endl;
		MOVES2_EMPTY = true;
	}
    // playing the game
	while (!MOVES1_EMPTY || !MOVES2_EMPTY) {
        // first player's turn
		if (!MOVES1_EMPTY) {
			if(getline(movesFile1,line1) && !isLineContainWhiteSpaceOnly(line1)){
				move.setPlayer(FIRST_PLAYER);
				if(board.execMove(line1, move) == ERROR) {
					break;
				}
				firstPlayerLine++;
				if (board.checkVictory(FIRST_PLAYER, false) != NONE) {
					break;
				}
			}
			else {
				MOVES1_EMPTY = true;
			}
		}
        else{
            // need to check for victory after every step
            if (board.checkVictory(FIRST_PLAYER, false) != NONE) {
                break;
            }
        }

		if (!MOVES2_EMPTY) {
			if(getline(movesFile2,line2) && !isLineContainWhiteSpaceOnly(line2)){
				move.setPlayer(SECOND_PLAYER);
				if(board.execMove(line2, move) == ERROR) {
					break;
				}
				secondPlayerLine++;
				if (board.checkVictory(SECOND_PLAYER, false) != NONE) {
					break;
				}
			}
			else {
				MOVES2_EMPTY = true;
                if (board.checkVictory(SECOND_PLAYER, false) != NONE) {
                    break;
                }
			}

		}
         // need to check for victory after every step
        else{
            if (board.checkVictory(SECOND_PLAYER, false) != NONE) {
                break;
            }
        }

	}
	movesFile1.close();
	movesFile2.close();
    // if the game is over and there is no winner detected - try to get winner now
    if(board.getWinner() == NONE)
        board.checkVictory(FIRST_PLAYER, true);
}

int Game::startGame() {
	//std::cout << "start startGame" << std::endl;
    int initBoards = initBoard();
	if (initBoards == ERROR) {
		return writeToOutput();
	}
    // One of the input files could not be opened. No output file should be created.
    else if(initBoards == MISSING_INPUT_FILE)
        return SUCCESS;
	//std::cout << "in startGame" << std::endl;

	if (firstTurn() != NONE) {
		return writeToOutput();
	}
	playGame();
	//std::cout << "finished StartGame" << std::endl; //DEBUG
	return writeToOutput();
}

int Game::writeToOutput() {
	std::ofstream output(OUTPUT, std::ofstream::trunc);
	int winner = board.getWinner();

	if(!output.is_open()) {
		std::cout << "Error: could not write to output file:" << std::strerror(errno) << std::endl;
		return ERROR;
	}
	if(winner == NONE) winner = TIE;
	output << "Winner: " << winner << std::endl;
    // check for error in writing to output file
    //bad() function will check for badbit
    if(output.bad()){
        std::cout << "Failed writing to output file" << std::strerror(errno) << std::endl;
        return ERROR;
    }
    //print reason to output file
    if(printReasonToOutputFile(output,board.getReason(),winner) == ERROR){
        std::cout << "Failed writing reason to output file" << std::strerror(errno) << std::endl;
        output.close();
        return ERROR;
    }
    // Third line should be empty line
    output << std::endl;
    // check for error in writing to output file
    //bad() function will check for badbit
    if(output.bad()){
        std::cout << "Failed writing to output file" << std::strerror(errno) << std::endl;
        output.close();
        return ERROR;
    }
    // print board state to file
	if(board.printBoard(output) == ERROR){
        output.close();
        return ERROR;
    }

	output.close();
	return SUCCESS;
}

int Game::printReasonToOutputFile(std::ofstream& output, int reason, int winner) const{
    int line;
    if (winner == FIRST_PLAYER) {
        line = secondPlayerLine;
    } else {
        line = firstPlayerLine;
    }
    // print reason to file
    switch(reason) {
        case FLAG_CAPTURED:
            output << "Reason: All flags of the opponent are captured" << std::endl;
            break;
        case ALL_MOVING_PIECES_EATEN:
            output << "Reason: All moving PIECEs of the opponent are eaten" << std::endl;
            break;
        case TIE_GAME_OVER:
            output << "Reason: A tie - both Moves input files done without a winner" << std::endl;
            break;
        case TIE_BOTH_FLAGS_CAPTURED:
            output << "Reason: A tie - all flags are eaten by both players in the position files" << std::endl;
            break;
        case BAD_POSITIONING:
            output << "Reason: Bad Positioning input file for player " << board.getOpponent(winner) << " line " << line << std::endl;
            break;
        case BOTH_PLAYERS_BAD_POSITIONING:
            output << "Reason: Bad Positioning input file for both players - player 1: line " << firstPlayerLine << ", player 2: line " << secondPlayerLine << std::endl;
            break;
        case BAD_MOVE:
            output << "Reason: Bad Moves input file for player " << board.getOpponent(winner) << " - line " << line << std::endl;
            break;
        default:
            std::cout << "Error in REASON" << std::endl;
            return ERROR;
    }
    // check for error in writing to output file
    //bad() function will check for badbit
    if(output.bad()){
        std::cout << "Failed writing to output file" << std::strerror(errno) << std::endl;
        return ERROR;
    }
    return SUCCESS;
}


