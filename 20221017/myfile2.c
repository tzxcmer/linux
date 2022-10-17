#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
  int fd = open("bite",O_WRONLY|O_CREAT|O_TRUNC,0666);
  const char* s1 = "I like linux!\n";
  write(fd,s1,strlen(s1));
  close(fd);
  int fd1 = open("bite",O_RDWR,0666);
  char s2[100];
  memset(s2,'\0',sizeof(s2));
  read(fd1,s2,sizeof(s2));
  puts(s2);
  
  
  close(fd1);
  return 0;
}
