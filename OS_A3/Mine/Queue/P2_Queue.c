#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "helpers.c"

struct infoPacket {
    long mesg_type;
    char mesg_text[2000];
} ;
  
int main()
{
    int firstmID;
    size_t sizeOfPacket = sizeof(struct infoPacket);
    struct infoPacket *msg1 = malloc(sizeOfPacket);
    struct infoPacket *msg2 = malloc(sizeOfPacket);

    int index=0;
    while(index<49){
        firstmID = msgget(ftok("progfile1", 65), 0666 | IPC_CREAT);
        
        msgrcv(msgget(ftok("progfile1", 65), 0666 | IPC_CREAT), msg1, sizeOfPacket, 1, 0);
        printf("Message Recieved - %s", msg1->mesg_text);

        msg2->mesg_type = 2;
        index = atoi(&msg1->mesg_text[strlen(msg1->mesg_text)-3]);
        printf("Value Sent to Server: %d\n",index+1);
        sprintf(msg2->mesg_text,"%d",index);

        if(msgsnd(msgget(ftok("progfile2",75), 0777 | IPC_CREAT), msg2, sizeOfPacket, 0)!=0){
            erroeandexit("Error While Sending");
        }
        msg2->mesg_text[0] = '\0';
    }
    msgctl(firstmID, IPC_RMID, NULL);  
    return 0;
}
