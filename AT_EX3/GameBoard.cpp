#include "GameBoard.h"

GameBoard::GameBoard(): firstPlayerBoard{}, secondPlayerBoard{}, firstPlayerPieces(),secondPlayerPieces(),
                        winner(NONE), reason (0){}

char GameBoard::getPieceAtPosition(int player, const Point& pos) const{
    // pos is a legal position
    if(player == FIRST_PLAYER){
        return firstPlayerBoard[pos.getX()][pos.getY()];
    }
    return secondPlayerBoard[pos.getX()][pos.getY()];
}

void GameBoard::setPieceAtPosition(int player, char piece, const Point& pos){
    if(player == FIRST_PLAYER){
        firstPlayerBoard[pos.getX()][pos.getY()] = piece;
    }
    else{
        secondPlayerBoard[pos.getX()][pos.getY()] = piece;
    }
}

bool GameBoard::isFight(int playerToCheck, Position& pos) const{
    int x = pos.getX();
    int y = pos.getY();
    if(playerToCheck == FIRST_PLAYER)
        return (firstPlayerBoard[x][y] != EMPTY_CHAR);
    else return (secondPlayerBoard[x][y] != EMPTY_CHAR);
}


bool GameBoard::checkAndRunFight(int player, Position &dstPos, GameFightInfo& fightInfo) {
    int opponent = getOpponent(player);
    char opponentPiece = toupper(getPieceAtPosition(opponent,dstPos));
    char currentPlayerPiece = toupper(getPieceAtPosition(player,dstPos));
    int winner;
    if(isFight(opponent, dstPos)){
        //Fight
        winner = fight(dstPos);
        // update opponent board
        if(winner == player)
            updateAfterLoseFight(opponent,dstPos);
            // the current player lose...
        else if(winner == opponent)
            updateAfterLoseFight(player,dstPos);
        else {
            // it is a tie - need to remove both players
            updateAfterLoseFight(player,dstPos);
            updateAfterLoseFight(opponent,dstPos);
        }
        // Update fight info
        fightInfo.setIsFight(true);
        fightInfo.setPosition(dstPos);
        fightInfo.setWinner(winner);
        fightInfo.setPlayerPiece(player, currentPlayerPiece);
        fightInfo.setPlayerPiece(opponent, opponentPiece);
        return true;
    }
    // update fight info
    fightInfo.setIsFight(false);
    return false;
}

void GameBoard::updateBoardAfterMove(GameMove& move, GameFightInfo& fightInfo){
    // assuming it is a valid move
    int player = move.getPlayer();
    Position srcPos = move.getFrom();
    Position dstPos = move.getTo();
    // get char to be updated.
    char charToUpdate = getPieceAtPosition(player, srcPos);
    // update player char
    setPieceAtPosition(player,charToUpdate, dstPos);

    // No fight- need only to update player's dest position
    if (!checkAndRunFight(player, dstPos,fightInfo)) {
        setPieceAtPosition(player,charToUpdate, dstPos);
    }
    // set source position to empty char
    setPieceAtPosition(player,EMPTY_CHAR, srcPos);
}

void GameBoard::updateJoker(const GameJokerChanged& jokerInfo) {

    int player = jokerInfo.getPlayer();
    char jokerRep = tolower(jokerInfo.getJokerNewRep());
    char previousPiece = getPieceAtPosition(player, jokerInfo.getJokerChangePosition());
    setPieceAtPosition(player, jokerRep, jokerInfo.getJokerChangePosition());
    if(player == FIRST_PLAYER)
        firstPlayerPieces.updateJokerMovingCount(previousPiece, jokerRep);
    else
        secondPlayerPieces.updateJokerMovingCount(previousPiece, jokerRep);
}


int GameBoard::fight(Position& pos) const{
    int firstPlayerPiece = getPieceAtPosition(FIRST_PLAYER,pos);
    int secondPlayerPiece = getPieceAtPosition(SECOND_PLAYER,pos);
    //For joker cases
    firstPlayerPiece = toupper(firstPlayerPiece);
    secondPlayerPiece = toupper(secondPlayerPiece);
    // Tie
    if(firstPlayerPiece == secondPlayerPiece) return TIE;

    switch(firstPlayerPiece){
        case BOMB:
            return TIE; // Need to remove bomb from board
        case FLAG:
            if(secondPlayerPiece == BOMB) return TIE;
            return SECOND_PLAYER;
        case ROCK:
            if(secondPlayerPiece == SCISSORS || secondPlayerPiece == FLAG) return FIRST_PLAYER;
            else if(secondPlayerPiece == BOMB) return TIE;
            else return SECOND_PLAYER;
        case PAPER:
            if(secondPlayerPiece == ROCK || secondPlayerPiece == FLAG) return FIRST_PLAYER;
            else if(secondPlayerPiece == BOMB) return TIE;
            else return SECOND_PLAYER;
        case SCISSORS:
            if(secondPlayerPiece == PAPER || secondPlayerPiece == FLAG) return FIRST_PLAYER;
            else if(secondPlayerPiece == BOMB) return TIE;
            else return SECOND_PLAYER;
        default:
            return NONE;
    }
}

