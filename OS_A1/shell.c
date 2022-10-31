#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <pwd.h>
#include <errno.h>
#include <sys/wait.h>

char cmds[10][10] = {"cd", "echo", "pwd", "ls", "cat", "date", "rm", "mkdir", "exit"};
int nxt;
static int count = 0;

void cd(char **array_in)
{
    int hcs1 = INT_MAX;
    int hcs2 = INT_MAX;
    int hcs3 = INT_MAX;
    int hcs4 = INT_MAX;
    int hcs5 = INT_MAX;
    int hcs6 = INT_MAX;
    int hcs7 = INT_MAX;

    char cmd_input1[1024];

    if (array_in[1] != NULL)
    {

        strcpy(cmd_input1, array_in[1]);
        hcs1 = strcmp(cmd_input1, "~");
        hcs2 = strcmp(cmd_input1, "--");
        hcs3 = strcmp(cmd_input1, "-");
        hcs4 = strcmp(cmd_input1, "-P");
        hcs5 = strcmp(cmd_input1, "-L");
        hcs6 = strcmp(cmd_input1, "--help");
    }
    else
    {
        hcs7 = 0;
    }
    if (hcs3 == 0)
    {
        int flag3 = chdir("..");
        if (flag3 != 0)
        {
            perror("Error in command - ");
        }
        else
        {
            char cmd2[200];
            char *cmd32 = getcwd(cmd2, sizeof(cmd2));
            printf("%s", cmd32);
        }
    }
    else if (hcs1 == 0 || hcs2 == 0 || hcs7 == 0)
    {
        int flag127 = chdir(getenv("HOME"));
        if (flag127 != 0)
        {
            perror("Error in command - ");
        }
        else
        {
            char cmd[200];
            char *cmd3 = getcwd(cmd, sizeof(cmd));
            printf("%s", cmd3);
        }
    }

    else if (hcs6 == 0)
    {
        printf("this command is used to change the directory\n");
    }
    else if (hcs4 == 0)
    {
        // cd -P command
        char cmd_input2[1024];
        if (array_in[2] != NULL)
        {

            strcpy(cmd_input2, array_in[2]);
            char *pt = strtok(cmd_input2, "\n");
            char buf[PATH_MAX];
            char *result = realpath(pt, buf);
            if (!result)
            {
                perror("Error: realpath");
            }
            else
            {
                int value23 = chdir(result);
                printf("physical source directory : %s\n", buf);
                printf("%s\n", result);
                if (value23 != 0)
                {
                    perror("Error in command - ");
                }
                else
                {
                    char cmd5[200];
                    char *cmd35 = getcwd(cmd5, sizeof(cmd5));
                }
            }
        }
        else
        {
            int value2 = chdir(getenv("HOME"));
            if (value2 != 0)
            {
                perror("Error in command - ");
            }
            else
            {
                char cmd[200];
                char *cmd3 = getcwd(cmd, sizeof(cmd));
                printf("%s", cmd3);
            }
        }
    }
    else if (hcs5 == 0)
    {
        // cd -L command
        if (array_in[2] != NULL)
        {
            char cmd_input2[1024];
            strcpy(cmd_input2, array_in[2]);
            char *inputnew3 = "";
            char *inputnew4 = "hi";
            char *pt = strtok(cmd_input2, "\n");
            int id = chdir(pt);
            if (id != 0)
            {
                perror("Error in -L command - ");
            }
            else
            {
                char cmd[200];
                char *cmd3 = getcwd(cmd, sizeof(cmd));
                printf("%s", cmd3);
            }
        }
        else
        {
            int value2 = chdir(getenv("HOME"));
            if (value2 != 0)
            {
                perror("Error in command - ");
            }
            else
            {
                char cmd[200];
                char *cmd3 = getcwd(cmd, sizeof(cmd));
                printf("%s", cmd3);
            }
        }
    }
    else
    {
        char *pt = strtok(cmd_input1, "\n");
        int value = chdir(pt);
        if (value != 0)
        {
            perror("Error in commands - ");
        }
        else
        {
            char cmd[200];
            char *cmd3 = getcwd(cmd, sizeof(cmd));
            printf("%s", cmd3);
        }
    }
}

void echo(char **array_in, int size)
{
    int hc4 = INT_MAX;
    int hc5 = INT_MAX;
    int hc6 = INT_MAX;
    char echo_input[10];
    if (array_in[1] != NULL)
    {
        strcpy(echo_input, array_in[1]);
        hc4 = strcmp(echo_input, "-n");
        hc5 = strcmp(echo_input, "-E");
        hc6 = strcmp(echo_input, "--help");
    }
    else
    {
        return;
    }
    if (hc4 == 0)
    {
        // echo -n command
        nxt = 1;
        int i = 2;
        while (i < size)
        {
            if (array_in[i] != NULL)
            {
                printf("%s ", array_in[i]);
            }
            i++;
        }
    }
    else if (hc5 == 0)
    {
        // echo -E command
        int i = 2;
        while (i < size)
        {
            if (array_in[i] != NULL)
            {
                printf("%s ", array_in[i]);
            }
            i++;
        }
    }
    else if (hc6 == 0)
    {
        printf("this command prints the input given after echo");
    }
    else
    {
        int i = 1;
        while (i < size)
        {
            if (array_in[i] != NULL)
            {
                printf("%s ", array_in[i]);
            }
            ++i;
        }
    }
}

