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
        opponentPiece = getPieceFromWinningFight(loseChar);
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



void AutoPlayerAlgorithm::getBestMoveForPlayer(GameMove& move) const{
    int opponentPiecesScore = getOpponentPieceScore();
    int playerPieceScore = game.getPlayerPieceCount(player)*10;
    int piecesScore = playerPieceScore - opponentPiecesScore;
    // need to check for all the valid moves in playerMovingPositions
    // calculate the best move
}

int AutoPlayerAlgorithm::scoringFunction() const{
    return 0;
}

int AutoPlayerAlgorithm::getOpponentPieceScore() const{
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
}


char AutoPlayerAlgorithm::getPieceFromWinningFight(char losingPiece) const{
    char winningPiece;
    switch(losingPiece){
        case SCISSORS:
            // only rock can win scissors
            winningPiece = ROCK;
            break;
        case ROCK:
            // only paper wins rock
            winningPiece = PAPER;
            break;
        case PAPER:
            // only scissors wins paper
            winningPiece = SCISSORS;
            break;
        default:
            // not suppose to get hete
            std::cout << "Unknown winner in fight for char: " << losingPiece << std::endl;
            winningPiece = MOVING_PIECE;
            break;
    }
    return winningPiece;

}