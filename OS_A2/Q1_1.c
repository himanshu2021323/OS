#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

#define count 232

// Global variable to hold the value of each thread
int A, B, C;

// Function prototypes
void *countA(void *arg);
void *countB(void *arg);
void *countC(void *arg);

int main(void)
{
    // Variable to hold thread ID
    pthread_t tid1, tid2, tid3;

    // Create thread 1 with SCHED_OTHER policy
    if (pthread_create(&tid1, NULL, countA, NULL) != 0)
    {
        fprintf(stderr, "Unable to create thread 1\n");
        exit(1);
    }

    // Create thread 2 with SCHED_RR policy
    if (pthread_create(&tid2, NULL, countB, NULL) != 0)
    {
        fprintf(stderr, "Unable to create thread 2\n");
        exit(1);
    }

    // Create thread 3 with SCHED_FIFO policy
    if (pthread_create(&tid3, NULL, countC, NULL) != 0)
    {
        fprintf(stderr, "Unable to create thread 3\n");
        exit(1);
    }

    // Wait for all threads to complete
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    // Print out the value of each thread
    printf("Thread 1 value: %d\n", A);
    printf("Thread 2 value: %d\n", B);
    printf("Thread 3 value: %d\n", C);

    return 0;
}

// Thread 1 function
void *countA(void *arg)
{
    int i;
    struct timeval start, end;

    // Set the scheduling policy and priority
    pthread_setschedparam(pthread_self(), SCHED_OTHER, 0);

    // Get the starting time
    gettimeofday(&start, NULL);

    // Perform the counting
    for (i = 1; i <= count; i++)
        A++;

    // Get the ending time
    gettimeofday(&end, NULL);

    // Calculate the elapsed time in microseconds
    unsigned long elapsed = (end.tv_sec - start.tv_sec) * 1000000 +
                            (end.tv_usec - start.tv_usec);

    printf("Thread 1 completed in %ld microseconds\n", elapsed);

    pthread_exit(NULL);
}

// Thread 2 function
void *countB(void *arg)
{
    int i;
    struct timeval start, end;

    // Set the scheduling policy and priority
    pthread_setschedparam(pthread_self(), SCHED_RR, 0);

    // Get the starting time
    gettimeofday(&start, NULL);

    // Perform the counting
    for (i = 1; i <= count; i++)
        B++;

    // Get the ending time
    gettimeofday(&end, NULL);

    // Calculate the elapsed time in microseconds
    unsigned long elapsed = (end.tv_sec - start.tv_sec) * 1000000 +
                            (end.tv_usec - start.tv_usec);

    printf("Thread 2 completed in %ld microseconds\n", elapsed);

    pthread_exit(NULL);
}

// Thread 3 function
void *countC(void *arg)
{
    int i;
    struct timeval start, end;

    // Set the scheduling policy and priority
    pthread_setschedparam(pthread_self(), SCHED_FIFO, 0);

    // Get the starting time
    gettimeofday(&start, NULL);

    // Perform the counting
    for (i = 1; i <= count; i++)
        C++;

    // Get the ending time
    gettimeofday(&end, NULL);

    // Calculate the elapsed time in microseconds
    unsigned long elapsed = (end.tv_sec - start.tv_sec) * 1000000 +
                            (end.tv_usec - start.tv_usec);

    printf("Thread 3 completed in %ld microseconds\n", elapsed);

    pthread_exit(NULL);
}