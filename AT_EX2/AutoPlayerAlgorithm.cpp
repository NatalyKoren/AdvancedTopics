//
// Created by DELL on 29/04/2018.
//


#include "AutoPlayerAlgorithm.h"

void AutoPlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill){
    int pos_taken[N][M] = {{0}}; // an array to mark squares that are occupied, 0 means empty
    int x, y;
    char jokerRep = char(0);
    char pieces[] = {ROCK, PAPER, SCISSORS, BOMB, JOKER, FLAG};
    for (int i = 0; i < NUM_OF_DIFF_PIECES; i++) {
        for (int j = 0; j < pieceCount[i]; j++) {
            x = rand() % N;
            y = rand() % M;
            while (pos_taken[x][y] != 0) {
                x = rand() % N;
                y = rand() % M;
            }
            if (pieceCount[i] == JOKER) {
                jokerRep = BOMB;
            }
            pos_taken[x][y] = 1;
            Position curPos(x, y);
            InterfacePiecePosition curPiece(curPos, pieces[i], jokerRep);
            vectorToFill.push_back(std::make_unique<InterfacePiecePosition>(curPiece));
            // updating the autoplayer's board:
            game.setPieceAtPosition(player, pieces[i], curPos);
            if(pieces[i] == PAPER || pieces[i] == ROCK || pieces[i] == SCISSORS)
                playerMovingPositions.push_back(std::make_unique<Position>(x,y));
        }
    }
    // TODO delete this
    autoFilePlayer << "Board: " << std::endl;
    game.printBoard(autoFilePlayer);
    autoFilePlayer << "End Board" << std::endl;
    autoFilePlayer << "-----------------------" << std::endl;


}

void AutoPlayerAlgorithm::notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights){
    Position pos(0,0);
    // update opponent pieces on board
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            pos.setXposition(i);
            pos.setYposition(j);
            if(b.getPlayer(pos) == opponent){
                game.setPieceAtPosition(opponent,UNKNOWN_PIECE,pos);
                opponentPieceCount++;
                nonMovingPositions.push_back(std::make_unique<Position>(pos.getX(),pos.getY()));
            }
        }
    }
    // now check for fights...
    for(const unique_ptr<FightInfo>& fight: fights){
        notifyFightResult(*(fight));
    }
}

void AutoPlayerAlgorithm::notifyOnOpponentMove(const Move& move){
    const Position moveFrom = move.getFrom();
    const Position moveTo = move.getTo();
    char prevChar = game.getPieceAtPosition(opponent, moveFrom);
    // remove piece from source position
    game.setPieceAtPosition(opponent, (char)0, moveFrom);
    // set piece at destination position to be moving piece
    if(prevChar == UNKNOWN_PIECE)
        prevChar = MOVING_PIECE;
    game.setPieceAtPosition(opponent, prevChar,moveTo);
    removePieceFromVector(NON_MOVING_VECTOR, moveFrom);
}

void AutoPlayerAlgorithm::notifyFightResult(const FightInfo& fightInfo){
    int winner = fightInfo.getWinner();
    const Position fightPos = fightInfo.getPosition();

    // current player wins the fight
    // need to update opponents board
    if(winner == player){
        // delete the char from opponents board
        game.setPieceAtPosition(opponent, (char)0, fightPos);
        // remove piece from vector
        removePieceFromVector(NON_MOVING_VECTOR,fightPos);
        opponentPieceCount--;
    }
    else if(winner == opponent){
        // need to update player board
        game.updateAfterLoseFight(player,fightPos);
        removePieceFromVector(MOVING_VECTOR, fightPos);
        // it is a moving piece of the opponent - need to find put which one
        char opponentPiece = fightInfo.getPiece(opponent);
        game.setPieceAtPosition(opponent, opponentPiece,fightPos);
        removePieceFromVector(NON_MOVING_VECTOR, fightPos);
    }
    else if(winner == TIE){
        // need to update player board
        game.updateAfterLoseFight(player,fightPos);
        removePieceFromVector(MOVING_VECTOR, fightPos);
        // delete the char from opponents board
        game.setPieceAtPosition(opponent, (char)0, fightPos);
        opponentPieceCount--;
        removePieceFromVector(NON_MOVING_VECTOR, fightPos);
    }
    else{
        // should never get here
        std::cout << "Unknown winner in Fight Info." <<std::endl;
    }

}

