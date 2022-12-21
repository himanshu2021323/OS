#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <time.h>


#define SOCK_PATH "unix_sock.server"

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
    int server_sock, client_sock, len, rc;
    int bytes_rec = 0;
    struct sockaddr_un server_sockaddr;
    struct sockaddr_un client_sockaddr;
    char *buffer = (char*)calloc(26, sizeof(char));
    int backlog = 1;
    memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));
    memset(&client_sockaddr, 0, sizeof(struct sockaddr_un));
    


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


	server_sock = socket (AF_UNIX, SOCK_SEQPACKET, 0);
	if(server_sock<0){
		perror("Failed to create the sockets\n");
		exit(1);
	}

    server_sockaddr.sun_family = AF_UNIX;
    strcpy(server_sockaddr.sun_path, SOCK_PATH);
    len = sizeof(server_sockaddr);

    unlink(SOCK_PATH);

    if(bind(server_sock, (struct sockaddr *)&server_sockaddr, len)<0){
		perror("bind failed\n");
		exit(1);
	}

    if(listen(server_sock, backlog)<0){
        printf("can't listen to client\n");
        exit(1);
    }

    client_sock = accept(server_sock, (struct sockaddr *) &client_sockaddr, &len);
    
    if(client_sock==-1){
        printf("cant accept the client\n");
        exit(1);
    }

    len = sizeof(client_sockaddr);
    rc = getpeername(client_sock, (struct sockaddr *) &client_sockaddr, &len);
    if(rc==-1){
        printf("can't get the peer name\n");
        close(server_sock);
        close(client_sock);
        exit(1);
    }
    

    memset(buffer, 0, 26);
    
    
    for(int k = 0; k<10; k++){
        buffer = copyString(strings, loc4copy);
		loc4copy += 25;
		if(send(client_sock, buffer, 26, 0)<0){
			perror("Send failed\n");
			close(client_sock);
			exit(1);
		}
		sleep(1);
		if(recv(client_sock, &intRecieved, sizeof(int), 0)<0)  
 			perror("reading stream message error");
 		else
			printf("number recieved for the acknowledgement:%d\n", intRecieved);
        free(buffer);
	}


    close(server_sock);
    close(client_sock);
    return 0;
}