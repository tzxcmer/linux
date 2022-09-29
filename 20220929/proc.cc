#include<stdio.h>
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>


typedef void (*handler_t)();
std::vector<handler_t> handlers;


void fun_one()
{
  printf("这是一临时任务1\n");
}

void fun_two()
{
  printf("这是一个临时任务2\n");
}

void Load()
{
  handlers.push_back(fun_one);
  handlers.push_back(fun_two);
}

int main()
{
  pid_t id = fork();
  if(id == 0)
  {
    //子进程
    int cnt = 5;
    while(cnt)
    {
      printf("我是子进程:%d\n",cnt--);
      sleep(1);

    }

    exit(11);
  }
  else 
  {
    int quit = 0;
     while(!quit)   
     {
            int status = 0;
            pid_t res = waitpid(-1, &status, WNOHANG); //以非阻塞方式等待
            if(res > 0)
            {
                //等待成功 && 子进程退出
                printf("等待子进程退出成功, 退出码: %d\n", WEXITSTATUS(status));
                quit = 1;
            }
            else if( res == 0 )
            {
                //等待成功 && 但子进程并未退出
                printf("子进程还在运行中，暂时还没有退出，父进程可以在等一等, 处理一下其他事情？？\n");
                if(handlers.empty()) Load();
                for(auto it : handlers)
                {
                  it();
                }
            }
            
            sleep(1);
   }

  }
}
