#include <stdlib.h>
#include <errno.h>
#include <cstdio>
#include <syscall.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
int open_fromfile(char* nume)
{
    int ans = open(nume, O_RDONLY);
    if ( ans < 0 )
    {
        perror("File not existing");
        printf("Numarul erorii %d\n", errno);
        return -1;
    }
    return ans;
}
int open_tofile(char* nume)
{
    struct stat statul;
    stat(nume, &statul);
    if ( errno == 0 )
    {
        printf("Fisierul exista, vrei sa dam override oricum? (y/n)");
        char op;
        scanf("%c", &op);
        if ( op == 'n' || op == 'N' )
        {
            return -1;
        }
    }
    int ans = open(nume, O_WRONLY | O_CREAT);
    if ( ans < 0 )
    {
        printf("Fisierul de scriere nu poate fi deschis\nNumarul erorii %d\n", errno);
        return -1;
    }
    return ans;
}

void copy_file(int from, int to, int fsz)
{
    char* buff = new char[fsz];
    int aux = read(from, buff, fsz);
    if ( aux < 0 )
    {
        printf("File did not read well\n");
        return;
    }
    aux = write(to, buff, fsz);
    if ( aux < 0 )
    {
        printf("File did not write well\n");
        return;
    }
}

void print_sz(char* nume)
{
    struct stat sb;
    stat(nume, &sb);
    printf("The file has %d bytes.", sb.st_size);
}

int main(int argc, char* argv[])
{
    printf("Program got %d arguments\n", argc);
    if ( argc != 3 )
    {
        printf("Too few arg\n");
        return -1;
    }
    char* from = argv[1], *to = argv[2];
    int ffrom = open_fromfile(from);
    if ( ffrom < 0 )
    {
        printf("Ceva s-a intamplat naspa");
        return 0;
    }
    int fto = open_tofile(to);
    if ( fto < 0 )
    {
        printf("Altceva s-a intamlat naspa");
        return 0;
    }

    struct stat sb;
    stat(from, &sb);
    copy_file(ffrom, fto, sb.st_size);
    close(ffrom);
    close(fto);

    return 0;
}