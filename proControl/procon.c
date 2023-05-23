#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>



int code = 0;

int main()
{
  pid_t id = fork();
  if(id < 0)
  {
    perror("fork");
    exit(1);
  }
  else if(id == 0)
  {
    int cnt = 5;
    while(cnt)
    {
      printf("cnt: %d, 我是子进程, pid: %d, ppid : %d\n", cnt, getpid(), getppid());
      sleep(1);
      cnt--;
    }
    code = 15;
    exit(15);
  }
  else 
  {
     printf("我是父进程, pid: %d, ppid: %d\n", getpid(), getppid());
     int status = 0;
     pid_t ret = wait(NULL);
    // pid_t ret = waitpid(id,&status,0);
     if(ret > 0)
     {
       printf("等待子进程成功, ret: %d, 子进程收到的信号编号: %d,子进程退出码: %d\n",\
                    ret, status & 0x7F ,(status >> 8)&0xFF); //0xff --> 0000...000 1111 1111
            printf("code: %d\n", code);
     }
  }
}
