#include <stdio.h>     /* printf */
#include <stdlib.h>    /* exit */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h>  /* waitpid */
#include <unistd.h>    /* fork */

int g_ant = 0; /* global declaration */

void getTime()
{

    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    printf("Current local time and date: %s", asctime(timeinfo));
}

void process(int number, int time)
{
    printf("Process %d is running\n", number);
    sleep(time);
    printf("Prosess %d ran for %d seconds\n", number, time);
}

void writeloop(char *text)
{
    long i = 0;
    while (g_ant < 30)
    {
        if (++i % 100000 == 0)
        {
            printf("%s: %d\n", text, ++g_ant);
        }
    }
}

void childProcess(int pid, int id, int sleep)
{
    if (pid == 0)
    { /* child */
        process(2, 3);
        exit(0);
    }
}

int main(void)
{
    pid_t pid;

    pid = fork();
    childProcess(pid, 2, 3);
    waitpid(pid, NULL, 0);
    return 0;
}
