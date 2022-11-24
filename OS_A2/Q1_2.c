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
    struct timespec start, finish;
    clock_gettime(CLOCK_REALTIME, &start);
    pid = fork();
    if (pid == 0)
    {
        execl("/bin/sh", "sh", "script1.sh", (char *)NULL);
        clock_gettime(CLOCK_REALTIME, &finish);
        double time = finish.tv_sec - start.tv_sec;
        time += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
        printf("Time taken to compile the Linux kernel: %lf seconds\n", time);
    }
    else {
        pid1 = fork();
        if(pid1 == 1)
        {
            execl("/bin/sh", "sh", "script2.sh", (char *)NULL);
            clock_gettime(CLOCK_REALTIME, &finish);
            double time = finish.tv_sec - start.tv_sec;
            time += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
            printf("Time taken to compile the Linux kernel: %lf seconds\n", time);
        }
        else{
            pid2 = fork();
            if (pid2 == 2)
            {
            execl("/bin/sh", "sh", "script3.sh", (char *)NULL);
            clock_gettime(CLOCK_REALTIME, &finish);
            double time = finish.tv_sec - start.tv_sec;
            time += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
            printf("Time taken to compile the Linux kernel: %lf seconds\n", time);
            }
        }
    }
    return 0;
}
