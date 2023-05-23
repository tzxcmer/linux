#include"comm.hpp"

#include<sys/wait.h>


static void getMessage(int fd)
{
    char buffer[SIZE];
    while(true)
    {
        memset(buffer,'\0',sizeof(buffer));
        ssize_t s = read(fd,buffer,sizeof(buffer)-1);
        if(s > 0)
        {
            cout<<"["<<getpid()<<"]"<<"client say>"<<buffer<<endl;
        }
        else if(s == 0)
        {
            cout<<"["<<getpid()<<"]"<<"read end of file, clien quit, server quit too!" << endl;
        }
        else
        {
            perror("read");
            break;
        }
    }

        // memset(buffer,'\0',sizeof(buffer));
        // ssize_t s = read(fd,buffer,sizeof(buffer)-1);
        // if(s > 0)
        // {
        //     cout<<"["<<getpid()<<"]"<<"client say>"<<buffer<<endl;
        // }
        // else if(s == 0)
        // {
        //     cout<<"["<<getpid()<<"]"<<"read end of file, clien quit, server quit too!" << endl;
        // }
        // else
        // {
        //     perror("read");
        // }
    
}

int main()
{
    //创建管道文件
    if(mkfifo(ipcPath.c_str(),MODE) < 0)
    {
        perror("mkfifo");
        exit(1);
    }

    //Log("创建管道文件成功!",Debug)<<"step first"<<endl;

    //文件操作
    int fd = open(ipcPath.c_str(),O_RDONLY);
    if(fd < 0)
    {
        perror("open");
        exit(2);
    }

    //Log("打开管道文件成功!",Debug)<<"step second"<<endl;

   pid_t id = fork();
    if(id == 0)
    {
        getMessage(fd);
        exit(1);
    }

    waitpid(-1,nullptr,0);

    //关闭管道文件
    close(fd);
    //Log("关闭管道文件成功!",Debug)<<"step third"<<endl;

    //删除管道文件
    unlink(ipcPath.c_str());
    //Log("删除管道文件成功!",Debug)<<"step fourth"<<endl;

    return 0;
}