#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char cmdName[10] = "";
    char flag[10] = "";
    char *tkn = strtok(argv[1], " ");
    strcpy(cmdName, tkn);
    tkn = strtok(NULL, " ");
    if (tkn[0] == '-')
    {
        strcpy(flag, tkn);
        tkn = strtok(NULL, " ");
    }
    while (tkn)
    {
        char file[1000] = "";
        strcpy(file, tkn);
        if (flag[0] == '\0')
        {
            if (unlink(file) != 0)
            {
                perror(file);
            }
        }
        else if (flag[1] == 'd')
        {
            if (rmdir(file) != 0)
            {
                perror(file);
            }
        }
        else if (flag[1] == 'v')
        {
            if (unlink(file) == 0)
            {
                printf("removed file '%s'\n", file);
            }
            else
            {
                perror(file);
            }
        }
        else
        {
            printf("Invalid Input ---> %s\n", flag);
            return 1;
        }
        tkn = strtok(NULL, " ");
    }
    return 0;
}