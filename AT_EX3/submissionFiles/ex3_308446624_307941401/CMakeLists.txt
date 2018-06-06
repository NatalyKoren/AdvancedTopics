cmake_minimum_required(VERSION 3.9)
project(AT_EX3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

add_executable(AT_EX3
        AlgorithmRegistration.h
        AutoPlayerAlgorithm.cpp
        AutoPlayerAlgorithm.h
        Board.h
        Definitions.h
        FightInfo.h
        GameBoard.cpp
        GameBoard.h
        GameFightInfo.h
        GameJokerChanged.cpp
        GameJokerChanged.h
        GameManager.cpp
        GameManager.h
        GameMove.cpp
        GameMove.h
        InterfacePiecePosition.h
        JokerChange.h
        main.cpp
        Move.h
        PiecePosition.h
        PlayerAlgorithm.h
        PlayerPieces.cpp
        PlayerPieces.h
        Point.h
        Position.h GameTournamentManager.h GameTournamentManager.cpp)
