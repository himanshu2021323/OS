#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
int main()
{
pid_t pid;
int i,j;
struct timespec start,finish;
clock_gettime(CLOCK_REALTIME,&start);
for(i=0;i<3;i++)
{
 pid=fork();
 if(pid==0)
 {
  if(i==0)
   execl("/bin/sh","sh","script1.sh",(char*)NULL);
  if(i==1)
   execl("/bin/sh","sh","script2.sh",(char*)NULL);
  if(i==2)
   execl("/bin/sh","sh","script3.sh",(char*)NULL);
 }
}
for(j=0;j<3;j++)
 wait(NULL);
clock_gettime(CLOCK_REALTIME,&finish);
double elapsed=finish.tv_sec-start.tv_sec;
elapsed+=(finish.tv_nsec-start.tv_nsec)/1000000000.0;
printf("Time taken to compile the Linux kernel: %lf seconds\n",elapsed);
return 0;
}