#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "helpers.c"

#define ADDRESS     "Sockets"

int main()
{
    char c;
    FILE *fp;
    int fromlen;
    register int connection ;
    register int endPoint;
    register int sizeofAddressofHost;
    struct sockaddr_un addressofHost;
    struct sockaddr_un addressOfClient;
    
    char *listOfRS[50];
    arrayRS(listOfRS, 50);

    if ((endPoint = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        errorandexit("Error in Server's Socket");
    }

    addressofHost.sun_family = AF_UNIX;
    strcpy(addressofHost.sun_path, ADDRESS);

    unlink(ADDRESS);
    sizeofAddressofHost = sizeof(addressofHost.sun_family) + strlen(addressofHost.sun_path);

    if (bind(endPoint,(struct sockaddr *)&addressofHost, sizeofAddressofHost) < 0) {
        errorandexit("Error While Trying to Bind to Server");
    }

    if (listen(endPoint, 3) < 0) {
        errorandexit("Error While Trying to Listen to Socket");
    }

    if ((connection  = accept(endPoint, (struct sockaddr *)&addressOfClient, &fromlen)) < 0) {
        errorandexit("Error While Trying to Accept Connection");
    }

    fp = socketRead(connection );
    sendAndread(connection ,listOfRS);
    end(endPoint);
    exit(0);
}
