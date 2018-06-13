#include <iostream>
#include <string>
#include <utility>

#include "ex4_header.h"
#include "unit_test_util.h"

void test1(){
    GameBoard<12, 7, std::string, 4> myBoard;
    std::string piece = "nataly";
    std::string piece2 = "yotam";
    std::string piece3 = "tomer";
    myBoard.setPiece(5,5,piece,1);
    myBoard.setPiece(7,5,piece,2);
    myBoard.setPiece(8,6,"nataly",2);
    myBoard.setPiece(6,6,piece2,2);
    myBoard.setPiece(1,1,piece3,3);

    std::cout << "~ ~ myBoard iterator ~ ~"  << std::endl;
    for(auto pieceInfo : myBoard) {
        std::cout << "row: " << std::get<0>(pieceInfo) << std::endl;
        std::cout<< "col: " << std::get<1>(pieceInfo) << std::endl;
        std::cout << "piece: " << std::get<2>(pieceInfo) << std::endl; // we assume here that GAME_PIECE implemented <<
        std::cout << "player: " << std::get<3>(pieceInfo) << std::endl;
    }

    std::cout << "~ ~ myBoard.allPiecesOfPlayer~ ~"  << std::endl;
    for(auto pieceInfo : myBoard.allPiecesOfPlayer(1)) {
        std::cout << "row: " << std::get<0>(pieceInfo) << std::endl;
        std::cout<< "col: " << std::get<1>(pieceInfo) << std::endl;
        std::cout << "piece: " << std::get<2>(pieceInfo) << std::endl; // we assume here that GAME_PIECE implemented <<
        std::cout << "player: " << std::get<3>(pieceInfo) << std::endl;
    }

    std::cout << "~ ~ myBoard.allOccureneceOfPiece~ ~"  << std::endl;

    for(auto pieceInfo : myBoard.allOccureneceOfPiece(piece)) {
        std::cout << "row: " << std::get<0>(pieceInfo) << std::endl;
        std::cout<< "col: " << std::get<1>(pieceInfo) << std::endl;
        std::cout << "piece: " << std::get<2>(pieceInfo) << std::endl; // we assume here that GAME_PIECE implemented <<
        std::cout << "player: " << std::get<3>(pieceInfo) << std::endl;
    }

    std::cout << "~ ~ myBoard.allOccureneceOfPieceForPlayer~ ~"  << std::endl;

    for(auto pieceInfo : myBoard.allOccureneceOfPieceForPlayer(piece, 1)) {
        std::cout << "row: " << std::get<0>(pieceInfo) << std::endl;
        std::cout<< "col: " << std::get<1>(pieceInfo) << std::endl;
        std::cout << "piece: " << std::get<2>(pieceInfo) << std::endl; // we assume here that GAME_PIECE implemented <<
        std::cout << "player: " << std::get<3>(pieceInfo) << std::endl;
    }

}

static bool test2(){
    GameBoard<12, 7, std::string, 4> board;
    int i = 0;
    for (int row = 0; row < 12; row++){
        for(int col =0; col < 7; col++){
            board.setPiece(row, col, "Piece", i);
            i = (i+1)%4;
        }
    }
    int occurence[4]= {0,0,0,0};
    for(auto pieceInfo : board){
        occurence[std::get<3>(pieceInfo)]++;
    }
    for(int i = 0;i<4;i++){
        if (occurence[i] != 21){
            return false;
        }
    }
    return true;
}

void testYotam(){

    std::cout << "hello world" << std::endl;
    std::unique_ptr<int> uni;
    std::cout << "is null? " << (uni== nullptr ? "true" : "false") << std::endl;

    GameBoard<3, 4, std::string, 4> myBoard;
    myBoard.setPiece(0,1,"nataly",1);
    myBoard.setPiece(0,2,"yotam",2);
    myBoard.setPiece(0,3,"tomer",3);
    myBoard.setPiece(1,0,"Yotam",2);
    myBoard.setPiece(1,1,"party",2);
    myBoard.setPiece(1,2,"party",1);
    myBoard.setPiece(1,3,"party",2);

    std::cout << "\nSome getPiece basic checks: \n";
    (myBoard.getPiece(0,0) ?
     std::cout << "0,0: "<< myBoard.getPiece(0,0)->first << ", " << myBoard.getPiece(0,0)->second << std::endl :
     std::cout << "0,0: nullptr" << std::endl);
    (myBoard.getPiece(1,1) ?
     std::cout << "1,1: "<< myBoard.getPiece(1,1)->first << ", " << myBoard.getPiece(1,1)->second << std::endl :
     std::cout << "1,1: nullptr" << std::endl);
    (myBoard.getPiece(0,1) ?
     std::cout << "0,1: "<< myBoard.getPiece(0,1)->first << ", " << myBoard.getPiece(0,1)->second << std::endl :
     std::cout << "0,1: nullptr" << std::endl);

    std::cout << "\nIterate all pieces: \n";
    for(auto pieceInfo : myBoard) {
        std::cout << "row: " << std::get<0>(pieceInfo) << ", ";
        std::cout<< "col: " << std::get<1>(pieceInfo) << ", ";
        std::cout << "piece: <" << std::get<2>(pieceInfo) << ">, "; // we assume here that GAME_PIECE implemented <<
        std::cout << "player: " << std::get<3>(pieceInfo) << std::endl;
    }
    std::cout << "\nIterate player 2 pieces: \n";
    for(auto pieceInfo : myBoard.allPiecesOfPlayer(2)) {
        std::cout << "row: " << std::get<0>(pieceInfo) << ", ";
        std::cout<< "col: " << std::get<1>(pieceInfo) << ", ";
        std::cout << "piece: <" << std::get<2>(pieceInfo) << ">, "; // we assume here that GAME_PIECE implemented <<
        std::cout << "player: " << std::get<3>(pieceInfo) << std::endl;
    }

    std::cout << "\nIterate 'party' pieces: \n";
    for(auto pieceInfo : myBoard.allOccureneceOfPiece("party")) {
        std::cout << "row: " << std::get<0>(pieceInfo) << ", ";
        std::cout<< "col: " << std::get<1>(pieceInfo) << ", ";
        std::cout << "piece: <" << std::get<2>(pieceInfo) << ">, "; // we assume here that GAME_PIECE implemented <<
        std::cout << "player: " << std::get<3>(pieceInfo) << std::endl;
    }

    std::cout << "\nIterate player 2 'party' pieces: \n";
    for(auto pieceInfo : myBoard.allOccureneceOfPieceForPlayer("party", 2)) {
        std::cout << "row: " << std::get<0>(pieceInfo) << ", ";
        std::cout<< "col: " << std::get<1>(pieceInfo) << ", ";
        std::cout << "piece: <" << std::get<2>(pieceInfo) << ">, "; // we assume here that GAME_PIECE implemented <<
        std::cout << "player: " << std::get<3>(pieceInfo) << std::endl;
    }


    std::cout << "\ndone." << std::endl << std::flush;
}


int main(){

    RUN_TEST(test2);
    test1();
    testYotam();
    return 0;
}
