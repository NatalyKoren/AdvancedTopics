#include <iostream>
#include <fstream>
#include "Definitions.h"
#include "parse_board.h"
//using namespace std;

// int checkLin (std::string line) {
//   std::size_t found = line.find("<");
//   if (found!=std::string::npos) {
//     std::cout << "first '<' found at: " << found << std::endl;
//     return 0;
//   } else {
//       return 1;
//   }
// }

int ParseBoard::checkPieces() {
  for (int i = 0; i < sizeof(pieceCount); i++) {
    if (pieceCount[i] < 0) {
      std::cout << "Board file format error: too many pieces of same type." << std::endl;
      return curPlayer;
    }
    if (pieceCount[-1] > 0) {
      std::cout << "Board file format error: flag not placed on board." << std::endl;
      return curPlayer;
    }
  }
  return 0;
}

void ParseBoard::updatePieceCount (std::string line) {
  switch(line[1]) {
    case 'R': pieceCount[0]--;
    break;
    case 'P': pieceCount[1]--;
    break;
    case 'S': pieceCount[2]--;
    break;
    case 'B': pieceCount[3]--;
    break;
    case '<': pieceCount[4]--; //this is the joker
    break;
    case 'F': pieceCount[5]--;
    break;
  }
}

int ParseBoard::checkLine (std::string line) {
  // If joker line:
  if (line[0] == 'J') {
    if (line.length() != 10 || line[1] != "<"  || line[2] != 'J' || line[4] != "<" || line[7] != "<" ||
      line[3] != ">" || line[6] != ">" || line[9] != ">") {
      std::cout << "Format error in board file." << std:endl;
      return curLine;
    } else {
      return 0;
    }
  }
  // If not joker line:
  if (line.length() != 9 || line[0] != "<"  || line[1] == 'J' || line[3] != "<" || line[6] != "<" ||
      line[2] != ">" || line[5] != ">" || line[8] != ">") {
    std::cout << "Format error in board file." << std:endl;
      return curLine;
  } else {
    return 0;
  }
}

// gets line, checks format, calls all aiding functions
int ParseBoard::parseBoardFile (std::string filename) {
  std::string line;
  int res = -1;
  std::ifstream myfile (filename);
  if (myfile.is_open()) {
    curPlayer = filename[6] - '0'; // gets the int value of the char
    while (getline (myfile,line)) {     //getline returns a reference to myfile
      curLine++;
      res = checkLine (line);
      if (res == 0) {
        updatePieceCount (line);
      } else {
        return res;
      }
    }
    myfile.close();
    res = checkPieces();
  }
  else {
      std::cout << "Unable to open file" << std::endl; 
      return 1;
  }
  std::cout << "res is: " << res << std::endl;
  return res;
}



// int main () {
//   std::ofstream myfile ("example.txt");

//   // Is this check necessary?
//   if (!(myfile.is_open())) {
//       std::cout << "Error opening file, exiting." << std::endl;
//       return 1;
//   }
//   myfile << "Writing this to a file." << std::endl;
//   myfile.close();
//   int res = read_from_file();
//   std::cout << "Finished running code. Res is: " << res << std::endl;
//   return 0;
// }