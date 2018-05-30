COMP = g++-5.3.0
#put all your object files here
OBJS = main.o AutoPlayerAlgorithm.o GameBoard.o GameJokerChanged.o GameManager.o GameMove.o PlayerPieces.o GameTournamentManager.o
#The executabel filename DON'T CHANGE
EXEC = ex3
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG -fPIC
#CPP_SO_FLAGS = AutoPlayerAlgorithm.o  -shared -o libAutoPlayerAlgorithm.so
CPP_SO_FLAGS = -shared -o
LDFLAGS = -ldl
all: ex3 libAutoPlayerAlgorithm.so 


$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -rdynamic -o $@ -ldl
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
AutoPlayerAlgorithm.o: Definitions.h PlayerAlgorithm.h GameMove.h GameMove.cpp InterfacePiecePosition.h AlgorithmRegistration.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
libAutoPlayerAlgorithm.so: AutoPlayerAlgorithm.o
	$(COMP) $(CPP_SO_FLAGS) $*.o
GameManager.o: GameManager.cpp GameManager.h GameBoard.h PlayerAlgorithm.h AutoPlayerAlgorithm.cpp AutoPlayerAlgorithm.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameTournamentManager.o: GameTournamentManager.cpp GameTournamentManager.h PlayerAlgorithm.h GameManager.h AlgorithmRegistration.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

clean:
	rm -f $(OBJS) $(EXEC)