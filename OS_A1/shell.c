#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <pwd.h>
#include <errno.h>
#include <sys/wait.h>

char commands[10][10] = {"cd", "echo", "pwd", "exit", "ls", "cat", "date", "rm", "mkdir"};
static int count = 0;
int nextLine;

void cdP(char **input_array)
{
    char cwd_inputnew2[1024];

    if (input_array[2] != NULL)
    {

        strcpy(cwd_inputnew2, input_array[2]);
        char *pt = strtok(cwd_inputnew2, "\n");
        char buf[PATH_MAX];
        char *res = realpath(pt, buf);
        if (!res)
        {
            perror("Error: realpath");
        }
        else
        {
            int value23 = chdir(res);
            printf("physical source directory : %s\n", buf);
            printf("%s\n", res);
            if (value23 != 0)
            {
                perror("Error in command - ");
            }
            else
            {
                char cwd5[200];
                char *cwd35 = getcwd(cwd5, sizeof(cwd5));
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
            char cwd[200];
            char *cwd3 = getcwd(cwd, sizeof(cwd));
            printf("%s", cwd3);
        }
    }
}

void cdL(char **input_array)
{
    if (input_array[2] != NULL)
    {
        char cwd_inputnew2[1024];
        strcpy(cwd_inputnew2, input_array[2]);
        char *inputnew3 = "";
        char *inputnew4 = "hi";
        // printf("yo");
        char *pt = strtok(cwd_inputnew2, "\n");
        int id = chdir(pt);
        if (id != 0)
        {
            perror("Error in -L command - ");
        }
        else
        {
            char cwd[200];
            char *cwd3 = getcwd(cwd, sizeof(cwd));
            printf("%s", cwd3);
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
            char cwd[200];
            char *cwd3 = getcwd(cwd, sizeof(cwd));
            printf("%s", cwd3);
        }
    }
}

void cd(char **input_array)
{
    int flaggers1 = INT_MAX;
    int flaggers2 = INT_MAX;
    int flaggers3 = INT_MAX;
    int flaggers4 = INT_MAX;
    int flaggers5 = INT_MAX;
    int flaggers6 = INT_MAX;
    int flaggers7 = INT_MAX;

    char cwd_inputnew1[1024];

    if (input_array[1] != NULL)
    {

        strcpy(cwd_inputnew1, input_array[1]);
        flaggers1 = strcmp(cwd_inputnew1, "~");
        flaggers2 = strcmp(cwd_inputnew1, "--");
        flaggers3 = strcmp(cwd_inputnew1, "-");
        flaggers4 = strcmp(cwd_inputnew1, "-P");
        flaggers5 = strcmp(cwd_inputnew1, "-L");
        flaggers6 = strcmp(cwd_inputnew1, "--help");
    }
    else
    {
        flaggers7 = 0;
    }
    if (flaggers3 == 0)
    {
        int flag3 = chdir("..");
        if (flag3 != 0)
        {
            perror("Error in command - ");
        }
        else
        {
            char cwd2[200];
            char *cwd32 = getcwd(cwd2, sizeof(cwd2));
            printf("%s", cwd32);
        }
    }
    else if (flaggers1 == 0 || flaggers2 == 0 || flaggers7 == 0)
    {
        int flag127 = chdir(getenv("HOME"));
        if (flag127 != 0)
        {
            perror("Error in command - ");
        }
        else
        {
            char cwd[200];
            char *cwd3 = getcwd(cwd, sizeof(cwd));
            printf("%s", cwd3);
        }
    }

    else if (flaggers6 == 0)
    {
        printf("%s", "this command is used to change the directory to given input");
    }
    else if (flaggers4 == 0)
    {
        cdP(input_array);
    }
    else if (flaggers5 == 0)
    {
        cdL(input_array);
    }
    else
    {
        char *pt = strtok(cwd_inputnew1, "\n");
        int value = chdir(pt);
        if (value != 0)
        {
            perror("Error in commands - ");
        }
        else
        {
            char cwd[200];
            char *cwd3 = getcwd(cwd, sizeof(cwd));
            printf("%s", cwd3);
        }
    }
}

void echon(char **input_array, int size)
{
    int i = 2;
    while (i < size)
    {
        if (input_array[i] != NULL)
        {
            printf("%s ", input_array[i]);
        }
        i++;
    }
}

void echoE(char **input_array, int size)
{
    int i = 2;
    while (i < size)
    {
        if (input_array[i] != NULL)
        {
            printf("%s ", input_array[i]);
        }
        i++;
    }
}

void echo(char **input_array, int size)
{
    int flagger4 = INT_MAX;
    int flagger5 = INT_MAX;
    int flagger6 = INT_MAX;
    char echo_input[10];
    if (input_array[1] != NULL)
    {
        strcpy(echo_input, input_array[1]);
        flagger4 = strcmp(echo_input, "-n");
        flagger5 = strcmp(echo_input, "-E");
        flagger6 = strcmp(echo_input, "--help");
    }
    else
    {
        return;
    }
    if (flagger4 == 0)
    {
        nextLine = 1;
        echon(input_array, size);
    }
    else if (flagger5 == 0)
    {
        echoE(input_array, size);
    }
    else if (flagger6 == 0)
    {
        printf("%s", "this command prints the input given after echo");
    }
    else
    {
        for (int i = 1; i < size; ++i)
        {
            if (input_array[i] != NULL)
            {
                printf("%s ", input_array[i]);
            }
        }
    }
}

void pwdP()
{
    char newarr[1024];
    char *cwd2 = getcwd(newarr, sizeof(newarr));
    printf("%s", cwd2);
}

void pwdL()
{
    char buf[PATH_MAX];
    char newarr[1024];
    char *res = realpath(newarr, buf);
    char *cwd2 = getcwd(newarr, sizeof(newarr));
    printf("%s", cwd2);
}

void pwd(char **input_array)
{
    int newflag = 0;
    char cwd_input[10];
    char arr[1024];
    int flagger2 = INT_MAX;
    int flagger3 = INT_MAX;
    int flagger4 = INT_MAX;

    if (input_array[1] != NULL)
    {
        strcpy(cwd_input, input_array[1]);
        newflag = 1;
    }

    char *cwd = getcwd(arr, sizeof(arr));
    if (cwd == NULL)
    {
        perror("Error:");
    }
    else
    {
        if (newflag == 1)
        {
            flagger2 = strcmp(cwd_input, "-P");
            flagger3 = strcmp(cwd_input, "--help");
            flagger4 = strcmp(cwd_input, "-L");
            if (flagger3 == 0)
            {
                printf("%s", "this command prints the current working directory");
                exit;
            }
            else if (flagger2 == 0)
            {
                pwdP();
            }
            else if (flagger4 == 0)
            {
                pwdL();
            }
        }
        else
        {
            printf("%s", cwd);
        }
    }
}

int main()
{
    printf("\e[1;1H\e[2J");
    printf("\n\n\n\n*******************************Welcome To My SHELL***********************************\n\n\n\n");
    printf("Available commands:\n\tcd, pwd, history, echo, ls, cat, date, mkdir, rm, exit\n\n");
    char cwd[100];
    while (1)
    {
        nextLine = 0;
        char command[1024];
        printf("$ ");

        scanf("%[^\n]%*c", command);

        if (command[0] != 0)
        {
            int size = 0;
            char func[9];
            int flagger = -1;
            int func_no = -1;
            char new_command[1024];
            char **input_array = (char **)malloc(500 * sizeof(char *));

            strcpy(new_command, command);
            if (count > 999)
            {
                count = 0;
            }
            // strcpy(history_array[count++], new_command);

            char *token = strtok(command, " ");

            while (token != NULL)
            {
                input_array[size] = (char *)malloc(500 * sizeof(char));
                strcpy(input_array[size], token);
                token = strtok(NULL, " ");
                size++;
            }

            int i = 0;
            while (i < 10)
            {
                int ctr = 0;

                int flag = 0;

                while (commands[i][ctr] != '\0' && input_array[0][ctr] != '\0')
                {
                    if (commands[i][ctr] != input_array[0][ctr])
                    {
                        flag = 1;
                        break;
                    }
                    ctr++;
                }

                if (commands[i][ctr] != '\0' || input_array[0][ctr] != '\0')
                {
                    flag = 1;
                }

                if (flag != 1)
                {
                    func_no = i;
                    break;
                }
                i++;
            }

            if (func_no == 0)
            {
                cd(input_array);
            }
            else if (func_no == 1)
            {
                echo(input_array, size);
            }
            else if (func_no == 2)
            {
                pwd(input_array);
            }
            else if (func_no == 3)
            {
                printf("[PROCESS COMPLETED]\n");
                break;
            }

            else if (func_no == 4)
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
            else if (func_no == 5)
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
            else if (func_no == 6)
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
            else if (func_no == 7)
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
            else if (func_no == 8)
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
            else
            {
                printf("%s", "Error: Invalid Command");
            }
            if (nextLine == 0)
            {
                printf("%s\n", "");
            }
        }
        else
        {
            printf("%s\n", "PLEASE RUN AGAIN, THERE WAS NO INPUT");
        }
    }
    return 0;
}