unique_ptr<Move> AutoPlayerAlgorithm::getMove(){
    GameMove move(player);
    char prevChar;
    getBestMoveForPlayer(move);
    autoFilePlayer << "Move:" << std::endl;
    move.printMove(&autoFilePlayer);
    autoFilePlayer << "-----------------------" << std::endl;
    prevChar  = game.getPieceAtPosition(player, move.getFrom());
    game.setPieceAtPosition(player, char(0), move.getFrom());
    game.setPieceAtPosition(player, prevChar, move.getTo());
    // update moving pieces vector
    updateMovingPiecesVector(move);

	// updating the move to be 1-based instead of 0-based for the game manager
	move.setSrcPosition(move.getFrom().getX()+1, move.getFrom().getY()+1);
	move.setDstPosition(move.getTo().getX()+1, move.getTo().getY()+1);
    return std::make_unique<GameMove>(player, move.getFrom(), move.getTo());
}

unique_ptr<JokerChange> AutoPlayerAlgorithm::getJokerChange(){
    return nullptr;
}

void AutoPlayerAlgorithm::removePieceFromVector(int vectorType, const Position& posToRemove){
    if(vectorType == NON_MOVING_VECTOR){
        auto newEndIterator = std::remove_if(nonMovingPositions.begin(), nonMovingPositions.end(),
                                             [posToRemove](const std::unique_ptr<Position>& pos){
                                                 return (posToRemove.getX() == pos->getX()) && (posToRemove.getY() == pos->getY());
                                             });
        nonMovingPositions.erase(newEndIterator, nonMovingPositions.end());
    }
    else{
        auto newEndIterator = std::remove_if(playerMovingPositions.begin(), playerMovingPositions.end(),
                                             [posToRemove](const std::unique_ptr<Position>& pos){
                                                 return (posToRemove.getX() == pos->getX()) && (posToRemove.getY() == pos->getY());
                                             });
        playerMovingPositions.erase(newEndIterator, playerMovingPositions.end());
    }
}



void AutoPlayerAlgorithm::getBestMoveForPlayer(GameMove& move){
    // should update move with best move.
//    int opponentPiecesScore = getOpponentPieceScore();
//    int playerPieceScore = game.getPlayerPieceCount(player)*10;
//    int piecesScore = playerPieceScore - opponentPiecesScore;
    float minDist = std::numeric_limits<float>::infinity(); // infinity
//    int xPos,yPos;
    int currentScore;
    GameMove moveToCheck(player);

    autoFilePlayer << "Board:" << std::endl;
    game.printBoard(autoFilePlayer);
    for(const unique_ptr<Position>& piecePos: playerMovingPositions){
        // set move source position
        moveToCheck.setSrcPosition(*(piecePos));
        // check every direction for position
        for(int moveDirection = UP; moveDirection <= RIGHT; moveDirection++){
            // update move with current direction
            updateMoveWithDirection(moveToCheck,moveDirection);
            if(game.checkMove(moveToCheck, false) == VALID_MOVE){
                // this is a valid move, need to check for scoring
                currentScore = scoreMoveOnBoard(moveToCheck);
                if(currentScore < minDist){
                    // this is the best move so far
                    minDist = currentScore;
                    move.setSrcPosition(moveToCheck.getFrom());
                    move.setDstPosition(moveToCheck.getTo());
                }
            }
        }
    }
}
void AutoPlayerAlgorithm::updateMoveWithDirection(GameMove& moveToCheck, int moveDirection) const{
    int xPos = moveToCheck.getFrom().getX();
    int yPos = moveToCheck.getFrom().getY();
    switch(moveDirection){
        case UP:
            xPos-=1;
            break;
        case DOWN:
            xPos+=1;
            break;
        case LEFT:
            yPos-=1;
            break;
        case RIGHT:
            yPos+=1;
            break;
        default:
            //should never get here
            break;
    }
    moveToCheck.setDstPosition(xPos,yPos);
}

