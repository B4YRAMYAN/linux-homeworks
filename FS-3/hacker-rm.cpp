#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>


int main(int argc, char* argv[]){
	if(argc != 2){
		std::cout<<"invalid input" << std::endl;
		exit(1);
	}
	char* path = argv[1];
	
	int fd = open(path, O_WRONLY);
	if (fd == -1) {
		std::cout <<"file was not opend" << std::endl;
        	exit(1);
	}
	struct stat filesInfo;
	if (lstat(path, &filesInfo) == -1) {
		std::cout <<"invalid files information" << std::endl;
                exit(1);
        }
	char tmp = 0;

	for(unsigned i = 0; i < filesInfo.st_size; ++i){
		if(write(fd, &tmp, 1) != 1){
			std::cout << "error in time change all cahrs to 0" << std::endl;
			exit(1);
		}
	}
	close(fd);

    	if (unlink(path) == -1) {
        	std::cout << "error in time deleting" << std::endl;
        	exit(1);
   	}

	
}
