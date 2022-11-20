#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "Task.hpp"

#define PROCESS_NUM 5

using namespace std;

int waitCommand(int waitFd,bool &quit)
{
    uint32_t command = 0;
    ssize_t s = read(waitFd,&command,sizeof(command));

    if(s == 0)
    {
        quit = true;
        return -1;
    }

    assert(s == sizeof(uint32_t));

    return command;
}


void sendAndWakeup(pid_t who,int fd,uint32_t command)
{
    write(fd,&command,sizeof(command));

    cout<<"main process:call process"<<who<<"execute"
    <<desc[command]<<"through"<<fd<<endl;
}

int main()
{
    load();

    vector<pair<pid_t,int>> slots;

    for(int i=0;i<PROCESS_NUM;i++)
    {
        //创建管道
        int pipefd[2] = {0};
        int n = pipe(pipefd);
        assert(n == 0);
        (void)n;

        //创建进程
        pid_t id = fork();
        assert(id != -1);

        if(id == 0)
        {
            close(pipefd[1]);

            while(true)
            {
                bool quit = false;
                int command = waitCommand(pipefd[0],quit);

                if(quit)
                break;

                if(command>=0 && command <handlerSize())
                {
                    callbacks[command]();
                }
                else
                {
                    cout<<"非法command: "<<command<<endl;
                }
            }

            exit(1);
        }

        close(pipefd[0]);
        slots.push_back(pair<pid_t,int>(id,pipefd[1]));
    }

    //父进程发任务
    srand((unsigned int)time(nullptr) ^ getpid() ^ 23323123123L);
    while(true)
    {
        int command = rand() % handlerSize();
        int choice = rand() % slots.size();

        sendAndWakeup(slots[choice].first,slots[choice].second,command);
        sleep(1);
    }

    for(const auto& slot: slots)
    {
        close(slot.second);
    }

    for(const auto& slot : slots)
    {
        waitpid(slot.first,nullptr,0);
    }

    return 0;
}