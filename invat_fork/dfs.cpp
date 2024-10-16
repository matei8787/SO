/*
NU STIU SA FAC ASA CEVA!
#include <bits/stdc++.h>
#include <sys/wait.h>
using namespace std;

vector<int> g[100005];
int x, n;

void citire()
{
    int m;
    cin>>n>>m>>x;
    for ( int i = 1 ; i <= m ; i++ )
    {
        int u, v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
}
int viz[100005];
void dfs(int nod)
{
    viz[nod] = 1;
    cout<<nod<<" ";
    for ( int vec : g[nod] )
    {
        if ( viz[vec] )
            continue;
        pid_t pid = fork();
        if ( pid < 0 )
        {
            cout<<"Ceva nu a mers bine";
            return;
        }
        if ( pid == 0 )
        {
            dfs(vec);
            exit(0);
        }
        wait(NULL);
    }
}
void rez()
{
    int nod = x;
    for ( int i = 0 ; i < g[nod].size() ; i++ )
    {
        viz[nod] = 1;
        cout<<nod<<" ";
        if ( viz[g[nod][i]] )
            continue;
        pid_t pid = fork();
        if ( pid == 0 )
        {
            i = 0;
            nod = g[nod][i];
        }
        else if ( pid > 0 )
        {
            wait(NULL);
        }
    }
}
void factorial(int nr)
{
    while ( nr > 0 )
    {
        
    }
}
void pjos();
void psus(int nr)
{
    pid_t pid = fork();
    if ( pid == 0 )
    {
        pjos(nr);
    }
    else if ( pid > 0 )
    {
        wait(NULL);
    }
}
void pjos(int nr)
{
    if ( nr == 1 )
        return 1;
}
int main()
{
    citire();
    rez();
    return 0;
}*/