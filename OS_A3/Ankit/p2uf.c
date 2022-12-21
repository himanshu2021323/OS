#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	int maxInd = -1;
	int fd = open("sendThroughFifo", O_RDONLY);
	if(fd<0){
		printf("failed to open the file\n");
		return 1;
	}
	if(mkfifo("ackThroughFifo", 0777)==-1){
		printf("failed to create the fifo file\n");
		return 1;
	}
	int count = 0;
	for(int k = 0; k<10; k++){
		char *buffer = (char*)calloc(26, sizeof(char));
		if(read(fd, buffer, 26)<0){
			printf("failed to read the file\n");
			return 1;
		}
		int i = 0;
		printf("---String Set No:%d---\n",k+1);
		while(i<26){
			if((i+1)%5 != 0 || i==0){
				printf("%c", buffer[i]);
			}else{
				if(maxInd<(int)buffer[i]){
					maxInd = (int)buffer[i]-65;
				}
				printf(", ID:%d\n", maxInd);
			}
			i++;
		}
		printf("-------------------------\n");

		int fd2 = open("ackThroughFifo", O_WRONLY);
		if(fd2<0){
			printf("failed to open the file\n");
			return 1;
		}
		if(write(fd2, &maxInd, sizeof(int))==-1){
			printf("failed to write into the file\n");
			return 1;
		}
	}
	sleep(1);
	return 0;
}
