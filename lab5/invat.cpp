#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <strings.h>
#include <cstdio>
int main()
{
    char nume[] = "myshm";
    int shared_fd = shm_open(nume, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if ( shared_fd < 0 )
    {
        return errno;
    }
    size_t shm_sz = 1000;
    if ( ftruncate(shared_fd, shm_sz) == -1 ){
        shm_unlink(nume);
        return errno;
    }
    void* shm_ptr = mmap(0, shm_sz, PROT_WRITE, MAP_SHARED, shared_fd, 0);
    if ( shm_ptr == MAP_FAILED){
        shm_unlink(nume);
        return errno;
    }
    sprintf(static_cast<char*>(shm_ptr), "%s", "Hello, World!");
    shm_ptr = mmap(0, shm_sz, PROT_READ, MAP_SHARED, shared_fd, 0);
    printf("%s", static_cast<char*>(shm_ptr));
    return 0;
}