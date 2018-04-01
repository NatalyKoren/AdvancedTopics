/*
 * ParseBoardUnitTest.cpp
 *
 *  Created on: Mar 30, 2018
 *      Author: liron
 */
#include "parse_board.h"

int main(int argc, char** argv) {
	ParseBoard parser;
	std::string filename = argv[1];
	int res = parser.parseBoardFile(filename);
	if (res == 0) {
		std::cout << "All good!" << std::endl;
	} else {
		std::cout << "Uh oh, we have a problem" << std::endl;
	}
	return res;
}

/*
 *  Successfully tested on:
 *  1. no rocks (valid board)
 *  2. no flag (invalid board)
 *  3. Randomly placed white spaces (valid & invalid boards)
 *  4. 2 pieces on same square (invalid board)
 *  5. Joker without specifying replacement piece (invalid board)
 *  6. Position index not in range (invalid board)
 *
 */