void GameBoard::increasePieceNum(int player, char piece, int num){
    if(player == FIRST_PLAYER) firstPlayerPieces.incrementPieceNum(piece, num);
    else secondPlayerPieces.incrementPieceNum(piece, num);
}

void GameBoard::updateAfterLoseFight(int player, const Position& pos){
    char charToRemove = getPieceAtPosition(player, pos);
    setPieceAtPosition(player,EMPTY_CHAR, pos);
    increasePieceNum(player,charToRemove,-1);
}

int GameBoard::checkVictory(int curPlayer, bool initStage){
    int curPlayerMovingNum;
    int opponentMovingNum;
    if(curPlayer == FIRST_PLAYER) {
        curPlayerMovingNum = firstPlayerPieces.getMovePiecesNum();
        opponentMovingNum = secondPlayerPieces.getMovePiecesNum();
    }
    else{
        curPlayerMovingNum = secondPlayerPieces.getMovePiecesNum();
        opponentMovingNum = firstPlayerPieces.getMovePiecesNum();
    }
    // Flags check
    if(firstPlayerPieces.getFlagNum() == 0) {
        if(secondPlayerPieces.getFlagNum() == 0) {
            winner = TIE;
            reason = TIE_BOTH_FLAGS_CAPTURED;
        }
        else{
            // second player wins
            winner = SECOND_PLAYER;
            reason = FLAG_CAPTURED;
        }
    }
    else if(secondPlayerPieces.getFlagNum() == 0){
        // first player wins - flag num of first player is not 0.
        winner = FIRST_PLAYER;
        reason = FLAG_CAPTURED;
    }
     // flags number of both players is not 0.
    else if (opponentMovingNum == 0) {
        winner = curPlayer;
        reason = ALL_MOVING_PIECES_EATEN;
        // init stage - maybe two player does not have moving pieces
        if(initStage && curPlayerMovingNum == 0){
            winner = TIE;
            reason = ALL_MOVING_PIECES_EATEN;
        }
    }
        // init stage - all player moving pieces are eaten
    else if(initStage && curPlayerMovingNum == 0){
        winner = getOpponent(curPlayer);
        reason = ALL_MOVING_PIECES_EATEN;
    }
    else {
        winner = NONE;
        reason = TIE_GAME_OVER;
    }
    return winner;
}

void GameBoard::addPieceToGame(int player, char piece, const Point& pos){
    setPieceAtPosition(player,piece,pos);
    increasePieceNum(player, piece, 1);
}
bool GameBoard::isEmpty(int player, const Point& pos) const{
    return (getPieceAtPosition(player,pos) == (char) 0);
}

int GameBoard::checkMove(GameMove& move, bool printToConsole) const{
    char charToMove;
    // (1) boundary tests
    if(checkMoveBoundaries(move,printToConsole) == INDEX_OUT_OF_BOUND)
        return INDEX_OUT_OF_BOUND;
    // boundary is valid
    // (2) moving to position contain same player piece
    if(!(isEmpty(move.getPlayer(), move.getTo()))){
        if(printToConsole){
            std::cout << "Illegal move. Player: " << move.getPlayer() << " try to move to destination position occupied by him. Destination position: ";
            printPoint(move.getTo());
            std::cout << std::endl;
        }
        return ILLEGAL_MOVE;
    }
    if(move.testForValidMovementOfBoard() == ILLEGAL_MOVE){
        if(printToConsole){
            std::cout << "Illegal movement on board. Player: " << move.getPlayer() << " try to move from: ";
            printPoint(move.getFrom());
            std::cout << " to: ";
            printPoint(move.getTo());
            std::cout << std::endl;
        }
        return ILLEGAL_MOVE;
    }
    // (3) source position is empty
    charToMove = getPieceAtPosition(move.getPlayer(), move.getFrom());
    if(charToMove == EMPTY_CHAR){
        if(printToConsole){
            std::cout << "Illegal source position for Player: " << move.getPlayer() << ". Position ";
            printPoint(move.getFrom());
            std::cout << " does not contain a player piece." << std::endl;
        }
        return ILLEGAL_MOVE;
    }
    // (4) try to move non moving piece
    if(toupper(charToMove) == BOMB || charToMove == FLAG ){
        if(printToConsole){
            std::cout << "Illegal source position for Player " << move.getPlayer() << ". Position ";
            printPoint(move.getFrom());
            std::cout << " contains non moving piece." << std::endl;
        }
        return ILLEGAL_MOVE;
    }
    // Seems OK ...
    return VALID_MOVE;
}

