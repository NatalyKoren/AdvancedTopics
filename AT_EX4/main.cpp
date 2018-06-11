#include <iostream>
#include "GameBoard.h"



int main(int argc, char *argv[]){
    GameBoard<12, 7, std::string, 4> myBoard;
    std::string piece = "nataly";
    std::string piece2 = "yotam";
    std::string piece3 = "tomer";
    myBoard.setPiece(5,5,piece,1);
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


    return 0;
}
