#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <strings.h>
#include <cstring>
#include <sys/wait.h>
std::string tostring(int nr)
{
    std::string ans = "";
    while ( nr > 0 )
    {
        ans = (char)(nr%10 + '0') + ans;
        nr /= 10;
    }
    if ( ans.size() == 0 )
        ans = "0";
    return ans;
}

std::string collatz(int nr)
{
    std::string ans = tostring(nr) + ": ";
    while ( nr > 1 )
    {
        ans += tostring(nr);
        ans += " ";
        if ( nr % 2 == 0 )
            nr /= 2;
        else
            nr = nr * 3 + 1;
    }
    ans += "1\n";
    return ans;
}
void share_collatz(std::string sir, int sfd, int nr_sir)
{
    void* sptr = mmap(0, getpagesize(), PROT_WRITE, MAP_SHARED, sfd, nr_sir * getpagesize());
    if ( sptr == MAP_FAILED )
    {
        printf("Ceva nu a mers la mapare");
        return;
    }
    sprintf(static_cast<char*>(sptr), "%s", sir.c_str());
    return;
}
int main(int argc, char* argv[])
{
    char nume[] = "Collatzele";
    int sfd = shm_open(nume, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if ( sfd < 0 )
    {
        perror(NULL);
        printf("Nu merge sa sharuim memorie");
        return errno;
    }
    if ( ftruncate(sfd, getpagesize() * argc) == -1 ) ///nu inteleg asta, cum de e destula memorie
    {
        perror(NULL);
        printf("Nu am putut sa truncam fd-ul");
        return errno;
    }
    for ( int i = 1 ; i < argc ; i++ )
    {
        pid_t pid = fork();
        if ( pid < 0 )
        {
            printf("Eroare la creerea procesulii fiu");
            return errno;
        }
        else if ( pid == 0 )
        {
            share_collatz(collatz(atoi(argv[i])), sfd, i-1);
            printf("Done. Parent = %d, Me = %d\n", getppid(), getpid());
            exit(0);
        }
    }
    for ( int i = 1 ; i < argc ; i++ )
    {
        wait(NULL);
    }
    for ( int i = 1 ; i < argc ; i++ )
    {
        void* sptr = mmap(0, getpagesize(), PROT_READ, MAP_SHARED, sfd, (i-1) * getpagesize());
        if ( sptr == MAP_FAILED )
        {
            printf("Eroare la citirea lui nea Collatz");
            return errno;
        }
        printf("%s", static_cast<char*>(sptr));
    }
    void* sptr = mmap(0, getpagesize() * argc, PROT_READ, MAP_SHARED, sfd, 0);
    if ( munmap(sptr, getpagesize() * argc) == -1 )
    {
        printf("Nu a mers unmaparea");
        return errno;
    }
    ///printf("%s", static_cast<char*>(sptr)); da segfault, presupun ca e bine
    if ( shm_unlink(nume) == -1 )
    {
        printf("Nu stii sa eliberezi resurse, boss");
        return errno;
    }
    else
    {
        printf("Am eliberat resurse\n");
    }
    return 0;
}