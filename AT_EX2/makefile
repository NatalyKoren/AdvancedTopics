COMP = g++
#put all your object files here
OBJS = main.o  autoPlayerAlgorithm.o filePlayerAlgorithm.o GameBoard.o GameJokerChanged.o GameManager.o GameMove.o PlayerPieces.o
#The executabel filename DON'T CHANGE
EXEC = ex2
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
main.o: main.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameBoard.o: GameBoard.cpp GameBoard.h GameMove.h GameMove.cpp GameFightInfo.h Position.h PlayerPieces.cpp PlayerPieces.h Definitions.h Board.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameMove.o: GameMove.cpp GameMove.h Move.h Point.h Position.h Definitions.h GameJokerChanged.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
PlayerPieces.o: PlayerPieces.cpp PlayerPieces.h Definitions.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
filePlayerAlgorithm.o: Definitions.h PlayerAlgorithm.h PlayerAlgorithm.cpp GameMove.h GameMove.cpp InterfacePiecePosition.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameManager.o: GameManager.cpp GameManager.h GameBoard.h PlayerAlgorithm.h FilePlayerAlgorithm.h AutoPlayerAlgorithm.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)