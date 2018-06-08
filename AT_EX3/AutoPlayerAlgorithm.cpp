//
// Created by DELL on 29/04/2018.
//


#include "AutoPlayerAlgorithm.h"

bool printToFile = false;
// Registering the algorithm
REGISTER_ALGORITHM(308446624)

void RSPPlayer_308446624::init() {
	srand(time(0));
	if (printToFile) {
		std::string fileName = "AutoPlayerFile_" + std::to_string(player)
				+ ".txt";
		autoFilePlayer.open(fileName.c_str());
	}
}
extern "C"{
RSPPlayer_308446624::RSPPlayer_308446624(int playerNum):player(playerNum), game(), opponent(game.getOpponent(playerNum)),
                                                        opponentPieceCount(0),pieceCount{R,P,S,B,J,F}, nonMovingPositions(),
                                                        playerMovingPositions(){
	init();
}

void RSPPlayer_308446624::getInitialPositions(int playerNum, std::vector<unique_ptr<PiecePosition>>& vectorToFill){
    // Set the correct player
    player = playerNum;
    opponent = game.getOpponent(playerNum);
    int pos_taken[M][N] = {{0}}; // an array to mark squares that are occupied, 0 means empty
    int x, y;
    positionFlag(vectorToFill, pos_taken);
    char pieces[] = {ROCK, PAPER, SCISSORS, BOMB, JOKER, FLAG};
    for (int i = 0; i < NUM_OF_DIFF_PIECES; i++) {
        for (int j = 0; j < pieceCount[i]; j++) {
            x = rand() % M;
            y = rand() % N;
            while (pos_taken[x][y] != 0) {
                x = rand() % M;
                y = rand() % N;
            }
            positionPieceOnBoard(vectorToFill,pos_taken,pieces[i], Position(x,y));
            // updating the auto player's board
            if(isMovingPiece(pieces[i]))
                playerMovingPositions.push_back(std::make_unique<Position>(x,y));
        }
    }
    if(printToFile){
        autoFilePlayer << "Board: " << std::endl;
        game.printBoard(autoFilePlayer);
        autoFilePlayer << "End Board" << std::endl;
        autoFilePlayer << "-----------------------" << std::endl;
    }
}

void RSPPlayer_308446624::notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights){
    Position pos(0,0);
    // update opponent pieces on board
    for(int i=0; i<M; i++){
        for(int j=0; j<N; j++){
            // Function getPlayer is an interface function, thus need to get point 1-based.
            pos.setXposition(i+1);
            pos.setYposition(j+1);
            if(b.getPlayer(pos) == opponent){
                // new setPosition get 0-based
                pos.setXposition(i);
                pos.setYposition(j);
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

void RSPPlayer_308446624::notifyOnOpponentMove(const Move& move){
    const Position moveFrom(move.getFrom().getX()-1, move.getFrom().getY()-1);
    const Position moveTo(move.getTo().getX()-1, move.getTo().getY()-1);
    if(!checkForValidPosition(moveFrom) || !checkForValidPosition(moveTo)){
        std::cout << "Received invalid move at notifyOnOpponentMove" << std::endl;
        return;
    }
    char prevChar = game.getPieceAtPosition(opponent, moveFrom);
    // remove piece from source position
    game.setPieceAtPosition(opponent, EMPTY_CHAR, moveFrom);
    // set piece at destination position to be moving piece
    if(prevChar == UNKNOWN_PIECE)
        prevChar = MOVING_PIECE;
    game.setPieceAtPosition(opponent, prevChar,moveTo);
    removePieceFromVector(NON_MOVING_VECTOR, moveFrom);
}

void RSPPlayer_308446624::notifyFightResult(const FightInfo& fightInfo){
    int winner = fightInfo.getWinner();
    Position fightPos = fightInfo.getPosition();
    fightPos.setXposition(fightPos.getX()-1);
    fightPos.setYposition(fightPos.getY()-1);
    if(!checkForValidPosition(fightPos)){
        std::cout << "Received invalid move at notifyFightResult" << std::endl;
        return;
    }

    // current player wins the fight
    // need to update opponents board
    if(winner == player){
        // delete the char from opponents board
        game.setPieceAtPosition(opponent, EMPTY_CHAR, fightPos);
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
        game.setPieceAtPosition(opponent, EMPTY_CHAR, fightPos);
        opponentPieceCount--;
        removePieceFromVector(NON_MOVING_VECTOR, fightPos);
    }
    else{
        // should never get here
        std::cout << "Unknown winner in Fight Info." <<std::endl;
    }
}

unique_ptr<Move> RSPPlayer_308446624::getMove(){
    GameMove move(player);
    char prevChar;
    getBestMoveForPlayer(move);
    if(printToFile){
        autoFilePlayer << "Move:" << std::endl;
        move.printMove(&autoFilePlayer);
        autoFilePlayer << "-----------------------" << std::endl;
    }
    prevChar  = game.getPieceAtPosition(player, move.getFrom());
    game.setPieceAtPosition(player, EMPTY_CHAR, move.getFrom());
    game.setPieceAtPosition(player, prevChar, move.getTo());
    // update moving pieces vector
    updateMovingPiecesVector(move);

    // updating the move to be 1-based instead of 0-based for the game manager
    move.setSrcPosition(move.getFrom().getX()+1, move.getFrom().getY()+1);
    move.setDstPosition(move.getTo().getX()+1, move.getTo().getY()+1);
    return std::make_unique<GameMove>(player, move.getFrom(), move.getTo());
}

unique_ptr<JokerChange> RSPPlayer_308446624::getJokerChange(){
    return nullptr;
}
}
void RSPPlayer_308446624::removePieceFromVector(int vectorType, const Position& posToRemove){
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



void RSPPlayer_308446624::getBestMoveForPlayer(GameMove& move){
    // should update move with best move.
    int currentScore;
    GameMove moveToCheck(player);
    float minDist = std::numeric_limits<float>::infinity(); // infinity

    // print to debug file
    if(printToFile){
        autoFilePlayer << "Board:" << std::endl;
        game.printBoard(autoFilePlayer);
    }
    // For every moving position
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
void RSPPlayer_308446624::updateMoveWithDirection(GameMove& moveToCheck, int moveDirection) const{
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

float RSPPlayer_308446624::scoreMoveOnBoard(const GameMove& moveToCheck){
    // first check for a fight
    int opponentChar = game.getPieceAtPosition(opponent, moveToCheck.getTo());
    int ourChar = game.getPieceAtPosition(player, moveToCheck.getFrom());
    ourChar = toupper(ourChar);
    int winner;
    if(opponentChar == UNKNOWN_PIECE){
        // we want to go there - it maybe a flag!
        return -10;
    }
    else if(opponentChar != EMPTY_CHAR){
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
            return 10;
        }
    }
    return calculateMinDistance(moveToCheck.getTo(), nonMovingPositions);
}


int RSPPlayer_308446624::getWinnerOfFight(char ourChar, char opponentChar) const{
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


int RSPPlayer_308446624::calculateMinDistance(const Point& fromPos, const std::vector<unique_ptr<Position>>& vectorToComare) const{
    float minDis = std::numeric_limits<float>::infinity();
    float dist;
    for(const unique_ptr<Position>& pieceToCheck: vectorToComare){
        dist = abs(pieceToCheck->getX() - fromPos.getX()) + abs(pieceToCheck->getY() - fromPos.getY());
        if(dist < minDis)
            minDis = dist;
    }
    return minDis;
}

void RSPPlayer_308446624::updateMovingPiecesVector(const GameMove& move){
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

bool RSPPlayer_308446624::checkForValidPosition(const Point& pos) const{
    int x = pos.getX();
    int y = pos.getY();
    if(x < 0 || x >= M)
        return false;
    if(y < 0 || y >= N)
        return false;
    return true;
}

bool RSPPlayer_308446624::isMovingPiece(char piece)const{
    return (piece == PAPER)|| (piece == ROCK) || (piece == SCISSORS);
}


void RSPPlayer_308446624::positionFlag(std::vector<unique_ptr<PiecePosition>>& vectorToFill, int board[M][N]){
    GameMove tempMove(player);
    int bombIndex = 3;
    int jokerIndex = 4;
    int flagIndex = 5;
    int flagX = rand() % M;
    int flagY = rand() % N;
    // add flag positioning
    board[flagX][flagY] = 1;
    Position curPos(flagX, flagY);
    game.addPieceToGame(player, FLAG, curPos);
    pieceCount[flagIndex]--;
    tempMove.setSrcPosition(curPos);
    curPos.setXposition(flagX+1);
    curPos.setYposition(flagY+1);
    InterfacePiecePosition curPiece(curPos, FLAG, EMPTY_CHAR);
    vectorToFill.push_back(std::make_unique<InterfacePiecePosition>(curPiece));
    // positioning bomb and joker
    for(int direction = UP; direction <=RIGHT; direction++){
        updateMoveWithDirection(tempMove,direction);
        if(tempMove.positionBoundaryTest(tempMove.getTo()) == VALID_INDEX){
            if(pieceCount[bombIndex] > 0){
                positionPieceOnBoard(vectorToFill,board,BOMB,tempMove.getTo());
                pieceCount[bombIndex]--;
            }
            else{
                positionPieceOnBoard(vectorToFill,board,JOKER,tempMove.getTo());
                pieceCount[jokerIndex]--;
            }
        }
    }
}

void RSPPlayer_308446624::positionPieceOnBoard(std::vector<unique_ptr<PiecePosition>>& vectorToFill,int board[M][N], char piece, const Point& pos){
    int x = pos.getX();
    int y = pos.getY();
    char jokerRep = BOMB;
    board[x][y] = 1;
    Position curPos(x, y);
    // update piece on board
    if(piece ==JOKER)
        game.addPieceToGame(player, tolower(jokerRep), curPos);
    else
        game.addPieceToGame(player, piece, curPos);

    curPos.setXposition(x+1);
    curPos.setYposition(y+1);
    InterfacePiecePosition curPiece(curPos, piece, jokerRep);
    vectorToFill.push_back(std::make_unique<InterfacePiecePosition>(curPiece));
}