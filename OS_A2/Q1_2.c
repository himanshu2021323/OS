#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
int main()
{
    pid_t pid1, pid2, pid3;
    int i, j;
    struct timespec start1, finish1;
    clock_gettime(CLOCK_REALTIME, &start1);
    pid1 = fork();
    if (pid1 == 0)
    {
        execl("/bin/sh", "sh", "script1.sh", (char *)NULL);
    }
    else {
        int status;
        waitpid(pid1, &status, 0);
        clock_gettime(CLOCK_REALTIME, &finish1);
        
        struct timespec start2, finish2;
        clock_gettime(CLOCK_REALTIME, &start2);
        pid2 = fork();
        if(pid2 == 1)
        {
            execl("/bin/sh", "sh", "script2.sh", (char *)NULL);
        }
        else{
            int status2;
            waitpid(pid2, &status2, 0);
            clock_gettime(CLOCK_REALTIME, &finish2);
           
            struct timespec start3, finish3;
            clock_gettime(CLOCK_REALTIME, &start3);
            pid3 = fork();
            if (pid3 == 2)
            {
                execl("/bin/sh", "sh", "script3.sh", (char *)NULL);
            }
            else{
                int status3;
                waitpid(pid3, &status3, 0);
                clock_gettime(CLOCK_REALTIME, &finish3);

                double time = finish1.tv_sec - start1.tv_sec;
                time += (finish1.tv_nsec - start1.tv_nsec) / 1000000000.0;
                printf("Time taken to compile the Linux kernel: %lf seconds\n", time);

                double time = finish2.tv_sec - start2.tv_sec;
                time += (finish2.tv_nsec - start2.tv_nsec) / 1000000000.0;
                printf("Time taken to compile the Linux kernel: %lf seconds\n", time);

                double time = finish3.tv_sec - start3.tv_sec;
                time += (finish3.tv_nsec - start3.tv_nsec) / 1000000000.0;
                printf("Time taken to compile the Linux kernel: %lf seconds\n", time);

            }
        }
    }
    return 0;
}