float AutoPlayerAlgorithm::scoreMoveOnBoard(const GameMove& moveToCheck){
    // first check for a fight
    int opponentChar = game.getPieceAtPosition(opponent, moveToCheck.getTo());
    int ourChar = game.getPieceAtPosition(player, moveToCheck.getFrom());
    int winner;
    if(opponentChar == UNKNOWN_PIECE){
        // we want to go there - it maybe a flag!
        return -10;
    }
    else if(opponentChar != (char)0){
        // it is some moving piece
        winner = getWinnerOfFight(ourChar, opponentChar);
        if(winner == player){
            // we won the fight
            return -5;
        }
        else if(winner == opponent || winner == TIE){
            // we are losing the fight - Don't want this move
            return 100;
        }
        else{
            // we don't know who wins
            // todo can improve this by adding this score to the distance calculation
            return 2;
        }
    }

    return calculateMinDistance(moveToCheck.getTo(), nonMovingPositions);
}


int AutoPlayerAlgorithm::getOpponentPieceScore() const{
    int nonMovingCount = nonMovingPositions.size();
    return nonMovingCount*10 + (opponentPieceCount - nonMovingCount)*5;
}



int AutoPlayerAlgorithm::getWinnerOfFight(char ourChar, char opponentChar) const{
    // assuming ourChar is a moving piece
    ourChar = toupper(ourChar);
    if(ourChar == opponentChar)
        return TIE;
    int winner;
    switch(opponentChar){
        case SCISSORS:
            if(ourChar == ROCK) winner = player;
            else if(ourChar == PAPER) winner = opponent;
            else winner = NONE;
            break;
        case ROCK:
            if(ourChar == PAPER) winner = player;
            else if(ourChar == SCISSORS) winner = opponent;
            else winner = NONE;
            break;
        case PAPER:
            if(ourChar == SCISSORS) winner = player;
            else if(ourChar == ROCK) winner = opponent;
            else winner = NONE;
            break;
        case MOVING_PIECE:
            // we don't know who wins
            winner = NONE;
            break;
        default:
            winner = NONE;
            break;
    }
    return winner;
}


int AutoPlayerAlgorithm::calculateMinDistance(const Point& fromPos, std::vector<unique_ptr<Position>>& vectorToComare) const{
    float minDis = std::numeric_limits<float>::infinity();
    float dist;
    for(unique_ptr<Position>& pieceToCheck: vectorToComare){
        dist = abs(pieceToCheck->getX() - fromPos.getX()) + abs(pieceToCheck->getY() - fromPos.getY());
        if(dist < minDis)
            minDis = dist;
    }
    return minDis;
}

void AutoPlayerAlgorithm::updateMovingPiecesVector(const GameMove& move){
    const Position srcPos = move.getFrom();
    const Position dstPos = move.getTo();
    for(unique_ptr<Position>& piecePos: playerMovingPositions){
        if((*piecePos).isEqual(srcPos)){
            piecePos->setXposition(dstPos.getX());
            piecePos->setYposition(dstPos.getY());
            break;
        }
    }

}

void AutoPlayerAlgorithm::compareListToBoard(){
    for(unique_ptr<Position>& piecePos: playerMovingPositions){
        if(game.getPieceAtPosition(player, *piecePos) == char(0)){
            std::cout << "Mismatch between board and vector" << std::endl;
            printPoint(*piecePos);

        }
    }
}
