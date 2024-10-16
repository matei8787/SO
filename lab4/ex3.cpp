#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <cstdio>
#include <cstring>
#include <errno.h>
int make_nr(char* s)
{
    int ans = 0;
    int n = strlen(s);
    for ( int i = 0 ; i < n ; i++ )
    {
        ans = ans * 10 + (s[i] - '0');
    }
    return ans;
}
void make_collatz(int nr)
{
    printf("%d: ", nr);
    while ( nr != 1 )
    {
        printf("%d ", nr);
        if ( nr % 2 == 0 )
        {
            nr /= 2;
        }
        else
        {
            nr = nr * 3 + 1;
        }
    }
    printf("%d\n", nr);
}
int main(int argc, char* argv[])
{
    if ( argc < 2 )
    {
        printf("Too few arguments");
        return errno;
    }

    pid_t child_pid, wpid;
    int status = 0;
    printf("Starting parrent %d\n", getpid());
    for ( int i = 1 ; i < argc ; i++ )
    {
        child_pid = fork();
        if ( child_pid == 0 )
        {
            make_collatz(make_nr(argv[i]));
            printf("Done Parent %d Me %d\n", getppid(), getpid());
            exit(0);
        }
    }

}