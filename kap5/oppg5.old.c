#include <stdio.h>     /* printf */
#include <stdlib.h>    /* exit */
#include <unistd.h>    /* fork */
#include <sys/wait.h>  /* waitpid */
#include <sys/types.h> /* pid_t */
#include <time.h>      /* pid_t */
/* Note: pid_t is probably just an int, but it might be different
kind of ints on different platforms, so using pid_t instead of
int helps makes the code more platform-independent
*/
char *getTime()
{

    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    // printf("Current local time and date: %s", asctime(timeinfo));
    return asctime(timeinfo);
}

int isChild(int rc)
{
    if (rc == 0)
        return 1;
    return 0;
}

void process(int number, int time, int parent)
{
    printf("Prosess %d starter, (me: %d) (parent: %d) (time: %s)\n", number, getpid(), parent, getTime());
    getTime();
    sleep(time);
    printf("Prosess %d ferdig, (me: %d) (parent: %d) (time: %s)\n", number, getpid(), parent, getTime());
}

int main(int argc, char *argv)
{
    int parent = 0;
    int rc = fork();
    if (isChild(rc))
    {
        process(2, 3, parent);
        parent = getpid();
        fork();
        if (getpid() != parent)
        {
            process(3, 2, parent);
        }
    }
    else
    {
        process(0, 1, parent);
        parent = getpid();
        fork();
        if (getpid() != parent)
        {
            process(1, 2, parent);
            parent = getpid();
            fork();
            if (getpid() != parent)
            {
                process(3, 2, parent);
            }
        }
        else
        {
            parent = getpid();
            fork();
            if (getpid() != parent)
            {
                process(4, 3, parent);
                parent = getpid();
                fork();
                if (getpid() != parent)
                {
                    process(5, 3, parent);
                }
            }
        }
    }

    return 0;
}