#include <cstdio>
#include <unistd.h>
#include <bits/stdc++.h>
using namespace std;
int main()
{
    const char* msg = "Hello, World!";
    write(1, msg, strlen(msg));
}