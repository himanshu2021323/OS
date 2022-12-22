#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "helpers.c"

int main()
{
    int fd;
    char *random_Str[50];
    char * myfifo = "/tmp/myfifo";

    for(int i = 0; i<50; i++){
        random_Str[i] = getRS(5);
        if(i <= 9){
            sprintf(random_Str[i],"%s 0%d\n",random_Str[i],i);
        }
        else{ 
            sprintf(random_Str[i],"%s %d\n",random_Str[i],i);
        }

        random_Str[i][8]= '\n';
        random_Str[i][9]= '\0';
    }

    mkfifo(myfifo, 0666);

    char s1[1000];
    char **s2 = malloc(10000);

    int index = 0;
    while (index < 50)
    {
        s2 = random_Str;
        fd = open(myfifo, O_WRONLY);

        for(int a = 0; a < 5; a++){
            write(fd, *(s2+index+a), strlen(*s2));
        }
        
        close(fd);

        fd = open(myfifo, O_RDONLY);

        read(fd, s1, sizeof(s1));
        index = atoi(s1)+1;
        printf("Client sent by: %s\n", s1);

        close(fd);
    }
    unlink(myfifo);
    exit(0);
}