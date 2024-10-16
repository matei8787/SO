#include <bits/stdc++.h>
#include <semaphore.h>
using namespace std;

sem_t sem;
int vsem;
class Barrier
{
    int n, now;
    mutex mtx;
public:
    Barrier(int n)
    {
        this -> n = n;
        now = 0;
    }
    Barrier(){}
    void operator=(const Barrier&& b){
        n = b.n;
        now = 0;
    }
    void barrier_point()
    {
        mtx.lock();
        now++;
        if ( now == n )
        {
            mtx.unlock();
            sem_post(&sem);
            return;
        }
        mtx.unlock();
    }

};
Barrier b;
void tfun ( int tid )
{
    cout<<tid<<" reached barrier\n";
    b.barrier_point ();
    sem_wait(&sem);
    cout<<tid<<" passed barrier\n";
    sem_post(&sem);
}
void testeaza()
{
    int n;
    cin>>n;
    b = Barrier(n);
    sem_init(&sem, 0, vsem);
    thread th[n];
    for ( int i = 1 ; i <= n ; i++ )
    {
        th[i-1] = thread(tfun, i);
    }
    for ( int i = 0 ; i < n ; i++ )
    {
        th[i].join();
    }

}
int main()
{
    testeaza();
}