#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main ()
{
  printf("I am farent process :pid : %d\n",getpid());
  pid_t ret = fork();
  printf("ret:%d pid:%d ppid:%d\n",ret,getpid(),getppid());
  return 0;
}
