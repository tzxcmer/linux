#include"comm.hpp"

std::string TransToHex(key_t k)
{
    char buffer[32];
    snprintf(buffer,sizeof buffer,"0x%x",k);
    return buffer;
}

int main()
{
    //创建公共K值
    key_t k = ftok(PATH_NAME,PROJ_ID);
    assert(k != -1);

    Log("create key done", Debug) << " server key : " << TransToHex(k) << std::endl;
    
    //创建共享内存
    int shmid = shmget(k,SHM_SIZE,IPC_CREAT | IPC_EXCL | 0666);
    if(shmid == -1)
    {
        perror("shmget");
        exit(1);
    }
    Log("create shm done", Debug) << " shmid : " << shmid << std::endl;

    //共享内存连接到地址空间
    char* shmaddr = (char*)shmat(shmid,nullptr,0);
    Log("attach shm done", Debug) << " shmid : " << shmid << std::endl;

    sleep(10);

    //将共享内存和地址空间失去关联
    int n = shmdt(shmaddr);
    assert(n != -1);
    (void)n;
    Log("detach shm done", Debug) << " shmid : " << shmid << std::endl;
    sleep(10);

    //删除共享内存,IPC_RMID即便是有进程和当下的shm挂接，依旧删除共享内存
    n = shmctl(shmid,IPC_RMID,nullptr);
    assert(n != -1);
    (void)n;
    Log("delete shm done", Debug) << " shmid : " << shmid << std::endl;
    
    return 0;
}