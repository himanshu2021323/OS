#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
int main()
{
    pid_t pid1;
    pid_t pid2;
    pid_t pid3;
    int i;
    int j;
    struct timespec begin1, end1;
    clock_gettime(CLOCK_REALTIME, &begin1);
    pid1 = fork();
    if (pid1 == 0)
    {
        execl("/bin/sh", "sh", "script1.sh", (char *)NULL);
    }
    else {
        int ptr;
        waitpid(pid1, &ptr, 0);
        clock_gettime(CLOCK_REALTIME, &end1);
        
        struct timespec begin2, end2;
        clock_gettime(CLOCK_REALTIME, &begin2);
        pid2 = fork();
        if(pid2 == 0)
        {
            execl("/bin/sh", "sh", "script2.sh", (char *)NULL);
        }
        else{
            int ptr2;
            waitpid(pid2, &ptr2, 0);
            clock_gettime(CLOCK_REALTIME, &end2);
            
            struct timespec begin3, end3;
            clock_gettime(CLOCK_REALTIME, &begin3);
            pid3 = fork();
            if (pid3 == 0)
            {
                execl("/bin/sh", "sh", "script3.sh", (char *)NULL);
            }
            else{
                int ptr3;
                waitpid(pid3, &ptr3, 0);
                clock_gettime(CLOCK_REALTIME, &end3);
                
                double time1 = end1.tv_sec - begin1.tv_sec;
                time1 += (end1.tv_nsec - begin1.tv_nsec) / 1000000000.0;
                printf("Time taken to compile the Linux kernel: %lf seconds\n", time1);

                double time2 = end2.tv_sec - begin2.tv_sec;
                time2 += (end2.tv_nsec - begin2.tv_nsec) / 1000000000.0;
                printf("Time taken to compile the Linux kernel: %lf seconds\n", time2);
                
                double time3 = end3.tv_sec - begin3.tv_sec;
                time3 += (end3.tv_nsec - begin3.tv_nsec) / 1000000000.0;
                printf("Time taken to compile the Linux kernel: %lf seconds\n", time3);

            }
        }
    }
    return 0;
}
