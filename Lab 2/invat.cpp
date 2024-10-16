#include <sys/stat.h>
#include <cstdio>
#include <errno.h>

int main()
{
    struct stat sb;
    if ( stat("foo", &sb) )
    {
        return errno;
    }
    printf("Foo was accessed at time %d seconds\n", sb.st_atim);
    return 0;
}