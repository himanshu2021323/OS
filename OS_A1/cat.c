#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define O_RDONLY _O_RDONLY

int main(int argc, char *argv[])
{
    char cmdName[10] = "", flag[10] = "", fileName[1000] = "", *tkn = strtok(argv[1], " ");
    strcpy(cmdName, tkn);
    tkn = strtok(NULL, " ");
    if (tkn[0] == '-')
    {
        strcpy(flag, tkn);
        tkn = strtok(NULL, " ");
    }
    while (tkn)
    {
        strcpy(fileName, tkn);
        if (strcmp(flag, "") == 0)
        {
            int file;
            file = open(fileName, O_RDONLY);
            if (file < 0)
            {
                perror("Error: File Not Present");
                return;
            }
            char ch;
            int size;
            while ((size = read(file, &ch, 1)))
            {
                if (size < 0)
                {
                    perror("read");
                    return;
                }
                size_t w;
                w = write(STDIN_FILENO, &ch, 1);
                if (w < 0)
                {
                    if (errno != EINTR)
                    {
                        perror("write");
                        return;
                    }
                }
            }
            if (close(file) < 0)
            {
                perror("close");
                return;
            }
            return;
        }
        else if (flag[1] == 'E')
        {
           
            int file;
            file = open(fileName, O_RDONLY);
            if (file < 0)
            {
                perror("Error: File Not Present");
                return;
            }
            char ch;
            int size;
            while ((size = read(file, &ch, 1)))
            {
                if (size < 0)
                {
                    perror("read");
                    return;
                }
                if (ch == '\n')
                {
                    char c = '$';
                    size_t w;
                    w = write(STDIN_FILENO, &c, 1);
                    if (w < 0)
                    {
                        if (errno != EINTR)
                        {
                            perror("write");
                            return;
                        }
                    }
                }
                write(STDIN_FILENO, &ch, 1);
            }
            if (close(file) < 0)
            {
                perror("close");
                return;
            }
            return;
        }
        else if (flag[1] == 'T')
        {
            int file;
            file = open(fileName, O_RDONLY);
            if (file < 0)
            {
                perror("Error: File Not Present");
                return;
            }
            char ch;
            int size;
            while ((size = read(file, &ch, 1)))
            {
                if (size < 0)
                {
                    perror("read");
                    return;
                }
                if (ch == 9)
                {
                    char c = '^';
                    size_t w;
                    w = write(STDIN_FILENO, &c, 1);
                    if (w < 0)
                    {
                        if (errno != EINTR)
                        {
                            perror("write");
                            return;
                        }
                    }
                    c = 'I';
                    w = write(STDIN_FILENO, &c, 1);
                    if (w < 0)
                    {
                        if (errno != EINTR)
                        {
                            perror("write");
                            return;
                        }
                    }
                }
                else
                {
                    size_t w = write(STDIN_FILENO, &ch, 1);
                    if (w < 0)
                    {
                        if (errno != EINTR)
                        {
                            perror("write");
                            return;
                        }
                    }
                }
            }
            if (close(file) < 0)
            {
                perror("close");
                return;
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