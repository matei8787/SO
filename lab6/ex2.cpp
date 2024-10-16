#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
using namespace std;
const int N = 205;
int a[N][N], b[N][N], c[N][N], nrcom;
int alin, bcol;
void citire()
{
    scanf("%d %d", &alin, &nrcom);
    for ( int i = 1 ; i <= alin ; i++ )
    {
        for ( int j = 1 ; j <= nrcom ; j++ )
        {
            scanf("%d", &a[i][j]);
        }
    }
    scanf("%d", &bcol);
    for ( int i = 1 ; i <= nrcom ; i++ )
    {
        for ( int j = 1 ; j <= bcol ; j++ )
        {
            scanf("%d", &b[i][j]);
        }
    }
}
namespace paralel{
    struct sarg
    {
        sarg(int n1, int n2): nr1(n1), nr2(n2){}
        int nr1, nr2;
    };
    void* inmul(void* arg)
    {
        int nr1 = static_cast<sarg*>(arg) -> nr1;
        int nr2 = static_cast<sarg*>(arg) -> nr2;
        int dans = nr1 * nr2;
        int* ans = new int(dans);
        void* vans = static_cast<void*>(ans);
        return vans;
    }
    void* mul(void* arg) ///inmultim linia lin din a cu coloana col din b
    {
        int lin=static_cast<sarg*>(arg) -> nr1;
        int col=static_cast<sarg*>(arg) -> nr2;
        pthread_t th[nrcom];
        for ( int i = 0 ; i < nrcom ; i++ )
        {
                int ireal = i + 1;
                sarg* parg = new sarg(a[lin][ireal], b[ireal][col]);
                void* arg = static_cast<void*>(parg);
                pthread_create(&th[i], NULL, inmul, arg);
        }
        int suma = 0;
        for ( int i = 0 ; i < nrcom ; i++ )
        {
            void* status;
            pthread_join(th[i], &status);
            int* pnr = static_cast<int*>(status);
            int nr = *pnr;
            suma += nr;
        }
        int* psuma = new int(suma);
        void* ans = static_cast<void*>(psuma);
        return ans;
    }
    void test_imul()
    {
        int a = 25;
        int b = 4;
        pthread_t t;
        sarg *arg = new sarg(a, b);
        void* varg = static_cast<void*>(arg);
        pthread_create(&t, NULL, inmul, varg);
        void* ans;
        pthread_join(t, &ans);
        int *x = static_cast<int*>(ans);
        int rasp = *x;
        printf("%d", rasp);
    }
    void rez()
    {
        pthread_t th[alin*bcol];
        for ( int i = 1 ; i <= alin ; i++ )
        {
            for ( int j = 1 ; j <= bcol ; j++ )
            {
                if ( pthread_create(&th[(i-1)*bcol+(j-1)], NULL, mul, static_cast<void*>(new sarg(i, j))))
                {
                    printf("Nu merge la creat");
                    return;
                }
            }
        }
        for ( int i = 1 ; i <= alin ; i++ )
        {
            for ( int j = 1 ; j <= bcol ; j++ )
            {
                void* res;
                if ( pthread_join(th[(i-1)*bcol+(j-1)], &res) )
                {
                    printf("Nu merge la preluat");
                    return;
                }
                int* pres = static_cast<int*>(res);
                int nr = *pres;
                c[i][j] = nr;
            }
        }
    }
}
void afis_m(int mat[N][N], int nrlin, int nrcol)
{
    for ( int i = 1 ; i <= nrlin ; i++ )
    {
        for ( int j = 1 ; j <= nrcol ; j++ )
        {
            cout<<mat[i][j]<<" ";
        }
        cout<<"\n";

    }
}
#include <fstream>
int rnr(int min)
{
    return rand() % min + min;
}
void make_date()
{
    ///alin com
    ///a[alin][com]
    ///bcol
    ///b[com][bcol]
    int n = 30;
    ofstream out("date.in");
    int y = rnr(n);
    out<<y<<" "<<n<<'\n';
    for ( int i = 1 ; i <= y ; i++ )
    {
        for ( int j = 1 ; j <= n ; j++ )
        {
            out<<rnr(n)<<" ";
        }
        out<<'\n';
    }
    y=rnr(n);
    out<<y<<'\n';
    for ( int i = 1 ; i <= n ; i++ )
    {
        for ( int j = 1 ; j <= y ; j++ )
        {
            out<<rnr(n)<<" ";
        }
        out<<'\n';
    }
    out.close();

}
namespace nu_paralel{
    void rez()
    {
        for ( int i = 1 ; i <= alin ; i++ )
        {
            for ( int j = 1 ; j <= bcol ; j++ )
            {
                int s = 0;
                for ( int k = 1 ; k <= nrcom ; k++ )
                {
                    s += a[i][k] * b[k][j];
                }
                c[i][j] = s;
            }
        }
    }
}
void afis_timp_paralel()
{
    time_t start = time(NULL);
    paralel::rez();
    time_t end = time(NULL);
    cout<<start<<" "<<end<<" "<<end-start;
}
void af_t_nuparalel()
{
    time_t start = time(NULL);
    nu_paralel::rez();
    time_t end = time(NULL);
    cout<<start<<" "<<end<<" "<<end-start;
}
int main()
{
    ///make_date();
    freopen("date.in", "r", stdin);
    freopen("date.out", "w", stdout);
    citire();
    afis_timp_paralel();
    cout<<'\n';
    af_t_nuparalel();
}