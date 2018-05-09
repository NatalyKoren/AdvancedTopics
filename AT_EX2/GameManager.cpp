//
// Created by DELL on 25/04/2018.
//

#include "GameManager.h"


GameManager::GameManager(int firstPlayerType, int secondPlayerType):game(),currentPlayer(FIRST_PLAYER){
	/*
    firstPlayerAlgorithm = (firstPlayerType == FILE_PLAYER)?
                           std::make_unique<FilePlayerAlgorithm>():std::make_unique<AutoPlayerAlgorithm>();

    secondPlayerAlgorithm = (secondPlayerType == FILE_PLAYER)?
                           std::make_unique<FilePlayerAlgorithm>():std::make_unique<AutoPlayerAlgorithm>();
	 */
	if(firstPlayerType == FILE_PLAYER)
		firstPlayerAlgorithm = std::make_unique<FilePlayerAlgorithm>(FIRST_PLAYER);
	else
		firstPlayerAlgorithm = std::make_unique<AutoPlayerAlgorithm>(FIRST_PLAYER);

	if(secondPlayerType == FILE_PLAYER)
		secondPlayerAlgorithm = std::make_unique<FilePlayerAlgorithm>(SECOND_PLAYER);
	else
		secondPlayerAlgorithm = std::make_unique<AutoPlayerAlgorithm>(SECOND_PLAYER);
	initializePieceCount();

}

void GameManager::initializePieceCount() {
	pieceCount[0] = R;
	pieceCount[1] = P;
	pieceCount[2] = S;
	pieceCount[3] = B;
	pieceCount[4] = J;
	pieceCount[5] = F;
}

int GameManager::checkPieces() {
	int pieceCountSize = sizeof(pieceCount) / sizeof(pieceCount[0]);
	for (int i = 0; i < pieceCountSize; i++) {
		if (pieceCount[i] < 0) {
			std::cout << "Board file format error: too many pieces of same type." << std::endl;
			//std::cout << "Index: " << i << " Count: " << pieceCount[i] << std::endl;
			return ERROR;
		}

	}
	// verify that there's a flag
	if (pieceCount[pieceCountSize-1] > 0) {
		std::cout << "Board file format error: flag not placed on board." << std::endl;
		return ERROR;
	}
	return SUCCESS;
}


int GameManager::checkAndUpdatePieceChar (const char& piece) {
	switch(piece) {
	case ROCK: pieceCount[0]--;
	return SUCCESS;
	case PAPER: pieceCount[1]--;
	return SUCCESS;
	case SCISSORS: pieceCount[2]--;
	return SUCCESS;
	case BOMB: pieceCount[3]--;
	return SUCCESS;
	case JOKER: pieceCount[4]--;
	return SUCCESS;
	case FLAG: pieceCount[5]--;
	return SUCCESS;
	default:
		std::cout << "Error in board file: undefined piece " << std::endl;
		return ERROR;
	}
}


int GameManager::checkInitialPositions(std::unique_ptr<PiecePosition>& pieceInfo, int player) {
	const char pieceType = pieceInfo->getPiece();

	// check that the piece type is correct
	if(checkAndUpdatePieceChar(pieceType) == ERROR){
		return ERROR;
	}

	// check for double positioning
	if (game.getPieceAtPosition(player, pieceInfo->getPosition()) != char(0)) {
		return ERROR;
	}
	return SUCCESS;
}

