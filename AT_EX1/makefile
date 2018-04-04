COMP = g++-5.3.0
#put all your object files here
OBJS = GameBoard.o move.o playerPieces.o parseBoard.o gamePlayed.o
#The executabel filename DON'T CHANGE
EXEC = ex1
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG
gcc
$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
main.o: main.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameBoard.o: GameBoard.cpp GameBoard.h GameBoard.cpp Move.h Move.cpp Position.h PlayerPieces.h PlayerPieces.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
move.o: Move.h Move.cpp Position.h Definitions.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
playerPieces.o: PlayerPieces.cpp PlayerPieces.h Definitions.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
parseBoard.o: parse_board.cpp parse_board.h Definitions.h Position.h GameBoard.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
gamePlayed.o: gamePlayed.cpp gamePlayed.h Move.h parse_board.h GameBoard.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)