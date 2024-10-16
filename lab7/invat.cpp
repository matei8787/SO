#include <pthread.h>
#include <errno.h>
#include <semaphore.h>
#include <bits/stdc++.h>
#include <thread>
using namespace std;
class FooBar {
private:
    int n;
    sem_t sem1, sem2;
    int v1, v2;

public:
    FooBar(int n) {
        this->n = n;
        sem_init(&sem1, 0, v1);
        sem_init(&sem2, 0, v2);
    }

    void foo(function<void()> printFoo) {
        
        printFoo();
        sem_post(&sem1);
        for (int i = 1; i < n; i++) {
            
        	// printFoo() outputs "foo". Do not change or remove this line.
            sem_wait(&sem2);
        	printFoo();
            sem_post(&sem1);
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            
        	// printBar() outputs "bar". Do not change or remove this line.
            sem_wait(&sem1);
        	printBar();
            sem_post(&sem2);
        }
    }
};
void print_foo()
{
    cout<<"foo";
}
void print_bar()
{
    cout<<"bar\n";
}
void testeaza()
{
    int n;
    cin>>n;
    FooBar *fb = new FooBar(n);
    thread a(&FooBar::foo, fb, print_foo),b(&FooBar::bar, fb, print_bar);
    a.join();
    b.join();
}
int main()
{
    testeaza();
    return 0;
}