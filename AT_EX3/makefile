COMP = g++
# COMP = g++-5.3.0
#put all your object files here
OBJS = main.o GameBoard.o GameJokerChanged.o GameManager.o GameMove.o PlayerPieces.o GameTournamentManager.o
#The executabel filename DON'T CHANGE
EXEC = ex3
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra -Werror -pedantic-errors -g
#CPP_SO_FLAGS = AutoPlayerAlgorithm.o  -shared -o libAutoPlayerAlgorithm.so
CPP_SO_FLAGS = -shared -o
all: ex3 RSPPlayer_222222222.so 


$(EXEC): $(OBJS) RSPPlayer_222222222.so
	$(COMP) $(OBJS) -rdynamic -ldl -pthread -g -o $@
RSPPlayer_222222222.so: AutoPlayerAlgorithm.o
	$(COMP) AutoPlayerAlgorithm.o -shared -g -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
main.o: main.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp -ldl
GameBoard.o: GameBoard.cpp GameBoard.h GameMove.h GameMove.cpp GameFightInfo.h Position.h PlayerPieces.cpp PlayerPieces.h Definitions.h Board.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameMove.o: GameMove.cpp GameMove.h Move.h Point.h Position.h Definitions.h GameJokerChanged.h GameJokerChanged.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
PlayerPieces.o: PlayerPieces.cpp PlayerPieces.h Definitions.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
AutoPlayerAlgorithm.o: Definitions.h PlayerAlgorithm.h GameMove.h GameMove.cpp InterfacePiecePosition.h AlgorithmRegistration.h
	$(COMP) $(CPP_COMP_FLAG) -fPIC -c $*.cpp
GameManager.o: GameManager.cpp GameManager.h GameBoard.h PlayerAlgorithm.h AutoPlayerAlgorithm.cpp AutoPlayerAlgorithm.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameTournamentManager.o: GameTournamentManager.cpp GameTournamentManager.h PlayerAlgorithm.h GameManager.h AlgorithmRegistration.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
.PHONY: all
all: $(EXEC)
clean:
	rm -f $(OBJS) AutoPlayerAlgorithm.o RSPPlayer_222222222.so $(EXEC)