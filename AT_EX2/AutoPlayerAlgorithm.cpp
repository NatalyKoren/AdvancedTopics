//
// Created by DELL on 29/04/2018.
//

#include "AutoPlayerAlgorithm.h"

void AutoPlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill){

}

void AutoPlayerAlgorithm::notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights){
    Position pos(0,0);
    // update opponent pieces on board
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            pos.setXposition(i);
            pos.setYposition(j);
            if(b.getPlayer(pos) == opponent)
                game.setPieceAtPosition(opponent,UNKNOWN_PIECE,pos);
                opponentPieceCount++;
                nonMovingPositions.push_back(std::make_unique<Position>(pos.getX(),pos.getY()));
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
    // remove piece from source position
    game.setPieceAtPosition(opponent, (char)0, moveFrom);
    // set piece at destination position to be moving piece
    game.setPieceAtPosition(opponent, MOVING_PIECE,moveTo);
    removePieceFromVector(NON_MOVING_VECTOR, move.getTo());
}

void AutoPlayerAlgorithm::notifyFightResult(const FightInfo& fightInfo){
    char loseChar, opponentPiece;
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
        loseChar = game.getPieceAtPosition(player,fightPos);
        // need to update player board
        game.updateAfterLoseFight(player,fightPos);
        removePieceFromVector(MOVING_VECTOR, fightPos);
        // it is a moving piece of the opponent - need to find put which one
        opponentPiece = fightInfo.getPiece(opponent);
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
    getBestMoveForPlayer(move);
    return std::make_unique<GameMove>(player, move.getFrom(), move.getTo());
}

unique_ptr<JokerChange> AutoPlayerAlgorithm::getJokerChange(){
    return nullptr;
}

void AutoPlayerAlgorithm::removePieceFromVector(int vectorType, const Position& posToRemove){
    if(vectorType == NON_MOVING_VECTOR){
        std::remove_if(nonMovingPositions.begin(), nonMovingPositions.end(),
                       [posToRemove](const std::unique_ptr<Position>& pos){
                           return (posToRemove.getX() == pos->getX()) && (posToRemove.getY() == pos->getY());
                       });
    }
    else{
        std::remove_if(playerMovingPositions.begin(), playerMovingPositions.end(),
                       [posToRemove](const std::unique_ptr<Position>& pos){
                           return (posToRemove.getX() == pos->getX()) && (posToRemove.getY() == pos->getY());
                       });
    }
}



void AutoPlayerAlgorithm::getBestMoveForPlayer(GameMove& move){
    // should update move with best move.
    int opponentPiecesScore = getOpponentPieceScore();
    int playerPieceScore = game.getPlayerPieceCount(player)*10;
    int piecesScore = playerPieceScore - opponentPiecesScore;
    float minDist = -std::numeric_limits<float>::infinity(); // negative infinity
    int xPos,yPos,currentScore;
    GameMove moveToCheck(player);

    for(const unique_ptr<Position>& piecePos: playerMovingPositions){
        // set move source position
        move.setSrcPosition(*(piecePos));
        // check every direction for position
        for(int moveDirection = UP; moveDirection > RIGHT; moveDirection++){
            // update move with current direction
            updateMoveWithDirection(moveToCheck,moveDirection);
            if(game.checkMove(moveToCheck) == VALID_MOVE){
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


    // need to check for all the valid moves in playerMovingPositions
    // calculate the best move
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

float AutoPlayerAlgorithm::scoreMoveOnBoard(GameMove& moveToCheck){
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
            return std::numeric_limits<float>::infinity();
        }
        else{
            // we don't know who wins
            // todo can improve this by adding this score to the distance calculation
            return 2;
        }
        // TODO: now need to calculate distances from non moving pieces

    }
    return 0.0;
}


int AutoPlayerAlgorithm::getOpponentPieceScore() const{
    /*
    char pieceType;
    int movingPieces = 0;
    int nonMovingPieces = 0;
    Position pos(0,0);
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            pos.setXposition(i);
            pos.setYposition(j);
            pieceType = game.getPieceAtPosition(opponent,pos);
            if(pieceType == MOVING_PIECE)
                movingPieces++;
            else if(pieceType == UNKNOWN_PIECE)
                nonMovingPieces++;
        }
    }
    return nonMovingPieces*10 + movingPieces*5;
     */
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
};