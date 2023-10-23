#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
  std::fstream source_file(argv[1], std::ios::in);
  std::fstream distination_file(argv[2], std::ios::out);

  std::string tmp;
  while (getline(source_file, tmp)) {
    distination_file << tmp;
  }
}
