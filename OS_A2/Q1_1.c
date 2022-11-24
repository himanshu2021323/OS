#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

#define count 4294967296

int A, B, C;

void *countA(void *arg);
void *countB(void *arg);
void *countC(void *arg);

void *countA(void *arg)
{
    int i = 1;
    struct timeval start, end;

    pthread_setschedparam(pthread_self(), SCHED_OTHER, 0);

    gettimeofday(&start, NULL);

    while(i<=count){
        A++;
        i++;
    }

    gettimeofday(&end, NULL);

    unsigned long time = ((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec);

    printf("Thread 1 completed in %ld microseconds", time);
    printf("\n");

    pthread_exit(NULL);
}

void *countB(void *arg)
{
    int i = 1;
    struct timeval start, end;

    pthread_setschedparam(pthread_self(), SCHED_RR, 0);


    gettimeofday(&start, NULL);

    while(i<=count){
        B++;
        i++;
    }

    gettimeofday(&end, NULL);

    unsigned long time = ((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec);

    printf("Thread 2 completed in %ld microseconds", time);
    printf("\n");

    pthread_exit(NULL);
}

void *countC(void *arg)
{
    int i = 1;
    struct timeval start, end;

    pthread_setschedparam(pthread_self(), SCHED_FIFO, 0);

    gettimeofday(&start, NULL);

    while(i<=count){
        C++;
        i++;
    }

    gettimeofday(&end, NULL);

    unsigned long time = ((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec);

    printf("Thread 3 completed in %ld microseconds", time);
    printf("\n");

    pthread_exit(NULL);
}

int main()
{
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;

    if (pthread_create(&thread1, NULL, countA, NULL) != 0)
    {
        fprintf(stderr, "Error to create thread 1");
        printf("\n");
        exit(1);
    }
    pthread_join(thread1, NULL);

    if (pthread_create(&thread2, NULL, countB, NULL) != 0)
    {
        fprintf(stderr, "Error to create thread 2");
        printf("\n");
        exit(1);
    }
    pthread_join(thread2, NULL);

    if (pthread_create(&thread3, NULL, countC, NULL) != 0)
    {
        fprintf(stderr, "Error to create thread 3");
        printf("\n");
        exit(1);
    } 
    pthread_join(thread3, NULL);

    printf("Thread 1: %d\n", A);
    printf("Thread 2: %d\n", B);
    printf("Thread 3: %d\n", C);

    return 0;
}
