#include <iostream>
#include <fstream>
#include "parse_board.h"
//using namespace std;

// int checkline(std::string line) {
//   std::size_t found = line.find("<");
//   if (found!=std::string::npos) {
//     std::cout << "first '<' found at: " << found << std::endl;
//     return 0;
//   } else {
//       return 1;
//   }
// }

int checkPieces

int checkline(std::string line) {
  // If joker line:
  if (line[0] == 'J') {
    if (line.length() != 10 || line[1] != "<"  || line[2] != 'J' || line[4] != "<" || line[7] != "<" ||
       line[3] != ">" || line[6] != ">" || line[9] != ">") {
      std::cout << "Format error in board file." << std:endl;
      return 1;
    } else {
      return 0;
    }
  }
  // If not joker line:
  if (line.length() != 9 || line[0] != "<"  || line[1] == 'J' || line[3] != "<" || line[6] != "<" ||
       line[2] != ">" || line[5] != ">" || line[8] != ">") {
    std::cout << "Format error in board file." << std:endl;
      return 1;
  } else {
    return 0;
  }
}


// int read_from_file () {
int main (int argc, char* argv[]) {
  std::string line;
  int res = -1;
  std::ifstream myfile (argv[1]);
  if (myfile.is_open()) {
    while (getline (myfile,line)) {     //getline returns a reference to myfile
      res = checkline(line);
    }
    myfile.close();
  }
  else {
      std::cout << "Unable to open file" << std::endl; 
      return 1;
  }
  std::cout << "res is: " << res << std::endl;
  return 0;
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