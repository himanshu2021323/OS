#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "helpers.c"

int main()
{
    int file1;
    char * myfifo = "/tmp/myfifo";
    mkfifo(myfifo, 0666);
    int i = 0;
    char s1[1000] = {0}; 
    char *s2 = malloc(1000);
    while (i<49)
    {
        file1 = open(myfifo,O_RDONLY);
        read(file1, s1, 1000);
        printString(i, s1);

        close(file1);
        int len = strlen(s1);

        const char *index = &s1[len-3];
        i = atoi(index);
        file1 = open(myfifo,O_WRONLY);
        sprintf(s2, "%d",i);
        
        write(file1, s2, strlen(s2)+1);
        close(file1);
    }
    unlink(myfifo);
    exit(0);
}