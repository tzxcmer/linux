#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>

#define NUM 1024

struct MyFile_
{
    int fd;
    char buffer[1024];
    int end;
};

typedef struct MyFile_ MyFile;

MyFile* fopen_(const char* pathname,const char* mode)
{
    assert(pathname);
    assert(mode);

    MyFile* fp = NULL;

    if(strcmp(mode,"r") == 0)
    {

    }
    else if(strcmp(mode,"r+") == 0)
    {

    }
    else if(strcmp(mode,"w") == 0)
    {
        int fd = open(pathname,O_WRONLY | O_TRUNC | O_CREAT,0666);

        if(fd>=0)
        {
            fp = (MyFile*)malloc(sizeof(MyFile));
            memset(fp,0,sizeof(MyFile));
            fp->fd = fd;
        }
    }
    else if(strcmp(mode,"w+") == 0)
    {

    }
    else if(strcmp(mode,"a") == 0)
    {

    }
    else if(strcmp(mode,"a+") == 0)
    {

    }
    else
    {

    }

    return fp;
} 

void fflush_(MyFile *fp)
{
    assert(fp);

    if(fp->end != 0)
    {
        //暂且认为刷新了--其实是把数据写到了内核
        write(fp->fd, fp->buffer, fp->end);
        syncfs(fp->fd); //将数据写入到磁盘
        fp->end = 0;
    }
}

void fputs_(const char* message, MyFile* fp)
{
    assert(message);
    assert(fp);

    strcpy(fp->buffer+fp->end,message);
    fp->end += strlen(message);

    printf("%s",fp->buffer);

    if(fp->fd == 0)
    {

    }
    else if(fp->fd == 1)
    {
        if(fp->buffer[fp->end-1] == '\n')
        {
            write(fp->fd,fp->buffer,fp->end);
            fp->end = 0;
        }
    }
    else if(fp->fd == 2)
    {

    }
    else
    {

    }
}

void fclose_(MyFile *fp)
{
    assert(fp);
    fflush_(fp);
    close(fp->fd);
    free(fp);
}

int main()
{
    close(1);
    MyFile* fp = fopen_("./log.txt","w");

    if(fp == NULL)
    {
        printf("open false\n");
        return 1;
    }

    fputs_("one:hello world\n",fp);

    fork();

    fclose_(fp);
    return 0;
}