int GameManager::updateInitialPositions(){
	// TODO: Check what about line number error and reason for error - need to see EX1 implementation for this.
	std::vector<unique_ptr<PiecePosition>> firstPlayerPositions;
	std::vector<unique_ptr<PiecePosition>> secondPlayerPositions;
	bool firstPlayerBadPositioningFile = false;
	bool secondPlayerBadPositioningFile = false;
//	int reason = SUCCESS;
	// get players positions on boards
	firstPlayerAlgorithm->getInitialPositions(FIRST_PLAYER, firstPlayerPositions);
	secondPlayerAlgorithm->getInitialPositions(SECOND_PLAYER, secondPlayerPositions);
	// update boards with positioning lists
	int updateResult = updatePositionsOnBoard(FIRST_PLAYER, firstPlayerPositions);
	if(updateResult == ERROR){
		std::cout << "Error in first player positioning stage" << std::endl;
		firstPlayerBadPositioningFile = true;
	}
	initializePieceCount();
	updateResult = updatePositionsOnBoard(SECOND_PLAYER, secondPlayerPositions);
	if(updateResult == ERROR){
		std::cout << "Error in second player positioning stage" << std::endl;
		secondPlayerBadPositioningFile = true;
	}
	// check if some player failed in positioning file
	if(firstPlayerBadPositioningFile && secondPlayerBadPositioningFile){
		// Both players have bad positioning file
		game.setWinner(TIE);
		game.setReason(BOTH_PLAYERS_BAD_POSITIONING);
	}
	else if(firstPlayerBadPositioningFile){
		// first player has bad positioning file - second player wins
		game.setWinner(SECOND_PLAYER);
		game.setReason(BAD_POSITIONING);
	}
	else if(secondPlayerBadPositioningFile){
		// second player has bad positioning file - second player wins
		game.setWinner(FIRST_PLAYER);
		game.setReason(BAD_POSITIONING);
	}
	else return SUCCESS;
	return ERROR;
}

int GameManager::updatePositionsOnBoard(int player, std::vector<unique_ptr<PiecePosition>>& vectorToUpdate){
	char pieceType;
	if(vectorToUpdate.empty())
		return ERROR;
	for(unique_ptr<PiecePosition>& pieceInfo: vectorToUpdate){
		pieceType = pieceInfo->getPiece();
		if(checkInitialPositions(pieceInfo, player) == ERROR){
			return ERROR;
		}
		// need to set lower case character in case of a joker
		if(pieceType == JOKER)
			pieceType = tolower(pieceInfo->getJokerRep());
		game.addPieceToGame(player,pieceType,pieceInfo->getPosition());
	}
	// check that there is a valid num of each piece and there is a flag
	if (checkPieces() == ERROR) {
		return ERROR;
	}
	return SUCCESS;
}

int GameManager::performAllFightAfterInitBoards(std::vector<unique_ptr<FightInfo>>& fights){
	Position pos (0,0);
	GameFightInfo fightInfo;
	for (int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			pos.setXposition(i);
			pos.setYposition(j);
			if(!game.isEmpty(FIRST_PLAYER,pos))
				game.checkAndRunFight(FIRST_PLAYER, pos,fightInfo);
			// if there was a fight need to add this fight to fights
			if(fightInfo.getIsFight())
				fights.push_back(std::make_unique<GameFightInfo>(fightInfo.getPosition(), fightInfo.getPiece(FIRST_PLAYER),
						fightInfo.getPiece(SECOND_PLAYER),fightInfo.getWinner()));

		}
	}
	return game.checkVictory(currentPlayer, true);
}

