#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>

int main ()
{
  pid_t id = fork();

  if(id == 0)
  {
    //子进程
    int cnt = 5;
    while(cnt)
    {
      printf("我是子进程: %d\n",cnt--);
      sleep(1);

    }
  }
    else 
    {
      int quit = 0;
      while(!quit)
      {

      }
      int status = 0;
      pid_t res = waitpid(-1,&status,WNOHANG);

      if(res > 0)
      {
        //等待成功 && 子进程退出
        printf("子进程成功退出，退出码：%d\n",WEXITSTATUS(status));

      }
    }
}
