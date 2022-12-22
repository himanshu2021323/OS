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

    generatedString[len] = ' ';
    return generatedString;
}

static char *indestoString(char *generatedString, size_t len, int stringIndex){
    int tens = ((stringIndex/10)%10);
    int lengthOftens = snprintf( NULL, 0, "%d", tens);
    char* tensAsString = malloc( lengthOftens + 1 );
    snprintf( tensAsString, lengthOftens + 1, "%d", tens );

    int ones = (stringIndex%10);
    int lengthOfones = snprintf( NULL, 0, "%d", ones);
    char* onesAsString = malloc( lengthOfones + 1 );
    snprintf( onesAsString, lengthOfones + 1, "%d", tens );

    generatedString[len+1] = tens + '0';
    generatedString[len+2] = ones + '0';
    generatedString[len+3] = '\n';

    return generatedString;
}

static char *getRandomString(char *generatedString, size_t len,int stringIndex){
    generatedString = getRS(len);
    generatedString = indestoString(generatedString, len, stringIndex);
    return generatedString;

}

static void end(register int s){
    close(s);
}

static FILE *socketRead(register int connection){
    FILE *fp;
    fp = fdopen(connection, "r");
}

static void errorandexit(char *str){
    perror(str);
    exit(1);
}

static void arrayRS(char* arrayToPopulate[], int lenOfArray){
    for(int i = 0; i < lenOfArray; i++){
        char *generatedString = malloc(20);
        arrayToPopulate[i] = getRandomString(generatedString, 20, i);
    }
}

static void sendAndread(register int connection, char *listOfRS[50]){
    int stringID=0;

    while(stringID<50){
        for (int i = 0; i < 5; i++)
        send(connection, listOfRS[i], strlen(listOfRS[i]), 0);

        char number[100];
        int i=0;
        int valread = read(connection,number, 100);
        printf("Number Received- %s\n",number);
        stringID = atoi(number);
    }
}