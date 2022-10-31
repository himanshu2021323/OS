#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>


void LsL(char arg[1000])
{
    DIR *directory;
    struct dirent *file;
    struct stat thestat;
    struct passwd *password;
    struct group *groups;
    char arr[512];
    if (strlen(arg) == 0)
    {
        arg = ".";
    }
    directory = opendir(arg);
    file = readdir(directory);
    while (file)
    {
        if (file->d_name[0] == '.')
        {
            continue;
        }
        sprintf(arr, "%s/%s", arg, file->d_name);
        stat(arr, &thestat);
        switch (thestat.st_mode & S_IFMT)
        {
        case S_IFBLK:
            printf("b");
            break;
        case S_IFCHR:
            printf("c");
            break;
        case S_IFDIR:
            printf("d");
            break;
        case S_IFIFO:
            printf("p");
            break;
        case S_IFLNK:
            printf("l");
            break;
        case S_IFSOCK:
            printf("s");
            break;
        default:
            printf("-");
            break;
        }
        printf((thestat.st_mode & S_IRUSR) ? "r" : "-");
        printf((thestat.st_mode & S_IWUSR) ? "w" : "-");
        printf((thestat.st_mode & S_IXUSR) ? "x" : "-");
        printf((thestat.st_mode & S_IRGRP) ? "r" : "-");
        printf((thestat.st_mode & S_IWGRP) ? "w" : "-");
        printf((thestat.st_mode & S_IXGRP) ? "x" : "-");
        printf((thestat.st_mode & S_IROTH) ? "r" : "-");
        printf((thestat.st_mode & S_IWOTH) ? "w" : "-");
        printf((thestat.st_mode & S_IXOTH) ? "x" : "-");
        printf(" %ld", thestat.st_nlink);
        password = getpwuid(thestat.st_uid);
        printf(" %s", password->pw_name);
        groups = getgrgid(thestat.st_gid);
        printf(" %s", groups->gr_name);
        printf(" %zu", thestat.st_size);
        printf(" %s", file->d_name);
        printf(" %s", ctime(&thestat.st_mtime));
    }
    closedir(directory);
}

int main(int argc, char *argv[])
{
    char cmd[10] = "";
    char flag[10] = "";
    char arg[1000] = "";
    if (argc > 1)
    {
        char *tkn = strtok(argv[1], " ");
        strcpy(cmd, tkn);
        tkn = strtok(NULL, " ");
        if (tkn != NULL)
        {
            if (tkn[0] == '-')
            {
                strcpy(flag, tkn);
                tkn = strtok(NULL, " ");
                if (tkn != NULL)
                {
                    strcpy(arg, tkn);
                }
            }
            else
            {
                strcpy(arg, tkn);
            }
        }
    }
    if (flag[0] == '\0')
    {
        struct dirent **names;
        int n;
        if (strlen(arg) == 0)
        {
            n = scandir(".", &names, NULL, alphasort);
        }
        else
        {
            n = scandir(arg, &names, NULL, alphasort);
        }
        int i = 0;
        if (n < 0)
        {
            perror("Error: scandir");
        }
        else
        {
            while (i < n)
            {
                if (names[i]->d_name[0] == '.')
                {
                    free(names[i++]);
                    continue;
                }
                printf("%s ", names[i]->d_name);
                free(names[i++]);
            }
            printf("\n");
            free(names);
        }
    }
    else if (flag[1] == 'a')
    {
        struct dirent **names;
        int n;
        if (strlen(arg) == 0)
        {
            n = scandir(".", &names, NULL, alphasort);
        }
        else
        {
            n = scandir(arg, &names, NULL, alphasort);
        }
        int i = 0;
        if (n < 0)
        {
            perror("Error: scandir");
        }
        else
        {
            while (i < n)
            {
                printf("%s ", names[i]->d_name);
                free(names[i++]);
            }
            printf("\n");
            free(names);
        }
    }
    else if (flag[1] == 'l')
    {
        LsL(arg);
    }
    else
    {
        printf("Invalid Input ---> %s\n", flag);
        return 1;
    }
    return 0;
}