void GameManager::playGame(){
	int movesCounter = 0;
	int opponent = SECOND_PLAYER;
	GameMove currentMove(currentPlayer);
	GameFightInfo currentFight;
	GameJokerChanged currentJokerChange;
	unique_ptr<Move> playerMove;
	unique_ptr<JokerChange> jokerChange;
	while(1){
		if(movesCounter > 100){
			// there is a 100 moves without a fight - game ends with a tie
			game.setWinner(TIE);
			game.setReason(TIE_GAME_OVER);
			break;
		}
		// get current player move
		playerMove = getMoveFromPlayer(currentPlayer);

		// reach EOF in player
		if(playerMove == NULL) break;

		// update move data
		currentMove.updateMoveFields(*(playerMove));
		currentMove.setPlayer(currentPlayer);

		// execute move
		if(game.execMove(currentMove, currentFight) == ERROR){
			// This is invalid move - the board winner is updated.
			break;
		}
		// if we got here the move is a valid move
		if(currentFight.getIsFight()){
			// need to notify to the current player
			notifyToPlayerOnFightResults(currentPlayer, currentFight);
			movesCounter = 0;
		}
		else
			movesCounter++;

		// check for victory
		if (game.checkVictory(currentPlayer, false) != NONE)
			break;

		// getJoker change
		jokerChange = getJokerChangeFromPlayer(currentPlayer);
		if(jokerChange != NULL){
			// there was a joker change in this move
			currentJokerChange.setPlayer(currentPlayer);
			currentJokerChange.setJokerPosition(jokerChange->getJokerChangePosition());
			currentJokerChange.setNewJokerRep(jokerChange->getJokerNewRep());
			if(game.execJokerChange(currentJokerChange));
		}

		// notify the other player
		opponent = game.getOpponent(currentPlayer);
		notifyToPlayerAfterOpponentsMove(opponent, currentMove);

        if(currentFight.getIsFight()){
            notifyToPlayerOnFightResults(opponent, currentFight);
        }

		// replace player
		currentPlayer = game.getOpponent(currentPlayer);
	}
	//TODO REMOVE THIS
	currentMove.printMove(&std::cout);
	// if the winner is none - check again for moving pieces.
	if(game.getWinner() == NONE)
		game.checkVictory(FIRST_PLAYER, true);
}


void GameManager::notifyToPlayerOnFightResults(int player, const GameFightInfo& fight)const {
	if(player == FIRST_PLAYER)
		firstPlayerAlgorithm->notifyFightResult(fight);
	else secondPlayerAlgorithm->notifyFightResult(fight);
}


unique_ptr<JokerChange> GameManager::getJokerChangeFromPlayer(int player) const{
	if(player==FIRST_PLAYER)
		return firstPlayerAlgorithm->getJokerChange();
	else return secondPlayerAlgorithm->getJokerChange();
}

unique_ptr<Move> GameManager::getMoveFromPlayer(int player) const{
	if(player == FIRST_PLAYER)
		return firstPlayerAlgorithm->getMove();
	else return secondPlayerAlgorithm->getMove();
}

void GameManager::notifyToPlayerAfterOpponentsMove(int playerToNotify, const Move& move) const{
	if(playerToNotify == FIRST_PLAYER)
		firstPlayerAlgorithm->notifyOnOpponentMove(move);
	else secondPlayerAlgorithm->notifyOnOpponentMove(move);

}

int GameManager::writeToOutput() {
	std::ofstream output(OUTPUT, std::ofstream::trunc);
	int winner = game.getWinner();

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
	if(printReasonToOutputFile(output,game.getReason(),winner) == ERROR){
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
	if(game.printBoard(output) == ERROR){
		output.close();
		return ERROR;
	}

	output.close();
	return SUCCESS;
}

int GameManager::printReasonToOutputFile(std::ofstream& output, int reason, int winner) const{
	int line = -1;
	int firstPlayerLine = -1;
	int secondPlayerLine = -1;
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
		output << "Reason: Bad Positioning input file for player " << game.getOpponent(winner) << " - line " << line << std::endl;
		break;
	case BOTH_PLAYERS_BAD_POSITIONING:
		output << "Reason: Bad Positioning input file for both players - player 1: line " << firstPlayerLine << ", player 2: line " << secondPlayerLine << std::endl;
		break;
	case BAD_MOVE:
		output << "Reason: Bad Moves input file for player " << game.getOpponent(winner) << " - line " << line << std::endl;
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

int GameManager::startAndRunGame(){
	// update initial positions
	std::vector<unique_ptr<FightInfo>> fights;
	if(updateInitialPositions() == ERROR)
		return writeToOutput();
	// perform all fights
	int firstStageWinner = performAllFightAfterInitBoards(fights);
	// there is a winner
	if(firstStageWinner != NONE)
		return writeToOutput();
	// notify on initial board
	firstPlayerAlgorithm->notifyOnInitialBoard(game,fights);
	secondPlayerAlgorithm->notifyOnInitialBoard(game,fights);

	// we can start the game now...
	playGame();
	// the game ends...
	return writeToOutput();
}
