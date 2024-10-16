#include <pthread.h>
#include <string.h>
#include <cstdio>
void* rev(void* arg)
{
    char* str = static_cast<char*>(arg);
    int n = strlen(str);
    char* ans = new char[n+1];
    for ( int i = 0 ; i < n ; i++ )
    {
        ans[n-i-1] = str[i];
    }
    ans[n] = NULL;
    void* vans = static_cast<void*>(ans);
    return vans;
}
int main(int argc, char* argv[])
{
    if ( argc != 2 )
    {
        printf("Nu am argumentele corecte");
        return -1;
    }
    pthread_t th;
    if ( pthread_create(&th, NULL, rev, static_cast<void*>(argv[1])) )
    {
        printf("Nu a mers threadul");
        return -1;
    }
    void* ans;
    if ( pthread_join(th, &ans) )
    {
        printf("Nu a mers sa joinuim");
        return -1;
    }
    printf("%s", static_cast<char*>(ans));
    return 0;
}