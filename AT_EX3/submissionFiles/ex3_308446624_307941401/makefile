COMP = g++-5.3.0
#put all your object files here
OBJS = main.o GameBoard.o GameJokerChanged.o GameManager.o GameMove.o PlayerPieces.o GameTournamentManager.o
#The executabel filename DON'T CHANGE
EXEC = ex3
SO_NAME = RSPPlayer_308446624
SO_OBJS = AutoPlayerAlgorithm.o GameBoard.o GameMove.o PlayerPieces.o GameJokerChanged.o
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra -Werror -pedantic-errors -g
CPP_SO_FLAGS = -shared -o
all: ex3 RSPPlayer_308446624.so
rps_tournament: $(EXEC)
rps_lib: $(SO_NAME).so

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -rdynamic -ldl -pthread -g -o $@
$(SO_NAME).so: $(SO_OBJS)
	$(COMP) $(SO_OBJS) -shared -g -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
main.o: main.cpp GameManager.cpp GameManager.h GameTournamentManager.cpp GameTournamentManager.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp -ldl
GameBoard.o: GameBoard.cpp GameBoard.h GameMove.h GameMove.cpp GameFightInfo.h Position.h PlayerPieces.cpp PlayerPieces.h Definitions.h Board.h
	$(COMP) $(CPP_COMP_FLAG) -fPIC -c $*.cpp
GameMove.o: GameMove.cpp GameMove.h Move.h Point.h Position.h Definitions.h GameJokerChanged.h GameJokerChanged.cpp
	$(COMP) $(CPP_COMP_FLAG) -fPIC -c $*.cpp
GameJokerChanged.o: GameJokerChanged.cpp GameJokerChanged.h Definitions.h Position.h 
	$(COMP) $(CPP_COMP_FLAG) -fPIC -c $*.cpp
PlayerPieces.o: PlayerPieces.cpp PlayerPieces.h Definitions.h
	$(COMP) $(CPP_COMP_FLAG) -fPIC -c $*.cpp
AutoPlayerAlgorithm.o: Definitions.h PlayerAlgorithm.h GameBoard.h GameBoard.cpp InterfacePiecePosition.h AlgorithmRegistration.h
	$(COMP) $(CPP_COMP_FLAG) -fPIC -c $*.cpp
GameManager.o: GameManager.cpp GameManager.h GameBoard.h PlayerAlgorithm.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameTournamentManager.o: GameTournamentManager.cpp GameTournamentManager.h PlayerAlgorithm.h GameManager.h AlgorithmRegistration.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
.PHONY: all
all: $(EXEC)
clean:
	rm -f $(OBJS) AutoPlayerAlgorithm.o RSPPlayer_308446624.so $(EXEC)