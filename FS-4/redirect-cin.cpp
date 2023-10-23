#include<iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <algorithm>
#include <unistd.h>


void initialize(int argc, char** argv)
{
  // put your implementation here 
 char* path = argv[1];
	
 int fd = open(path, O_RDONLY);

 if(fd < 0){
	 std::cout << "file was not opend" << std::endl;
	 exit(1); 
 }
 if(dup2(fd, 0) < 0){
 	std::cout << " file was not done stdcin file" << std::endl;
 }
 close(fd);

}

int main(int argc, char** argv)
{		
	 //initialize the program based on the requirements
 if(argc != 2){
        std::cout << "invalid input" << std::endl;
	exit(1);
  }

  initialize(argc, argv);	
  // read the string 

  std::string input;
  std::cin >> input;
  
					// logic to get the reversed string  
  					// put your reversing logic here
  std::string reversed;		
  std::reverse(input.begin(), input.end());
  reversed = input;

  // print to the console
  std::string s = reversed;
  std::cout << s;

  return 0;
}