int GameBoard::testForJokerValidChange(const GameJokerChanged& jokerInfo) const{
    int player = jokerInfo.getPlayer();
    Position jokerPos(jokerInfo.getJokerChangePosition());
    // joker position is empty
    if(isEmpty(player, jokerPos)){
        std::cout << "Joker position for Player: " << player << " is empty. Position ";
        jokerPos.printPosition();
        std::cout << std::endl;
        return ILLEGAL_MOVE;
    }
    // joker position doesn't contain a joker piece
    if(!islower(getPieceAtPosition(player,jokerPos))){
        std::cout << "Joker position for Player: " << player << " doesn't contain a joker's piece. Position ";
        jokerPos.printPosition();
        std::cout << std::endl;
        return ILLEGAL_MOVE;
    }
    // test if joker new char is a valid char: S,R,P,B
    if(!jokerInfo.isJokerValidChar()){
        std::cout << "Joker new representation for player" << player << " is invalid." << std::endl;
        return ILLEGAL_MOVE;
    }
    return VALID_MOVE;
}


int GameBoard::printBoard(std::ofstream& output) const{
    for (int y = 0; y < M; y++) {
        for (int x = 0; x < N; x++)  {
            Position pos (x,y);
            if (isEmpty(FIRST_PLAYER, pos)) {
                if (isEmpty(SECOND_PLAYER, pos)) {
                    output << " ";
                } else {
                    if(islower(secondPlayerBoard[x][y]))
                        output << 'j';
                    else
                        output << (char)tolower(secondPlayerBoard[x][y]);
                }
            }
            else {
                if(islower(firstPlayerBoard[x][y]))
                    output << 'J';
                else
                    output << (char)toupper(firstPlayerBoard[x][y]);
            }
            if(output.bad()){
                std::cout << "Failed writing to output file" << std::strerror(errno) << std::endl;
                return ERROR;
            }
        }
        output << std::endl;
    }
    return SUCCESS;
}

int GameBoard::getPlayer(const Point& pos) const{
    const Position posToCheck(pos.getX()-1, pos.getY()-1);
    if(!isEmpty(FIRST_PLAYER,posToCheck))
        return FIRST_PLAYER;
    if(!isEmpty(SECOND_PLAYER,posToCheck))
        return SECOND_PLAYER;
    return TIE;
}

int GameBoard::execMove(GameMove &move, GameFightInfo& fightInfo) {
    int currentPlayer = move.getPlayer();
    int opponentPlayer = getOpponent(currentPlayer);

    // check if move is a valid move
    // true because execMove is callled only from the game manager, thus we want to print reason to cout.
    if(checkMove(move, true) != VALID_MOVE){
        std::cout << "Bad move for player " << currentPlayer << std::endl;
        winner = opponentPlayer;
        reason = BAD_MOVE;
        return ERROR;
    }
    updateBoardAfterMove(move, fightInfo);
    return SUCCESS;
}

int GameBoard::execJokerChange(GameJokerChanged& jokerInfo){
    int curPlayer = jokerInfo.getPlayer();
    int opponentPlayer = getOpponent(curPlayer);
    // Test if joker change is valid
    if(testForJokerValidChange(jokerInfo) == ILLEGAL_MOVE){
        std::cout << "Bad joker change for player: " << curPlayer << ": illegal attempt to change Joker." << std::endl;
        winner = opponentPlayer;
        reason = BAD_MOVE;
        return ERROR;
    }
    // Execute joker change
    updateJoker(jokerInfo);
    return SUCCESS;
}

int GameBoard::getPlayerPieceCount(int player)const{
    if(player == FIRST_PLAYER)
        return firstPlayerPieces.getPieceCount();
    else return secondPlayerPieces.getPieceCount();

}

int GameBoard::checkMoveBoundaries(GameMove& move, bool printToConsole) const{
    // test src boundary
    if(move.positionBoundaryTest(move.getFrom()) == INDEX_OUT_OF_BOUND){
        if(printToConsole){
            std::cout << "Illegal source position. Player: " << move.getPlayer() << " insert out of bound source position: ";
            printPoint(move.getFrom());
            std::cout << std::endl;
        }
        return INDEX_OUT_OF_BOUND;
    }
    // test dst boundary
    if(move.positionBoundaryTest(move.getTo()) == INDEX_OUT_OF_BOUND){
        if(printToConsole){
            std::cout << "Illegal destination position. Player: " << move.getPlayer() << " insert out of bound source position: ";
            printPoint(move.getTo());
            std::cout << std::endl;
        }
        return INDEX_OUT_OF_BOUND;
    }
    // boundary is valid
    return VALID_MOVE;
}