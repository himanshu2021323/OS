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
    FILE *fp;
    register int endPoint, sizeofAddressofHost;
    struct sockaddr_un addressofHost;

    if ((endPoint = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        errorandexit("Error in Client's Socket");
    }

    addressofHost.sun_family = AF_UNIX;
    strcpy(addressofHost.sun_path, ADDRESS);

    sizeofAddressofHost = sizeof(addressofHost.sun_family) + strlen(addressofHost.sun_path);

    if (connect(endPoint, (struct sockaddr *)&addressofHost, sizeofAddressofHost) < 0) {
        errorandexit("Error While Trying to Connect to Client");
    }

    fp = socketRead(endPoint);
    int num = 0;

    while(num<50){
        char arr[1000];
        int j = 0;
        char temp;

        for (int i = 0; i < 5; i++) {
            while ((temp = fgetc(fp)) != EOF) {
                putchar(temp);
                if (temp == '\n')
                    break;
                arr[j] = temp;
                j++;
            }
        }
        num = (arr[j-2] -'0')*10  + (arr[j-1] -'0');
        printf("Number Received- %d\n",num);

        num += 1;

        char StringSentBack[200];
        sprintf(StringSentBack, "%d", num);

        printf("String - %s \n",StringSentBack);
        send(endPoint, StringSentBack, 2, 0);
    }

    end(endPoint);
    exit(0);
}