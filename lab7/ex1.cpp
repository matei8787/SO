#include <bits/stdc++.h>
#include <thread>
#include <mutex>
#include <semaphore.h>
using namespace std;
# define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES, vaf;
mutex mtx;
/*  intr-un fel am facut si ex2 ca am folosit un semafor
    sa sincronizez afisarea :))
*/
sem_t sem;
int vsem;
int decrease_count ( int count )
{
    if ( available_resources < count ){
        return -1;
    }
    else{
        available_resources -= count ;
    }
    return 0;
}
int increase_count ( int count )
{
    available_resources += count ;
    return 0;
}
void fincrease(int count)
{
    increase_count(count);
    sem_wait(&sem);
    cout<<"Released "<<count<<" resources "<<available_resources<<" remaining\n";
    sem_post(&sem);
}
void fdecrease(int count)
{
    mtx.lock();
    if ( decrease_count(count) == -1 )
    {
        while ( decrease_count(count) == -1 )
            continue;

    }
    sem_wait(&sem);
    cout<<"Got "<<count<<" resources "<<available_resources<<" remaining\n";
    sem_post(&sem);
    mtx.unlock();
}
void testeaza(istream& in)
{
    int n;
    in>>n;
    thread th[n];
    vector<int> cate;
    for ( int i = 1 ; i <= n ; i++ )
    {
        int x;
        in>>x;
        cate.push_back(x);
    }
    sem_init(&sem, 0, vsem);
    for ( int i = 0 ; i < n ; i++ )
    {
        th[i] = thread{fdecrease, cate[i]};
    }
    sem_post(&sem);
    for ( int i = 0 ; i < n ; i++ )
    {
        th[i].join();
        th[i] = thread{fincrease, cate[i]};
        th[i].join();
    }

}
int main()
{
    ifstream in("date.in");
    testeaza(in);
}