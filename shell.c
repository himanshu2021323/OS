#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <libgen.h> 
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <dirent.h>
//#include "ls.c"
// #include "date.c"
// #include "cat.c"
// #include "mkdir.c"
// #include "rm.c"


int main(){
	int max_size = 100;
	
	char line[max_size];
	int ctr=0;

	char root_folder[100];
	getcwd(root_folder,sizeof(root_folder));

	while (1){
		printf("myShell>>>");
		fgets(line,max_size,stdin);
		

		if(line==NULL){
			break;
		}

		char *history[100];
		history[ctr]=strdup(line);
		
		ctr++;
		

		char root[100];
		strcpy(root,root_folder);
		char *final=line;
		char *inCmd[3];
		
		inCmd[1]="cd";
		inCmd[2]="pwd";
		
		inCmd[3]="echo";

		int command_check=0;

		char *present_dir;
		char curr_path[100];
		char buff[1000];
	

		char *tkn=NULL;
		tkn=strtok(line," ");
		
		char *exec[100];
		int i=0;
		
		
		while(tkn !=NULL){
			exec[i] = (char *) malloc(strlen(tkn)+1);
			strcpy(exec[i],tkn);
			
			tkn=strtok(NULL," ");
			i++;
		}
		
		exec[i]=NULL;
		

		
		if(strcmp(exec[0],inCmd[1])==0){

			command_check=1;
			if(exec[1]==NULL){
				chdir("/home/verma");
			}
			else{
				int check=chdir(exec[1]);
				present_dir=getcwd(buff,sizeof(buff));
				//printf("cd %s cmd\n",exec[1] );
				if(check==-1){
					printf("Invalid path\n");
				}
			}
			

		}
		else if(strcmp(exec[0],inCmd[2])==0){
			command_check=1;
			getcwd(curr_path,sizeof(curr_path));
			printf("current working directory : %s\n", curr_path);
			printf("pwd cmd\n" );
		}
		
		else if(strcmp(exec[0],inCmd[3])==0){
			command_check=1;
			if(exec[1]==NULL){
				printf("\n");
			}
			else if(strcmp(exec[1],"-n")==0){

			}
			else{
				i=1;
				
				while(exec[i]!= NULL){
					printf("%s",exec[i] );
					i++;
				}
				printf("\n");
				
			}
		}

		
		
		
		if(fork()==0){
			
			if(strcmp(exec[0],"ls")==0){
				
					strcat(root,"/ls");
					execv(root,exec);
					
			}


			else if(strcmp(exec[0],"cat")==0){
				
					strcat(root,"/catto");
					execv(root,exec);
					
					
			}


			else if(strcmp(exec[0],"rm")==0){
				if(exec[1]==NULL){
					printf("Enter a name\n");
				}
				else{
					strcat(root,"/rem");
					execv(root,exec);
					
				}
			}


			else if(strcmp(exec[0],"date")==0){
				
				strcat(root,"/dato");
				execv(root,exec);
				
			}


			else if(strcmp(exec[0],"mkdir")==0){
				
				strcat(root,"/mak");
				execv(root,exec);
				
			}
			else {
				if(command_check==0)
					printf("Command not found\n");
			}
			exit(0);

		}
		else{
			wait(NULL);
		}

	}
	return 0;
}
