#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <time.h>


struct msgContainer{
    long int msg_type;
    char msg[26];
};

struct msgContainerForInt{
    long int msg_type;
    char msgI[2];
};

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

int main(int argc, char *argv[]){

    srand(time(NULL));
	int loc4copy = 0;
	int loc4paste = 0;
	int intRecieved;
	char* strings = (char*)calloc(251, sizeof(char));
	strings[250]= '\0';
    int help = 65;


    for(int i = 0; i<50; i++){
		char *ptr1 = retRandomString();
		ptr1[4] = help;
		pasteString(strings, ptr1, loc4paste);
		loc4paste += 5;
		help++;
		free(ptr1);
	}


    struct msgContainer myMsg;
    struct msgContainerForInt myInt;

    long int msgRecpriority = 0;
    int msgid = msgget((key_t)1234, 0777|IPC_CREAT);
    int msgidForInt = msgget((key_t)12347, 0777|IPC_CREAT);

    if(msgid==-1 || msgidForInt ==-1){
        printf("Error in creating the queue\n");
    }
    myMsg.msg_type = 1;

	for(int k = 0; k<10; k++){

		char *buffer = copyString(strings, loc4copy);
		loc4copy += 25;

        strcpy(myMsg.msg, buffer);
        if(msgsnd(msgid, (void *)&myMsg, 26, 0)==-1){
            printf("msg not sent\n");
        }        
        
		msgrcv(msgidForInt, (void *)&myInt, 2, msgRecpriority, 0);
        printf("the number recieved for the acknowledgement:%d\n", (int)myInt.msgI[0]-65);
        bzero(myMsg.msg, 26);
        bzero(myInt.msgI, 2);
		
	}
    msgctl(msgidForInt, IPC_RMID, 0);
    return 0;
}
