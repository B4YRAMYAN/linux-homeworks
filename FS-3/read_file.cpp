#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
  std::fstream file(argv[1], std::ios::in);
  std::string tmp;
  while (getline(file, tmp)) {
    std::cout << tmp << std::endl;
  }
}
