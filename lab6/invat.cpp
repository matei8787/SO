#include <pthread.h>
#include <cstdio>
#include <errno.h>
void* saluta(void* nume)
{
    printf("Hello, %s!", static_cast<char*>(nume));
    return NULL;
}
int main()
{
    pthread_t thread;
    char* nume = "Matei";
    if ( pthread_create(&thread, NULL, saluta, static_cast<void*>(nume)) ){
        return errno;
    }
    void** res;
    if ( pthread_join(thread, res) )
    {
        return errno;
    }
}