#include<iostream>
#include<unistd.h>

using namespace std;

int main()
{
    while(1)
    {
        sleep(1);
        cout<<"我是一个进程："<<getpid()<<endl;
    }

    return 0;
}