COMP = g++-5.3.0
#put all your object files here
OBJS = GameBoard.o Move.o PlayerPieces.o parse_board.o GamePlayed.o
#The executabel filename DON'T CHANGE
EXEC = ex1
CPP_COMP_FLAG = -std=c++11 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
main.o: main.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameBoard.o: GameBoard.cpp GameBoard.h Move.h Move.cpp Position.h PlayerPieces.cpp PlayerPieces.h 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Move.o: Move.cpp Move.h Position.h Definitions.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
PlayerPieces.o: PlayerPieces.cpp PlayerPieces.h Definitions.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
parse_board.o: parse_board.cpp parse_board.h Definitions.h Position.h GameBoard.cpp GameBoard.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GamePlayed.o: GamePlayed.cpp GamePlayed.h Move.cpp Move.h parse_board.cpp parse_board.h GameBoard.cpp GameBoard.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)