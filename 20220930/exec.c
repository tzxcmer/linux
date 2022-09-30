#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


#define NUM 16


const char* myfile = "./mycmd";

int main(int argc,char* argv[],char* env[])
{

  const char* _env[NUM] = {
    (char*)"tzx_VAL=123456",
    NULL
  };

  pid_t id = fork();
  if(id == 0)
  {
    printf("子进程开始：%d\n",getpid());
    sleep(3);
    char* const  _argv[NUM] = {
      (char*)"ls",
      (char*)"-a",
      (char*)"-l",
      (char*)"-i",
      NULL
    };

    //execle(myfile,"mycmd","-a",NULL,env);
    //execle(myfile, "mycmd", "-a", NULL, _env);
    //execl(myfile,"mycmd","-b",NULL);
    //execl("/usr/bin/ls", "ls", "-a", "-l", NULL);
    //execlp("ls", "ls", "-a", "-l", NULL);
    execv("/usr/bin/ls", _argv);
    exit(1);
  }
  else 
  {
    printf("父进程开始运行：%d\n",getppid());
    int status = 0;
    pid_t res = waitpid(-1,&status,0);
    if(res > 0)
    {
      printf("wait succes code :%d\n",WEXITSTATUS(status));
    }
  }
  return 0;
}
