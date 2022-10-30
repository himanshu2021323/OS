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

#define S_IFMT _S_IFMT

int main(int argc, char *argv[])
{
    char cmdName[10] = "";
    char flag[10] = "";
    char argue[1000] = "";
    if (argc > 1)
    {
        char *tkn;
        tkn = strtok(argv[1], " ");
        strcpy(cmdName, tkn);
        tkn = strtok(NULL, " ");
        if (tkn != NULL)
        {
            if (tkn[0] == '-')
            {
                strcpy(flag, tkn);
                tkn = strtok(NULL, " ");
                if (tkn != NULL)
                {
                    strcpy(argue, tkn);
                }
            }
            else
            {
                strcpy(argue, tkn);
            }
        }
    }
    if (flag[0] == '\0')
    {
        struct dirent **nameDir;
        int n;
        if (strlen(argue) == 0)
        {
            n = scandir(".", &nameDir, NULL, alphasort);
        }
        else
        {
            n = scandir(argue, &nameDir, NULL, alphasort);
        }
        if (n < 0)
        {
            perror("Error: scandir");
        }
        else
        {
            while (int i < n)
            {
                if (nameDir[i]->d_name[0] == '.')
                {
                    free(nameDir[i++]);
                    continue;
                }
                printf("%s ", nameDir[i]->d_name);
                free(nameDir[i++]);
            }
            printf("\n");
            free(nameDir);
        }
    }
    else if (flag[1] == 'a')
    {
        struct dirent **nameDir;
        int n;
        if (strlen(argue) == 0)
        {
            n = scandir(".", &nameDir, NULL, alphasort);
        }
        else
        {
            n = scandir(argue, &nameDir, NULL, alphasort);
        }
        if (n < 0)
        {
            perror("scandir");
        }
        else
        {
            while (int i < n)
            {
                printf("%s ", nameDir[i]->d_name);
                free(nameDir[i++]);
            }
            printf("\n");
            free(nameDir);
        }
    }
    else if (flag[1] == 'l')
    {
        DIR *directory;
        struct dirent *myfile;
        struct stat mystat;
        struct passwd *password;
        struct group *groups;
        char arr[512];
        if (strlen(argue) == 0)
        {
            argue = ".";
        }
        directory = opendir(argue);
        while ((myfile = readdir(directory)))
        {
            if (myfile->d_name[0] == '.')
            {
                continue;
            }
            sprintf(arr, "%s/%s", argue, myfile->d_name);
            mystat(arr, &mystat);
            switch (mystat.st_mode & S_IFMT)
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
            printf((mystat.st_mode & S_IRUSR) ? "r" : "-");
            printf((mystat.st_mode & S_IWUSR) ? "w" : "-");
            printf((mystat.st_mode & S_IXUSR) ? "x" : "-");
            printf((mystat.st_mode & S_IRGRP) ? "r" : "-");
            printf((mystat.st_mode & S_IWGRP) ? "w" : "-");
            printf((mystat.st_mode & S_IXGRP) ? "x" : "-");
            printf((mystat.st_mode & S_IROTH) ? "r" : "-");
            printf((mystat.st_mode & S_IWOTH) ? "w" : "-");
            printf((mystat.st_mode & S_IXOTH) ? "x" : "-");
            printf(" %ld", mystat.st_nlink);
            password = getpwuid(mystat.st_uid);
            printf(" %s", password->pw_name);
            groups = getgrgid(mystat.st_gid);
            printf(" %s", groups->gr_name);
            printf(" %zu", mystat.st_size);
            printf(" %s", myfile->d_name);
            printf(" %s", ctime(&mystat.st_mtime));
        }
        closedir(directory);
    }
    else
    {
        printf("Invalid Input ---> %s\n", flag);
        return 1;
    }
    return 0;
}