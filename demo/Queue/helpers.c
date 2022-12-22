#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char *getRS(size_t len){
    char Choices[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *generatedString = malloc(30);
    for (int i = 0; i < len; i++){
        generatedString[i] = Choices[rand() % (int) (sizeof Choices - 1)];
    }

    return generatedString;
}

static char *indextoString(char *generatedString, size_t len, int stringIndex){

    int tens = ((stringIndex/10)%10);
    int ones = (stringIndex%10);
    generatedString[len] = ' ';
    generatedString[len+1] = tens + '0';
    generatedString[len+2] = ones + '0';
    generatedString[len+3] = '\n';
    return generatedString;
}

static char *getRandomString(char *generatedString, size_t len,int stringIndex){
    generatedString = getRS(len);
    generatedString = indextoString(generatedString, len, stringIndex);

    return generatedString;
}

static void end(register int s){
    close(s);
}

static FILE *socketRead(register int conection){
    FILE *fp;
    fp = fdopen(conection, "r");
}

static void errorandexit(char *str){
    perror(str);
    exit(1);
}

static void arrayRS(char* popilateArray[], int lenOfArray){
    for(int i = 0; i < lenOfArray; i++){
        char *generatedString = malloc(20);
        popilateArray[i] = getRandomString(generatedString, 20, i);
    }
}

static void sendAndread(register int conection, char *listOfRS[50]){
    int stringID=0;

    while(stringID<50){
        for (int i = 0; i < 5; i++)
        send(conection, listOfRS[i], strlen(listOfRS[i]), 0);

        char num[100];
        int i=0;
        int valread = read(conection,num, 100);
        printf("Number Received - %s\n",num);
        stringID = atoi(num);
    }
}

static key_t generateKeyT(char *pathNametoUse, int projectID){
    return ftok(pathNametoUse, projectID);
}