#include<iostream>
#include<cstdlib>
#include<cstring>
#include<signal.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<string>

using namespace std;

int cnt = 0;

void hanlder(int signo)
{
    cout<<"我是一个进程，刚刚获取了信号："<<signo<<"cnt: "<<cnt<<endl;
    exit(1);
}

static void Usage(const string& proc)
{
    cerr<<"Usage:\n\t"<<proc<<"signo pid"<<endl;
}

int main(int argc,char *argv[])
{
    if(argc != 3)
    {
        Usage(argv[0]);
        exit(1);
    }

    if(kill(static_cast<pid_t>(atoi(argv[2])),atoi(argv[1])) == -1)
    {
        cerr<<"kill: "<<strerror(errno)<<endl;
        exit(2);
    }

    return 0;
}