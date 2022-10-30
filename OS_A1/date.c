#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sysexits.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    char cmdName[10] = "";
    char flag[10] = "";
    char *tkn  = strtok(argv[1], " ");
    strcpy(cmdName, tkn);
    tkn  = strtok(NULL, " ");
    if (tkn != NULL)
    {
        strcpy(flag, tkn);
    }
    if (strcmp(flag, "") == 0)
    {
        time_t Time;
        Time = time(NULL);
        if (Time == -1)
        {
            perror("Error");
            return;
        }
        struct tm *ktm;
        char buf1[4];
        char buf2[4];
        char buf3[6];
        ktm = localtime(&Time);
        if (ktm == NULL)
        {
            perror("Error");
            return;
        }
        strftime(buf1, 4, "%a", ktm);
        strftime(buf2, 4, "%b", ktm);
        strftime(buf3, 6, "%z", ktm);
        printf("%s %s %02d %02d:%02d:%02d %s %d\n", buf1, buf2, ktm->tm_mday, ktm->tm_hour, ktm->tm_min, ktm->tm_sec, buf3, ktm->tm_year + 1900);
    }
    else if (flag[1] == 'u')
    {
        time_t Time;
        Time = time(NULL);
        if (Time == -1)
        {
            perror("Error");
            return;
        }
        struct tm *ktm;
        char buf1[4];
        char buf2[4];
        char buf3[6];
        ktm = gmtime(&Time);
        if (ktm == NULL)
        {
            perror("Error");
            return;
        }
        strftime(buf1, 4, "%a", ktm);
        strftime(buf2, 4, "%b", ktm);
        strftime(buf3, 6, "%z", ktm);
        printf("%s %s %02d %02d:%02d:%02d UTC %d\n", buf1, buf2, ktm->tm_mday, ktm->tm_hour, ktm->tm_min, ktm->tm_sec, ktm->tm_year + 1900);
    }
    else if (flag[1] == 'R')
    {
        time_t Time;
        Time = time(NULL);
        if (Time == -1)
        {
            perror("Error");
            return;
        }
        struct tm *ktm;
        char buf1[4];
        char buf2[4];
        char buf3[6];
        ktm = localtime(&Time);
        if (ktm == NULL)
        {
            perror("Error is");
            return;
        }
        strftime(buf1, 4, "%a", ktm);
        strftime(buf2, 4, "%b", ktm);
        strftime(buf3, 6, "%z", ktm);
        printf("%s, %02d %s %d %02d:%02d:%02d %s\n", buf1, ktm->tm_mday, buf2, ktm->tm_year + 1900, ktm->tm_hour, ktm->tm_min, ktm->tm_sec, buf3);
    }
    else
    {
        printf("Invalid Input ---> %s\n", flag);
        return 1;
    }
    return 0;
}