void pwd(char **array_in)
{
    int newflag = 0;
    char cmd_input[10];
    char arr[1024];
    int hc2 = INT_MAX;
    int hc3 = INT_MAX;
    int hc4 = INT_MAX;

    if (array_in[1] != NULL)
    {
        strcpy(cmd_input, array_in[1]);
        newflag = 1;
    }

    char *cmd = getcwd(arr, sizeof(arr));
    if (cmd == NULL)
    {
        perror("Error:");
    }
    else
    {
        if (newflag == 1)
        {
            hc2 = strcmp(cmd_input, "-P");
            hc3 = strcmp(cmd_input, "--help");
            hc4 = strcmp(cmd_input, "-L");
            if (hc3 == 0)
            {
                printf("%s", "this command prints the current working directory");
                exit;
            }
            else if (hc2 == 0)
            {
                // pwd -P command
                    char newarr[1024];
                    char *cmd2 = getcwd(newarr, sizeof(newarr));
                    printf("%s", cmd2);
            }
            else if (hc4 == 0)
            {
                // pwd -L command
                char buf[PATH_MAX];
                char newarr[1024];
                char *result = realpath(newarr, buf);
                char *cmd2 = getcwd(newarr, sizeof(newarr));
                printf("%s", cmd2);
            }
        }
        else
        {
            printf("%s", cmd);
        }
    }
}

int main()
{
    printf("\n\n\n\n****************************************************************************\n\n\n\n");
    printf("\t\t\t Welcome To My Shell");
    printf("\n\n\n\n****************************************************************************\n\n\n\n");
    printf("Available commands:\n\t cd, pwd, echo, ls, cat, date, mkdir, rm \n\n");
    char cmd[100];
    while (1)
    {
        nxt = 0;
        char command[1024];
        printf("[himanshu@shell ~]$ ");

        scanf("%[^\n]%*c", command);

        if (command[0] != 0)
        {
            int size = 0;
            char func[9];
            int hc = -1;
            int function = -1;
            char new_command[1024];
            char **array_in = (char **)malloc(500 * sizeof(char *));

            strcpy(new_command, command);
            if (count > 999)
            {
                count = 0;
            }
            char *tkn = strtok(command, " ");

            while (tkn)
            {
                array_in[size] = (char *)malloc(500 * sizeof(char));
                strcpy(array_in[size], tkn);
                tkn = strtok(NULL, " ");
                size++;
            }

            int i = 0;
            while (i < 10)
            {
                int control = 0;

                int flag = 0;

                while (cmds[i][control] != '\0' && array_in[0][control] != '\0')
                {
                    if (cmds[i][control] != array_in[0][control])
                    {
                        flag = 1;
                        break;
                    }
                    control++;
                }

                if (cmds[i][control] != '\0' || array_in[0][control] != '\0')
                {
                    flag = 1;
                }

                if (flag != 1)
                {
                    function = i;
                    break;
                }
                i++;
            }

            if (function == 0)
            {
                cd(array_in);
            }
            else if (function == 1)
            {
                echo(array_in, size);
            }
            else if (function == 2)
            {
                pwd(array_in);
            }
            else if (function == 3)
            {
                pid_t id;
                int stat;
                if ((id = fork()) == 0)
                {
                    char *args[] = {"./ls", new_command, NULL};
                    execvp("./ls", args);
                    exit(0);
                }
                else
                {
                    pid_t time;
                    time = wait(&stat);
                }
            }
            else if (function == 4)
            {
                pid_t id;
                int stat;
                if ((id = fork()) == 0)
                {
                    char *args[] = {"./cat", new_command, NULL};
                    execvp("./cat", args);
                    exit(0);
                }
                else
                {
                    pid_t time;
                    time = wait(&stat);
                }
            }
            else if (function == 5)
            {
                pid_t id;

                int stat;
                if ((id = fork()) == 0)
                {
                    char *args[] = {"./date", new_command, NULL};
                    execvp("./date", args);
                    exit(0);
                }
                else
                {
                    pid_t time;
                    time = wait(&stat);
                }
            }
            else if (function == 6)
            {
                pid_t id;
                int stat;
                if ((id = fork()) == 0)
                {
                    char *args[] = {"./rm", new_command, NULL};
                    execvp("./rm", args);
                    exit(0);
                }
                else
                {
                    pid_t time;
                    time = wait(&stat);
                }
            }
            else if (function == 7)
            {
                pid_t id;
                int stat;
                if ((id = fork()) == 0)
                {

                    char *args[] = {"./mkdir", new_command, NULL};
                    execvp("./mkdir", args);
                    exit(0);
                }
                else
                {
                    pid_t time;
                    time = wait(&stat);
                }
            }
            else if (function == 8)
            {
                printf("[PROCESS COMPLETED]\n");
                break;
            }
            else
            {
                printf("Error: Invalid Command\n");
            }
            if (nxt == 0)
            {
                printf(" \n");
            }
        }
        else
        {
            printf("THERE IS NO INPUT FOUND, RUN AGAIN PLEASE\n");
        }
    }
    return 0;
}
