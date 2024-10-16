#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <cstdio>
int main()
{
    pid_t pid = fork();
    if ( pid < 0 )
    {
        return errno;
    }
    else if ( pid == 0 )
    {
        char *argv[] = {"ls", NULL};
        execve("/usr/bin/ls", argv, NULL);
        perror(NULL);
    }
    else
    {
        printf("My PID=%d, Child PID=%d\n", getpid(), pid);
        wait(NULL);
        printf("Child %d finished\n", pid);
    }
}