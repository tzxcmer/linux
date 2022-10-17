#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
  FILE* fp = fopen("bite","w+");
  const char* s1 = "linux so easy!\n";
  fwrite(s1,strlen(s1),1,fp);
  char s2[100];
  fclose(fp);
  FILE* fp1 = fopen("bite","r"); 

  if(fgets(s2,sizeof(s2),fp1) != NULL)
  puts(s2);
  
  
  fclose(fp1);
  return 0;
}
