#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "helpers.c"

struct infoPacket {
    long mesg_type;
    char mesg_text[2000];
} ;
  
int main()
{   
    size_t SizeOfpacket = sizeof(struct infoPacket);
    struct infoPacket *firstMesg = malloc(SizeOfpacket);
    struct infoPacket *secondMesg = malloc(SizeOfpacket);

    int mID1;
    int mID2;
    size_t string_size = 30;
    char *rSarray[50];
    arrayRS(rSarray, 50);
    
    int index = 0;
    int x = 1;
    while(index<50){

    mID1 = msgget(ftok("progfile1", 65), 0666 | IPC_CREAT);
    mID2 = msgget(ftok("progfile2", 75), 0777 | IPC_CREAT);

    firstMesg->mesg_type = 1;

    for(int a = 0; a < 5; a++){
        strcat(firstMesg->mesg_text,rSarray[index + a]);
    }
    msgsnd(mID1, firstMesg, SizeOfpacket, 0);
    firstMesg->mesg_text[0] = '\0';

    msgrcv(mID2, secondMesg, SizeOfpacket, 2, 0);
    index = atoi(secondMesg->mesg_text) + 1;

    printf("Random strings sent %d \n",x);
    printf("Client has Sent : %d \n", atoi(secondMesg->mesg_text)+1);
    x++;
    if (index == 50){
        printf("Exit");
    }
    }
    msgctl(mID2, IPC_RMID, NULL);
    return 0;
    
}