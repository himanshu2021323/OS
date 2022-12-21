#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>


char* retRandomString(){
	char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *strGenerated = (char*)calloc(5, sizeof(char));
	for(int i=0; i<4; i++){
		strGenerated[i] = letters[rand()%(52)];
	}
	return strGenerated;
}

char* copyString(char *src, int start){
	char *ptr = (char*)calloc(26, sizeof(char));
	ptr[25] = '\0';
	for (int i = start; i<start+25; i++){
		ptr[i%25] = src[i];
	}
	return ptr;
}

void pasteString(char* dest, char *src, int fromPos){
	for(int i = 0; i<5; i++){
		dest[fromPos+i] = src[i];
	}
}

int main(int argc, char* argv[]){

	srand(time(NULL));
	int loc4copy = 0;
	int loc4paste = 0;
	int intRecieved;
	char* strings = (char*)calloc(251, sizeof(char));
	strings[250]= '\0';
	int help = 65;
	
	
	
	if(mkfifo("sendThroughFifo", 0777)==-1){
		printf("failed to creation of the error file\n");
		return 1;
	}
	
	
	int fd = open("sendThroughFifo", O_WRONLY);
	if(fd<0){
		printf("failed to create the file\n");
		return 1;
	}

	for(int i = 0; i<50; i++){
		char *ptr1 = retRandomString();
		ptr1[4] = help;
		pasteString(strings, ptr1, loc4paste);
		loc4paste += 5;
		help++;
		free(ptr1);
	}
	
	for(int k = 0; k<10; k++){

		char *buffer = copyString(strings, loc4copy);
		loc4copy += 25;
		if(write(fd, buffer, 26)<0){
			printf("failed to write into the file\n");
			return 1;
		}
		sleep(1);
		int fd2 = open("ackThroughFifo", O_RDONLY);
		if(fd2<0){
			printf("failed to open the file\n");
			return 1;
		}
		if(read(fd2, &intRecieved, sizeof(int))<0){
			printf("failed to read the file\n");
			return 1;
		}else{
			printf("number recieved for the acknowledgement:%d\n", intRecieved);
		}
		free(buffer);
	}
	return 0;
}
