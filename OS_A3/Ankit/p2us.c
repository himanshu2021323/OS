#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <sys/wait.h>

#define SERVER_PATH "unix_sock.server"
#define CLIENT_PATH "unix_sock.client"

int main(int argc, char *argv[]){
    int client_sock, len, rc;
    int bytes_rec = 0;
    struct sockaddr_un server_sockaddr;
    struct sockaddr_un client_sockaddr;
    char buffer[26];

    memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));
    memset(&client_sockaddr, 0, sizeof(struct sockaddr_un));

	client_sock = socket (AF_UNIX, SOCK_SEQPACKET, 0);
    
	if(client_sock<0){
		perror("Failed to create the sockets\n");
		exit(1);
	}

    client_sockaddr.sun_family = AF_UNIX;
    strcpy(client_sockaddr.sun_path, CLIENT_PATH);
    len = sizeof(client_sockaddr);

    unlink(CLIENT_PATH);

    if(bind(client_sock, (struct sockaddr *)&client_sockaddr, len)<0){
		perror("bind failed\n");
		exit(1);
	}


    server_sockaddr.sun_family = AF_UNIX;
    strcpy(server_sockaddr.sun_path, SERVER_PATH);

    if(connect(client_sock, (struct sockaddr *) &server_sockaddr, len)<0){
        printf("can't connect to the server\n");
        exit(1);
    }

    int maxInd = -1;
    
    for(int k = 0; k<10; k++){
	    if(recv(client_sock, buffer, 26, 0)<0)
		    perror("reading stream message error");
		else{
            int i = 0;
            printf("---String Set No:%d---\n",k+1);
            while(i<26){
                if((i+1)%5 != 0 || i==0){
                    printf("%c", buffer[i]);
                }else{
                    
                    if(maxInd<(int)buffer[i]){
                        maxInd = (int)buffer[i]-65;
                    }
                    printf(", ID:%d\n", maxInd);
                }
                i++;
            }
            printf("-------------------------\n");
            if(send(client_sock, &maxInd, sizeof(int), 0)<0){
                perror("Send failed\n");
                close(client_sock);
                exit(1);
            }
        }
	}
    
    close(client_sock);
    return 0;
}
