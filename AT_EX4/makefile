COMP = g++-5.3.0
#put all your object files here
OBJS = main.o
#The executabel filename DON'T CHANGE
EXEC = ex4
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra -Werror -pedantic-errors -g

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -g -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
main.o: main.cpp GameBoard.h ex4_header.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

.PHONY: all
all: $(EXEC)
clean:
	rm -f $(OBJS) $(EXEC)