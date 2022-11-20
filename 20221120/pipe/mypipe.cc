#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main()
{
    //创建管道
    int pipefd[2] = {0};//0:read  1:write
    int n = pipe(pipefd);
    assert(n != -1);
    (void)n;


#ifdef DEBUG
    cout<<"pipefd[0]"<<pipefd[0]<<endl;
    cout<<"pipefd[1]"<<pipefd[1]<<endl;
#endif
    
    //创建子进程
    pid_t id = fork();
    assert(id != -1);

    if(id == 0)
    {
        //子进程
        //关闭子进程不要的fd
        close(pipefd[1]);
        char buffer[1024 * 8];

        // while(true)
        // {
        //     ssize_t s = read(pipefd[0],buffer,sizeof(buffer)-1);

        //     if(s > 0)
        //     {
        //         buffer[s] = 0;

        //         cout<<"child get message "<<getpid()<<endl;
        //         cout<<buffer<<endl;
        //     }
        //     else if( s == 0)
        //     {
        //         cout<<"write father"<<endl;
        //         break;
        //     }
        // }

        ssize_t s = read(pipefd[0],buffer,sizeof(buffer)-1);

            if(s > 0)
            {
                buffer[s] = 0;

                //cout<<"child get message "<<getpid()<<endl;
                cout<<buffer<<endl;
            }
            else if( s == 0)
            {
                cout<<"write father"<<endl;
            }

        exit(0);
    }

    //父进程
    close(pipefd[0]);
    //string message = "父进程正在发消息";
    string message = "I am father";
    int count = 0;
    char second_buffer[1024 * 8];

    while(true)
    {
        //构造变化字符串
        snprintf(second_buffer,sizeof(second_buffer),"%s[%d] : %d",
                 message.c_str(),getpid,count++);
        
        //写入
        write(pipefd[1],second_buffer,strlen(second_buffer));

        sleep(1);
        cout<<count<<endl;

        if(count == 5)
        {
            cout<<"write quit"<<endl;
            break;
        }
    } 

    close(pipefd[1]);

    pid_t ret = waitpid(id,nullptr,0);
    cout << "id: " << id << " ret: " << ret << endl;
    assert(ret > 0);
    (void)ret;

    return 0;
}