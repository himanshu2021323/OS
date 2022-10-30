#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

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
            int check = mkdir(file, 0777);
            if (check == -1)
            {
                perror(file);
            }
        }
        else
        {
            if (flag[1] == 'v')
            {
                int check = mkdir(file, 0777);
                if (check == -1)
                {
                    perror(file);
                }
                else
                {
                    printf("mkdir: created directory '%s'\n", file);
                }
            }
            else if (flag[1] == 'm' && flag[2] == '=')
            {
                if (strlen(flag) < 6)
                {
                    printf("Invalid Input ---> %s\n", flag);
                    return 1;
                }
                if (strlen(flag) == 7)
                {
                    char Str[5];
                    int i;
                    for (i = 0; i < 4; i++)
                    {
                        Str[i] = flag[i + 3];
                    }
                    int mode = atoi(Str);
                    if (mode != 400 && mode != 777 && mode != 100 && mode != 200)
                    {
                        printf("Invalid mode '%d'\n", mode);
                        return 1;
                    }
                    int check = mkdir(file, mode);
                    if (check == -1)
                    {
                        perror(file);
                    }
                }
                else
                {
                    char Str[4];
                    int i;
                    for (i = 0; i < 3; i++)
                    {
                        Str[i] = flag[i + 3];
                    }
                    int mode = atoi(Str);
                    if (mode != 400 && mode != 777 && mode != 100 && mode != 200)
                    {
                        printf("Invalid mode '%d'\n", mode);
                        return 1;
                    }
                    int check = mkdir(file, mode);
                    if (check == -1)
                    {
                        perror(file);
                    }
                }
            }
            else
            {
                printf("Invalid Input ---> %s\n", flag);
                return 1;
            }
        }
        tkn = strtok(NULL, " ");
    }
    return 0;
}