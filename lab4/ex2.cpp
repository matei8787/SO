#include <unistd.h>
#include <cstdio>
#include <errno.h>
#include <sys/wait.h>
#include <cstring>
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
int main(int argc, char* argv[])
{
    if ( argc != 2 )
    {
        printf("Nu sunt exact 2 argumente");
        return -1;
    }
    pid_t pid = fork();
    if ( pid < 0 )
    {
        printf("Eroare");
        return errno;
    }
    else if ( pid == 0 )
    {
        int nr = make_nr(argv[1]);
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
    else
    {
        wait(NULL);
        printf("Child %d finished\n", pid);
    }
}