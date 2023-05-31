#include<ctime>

#include"Task.hpp"
#include"ThreadPool.hpp"
#include<thread>

int main()
{
    prctl(PR_SET_NAME,"master");
    const string operators = "+/*/%";
    unique_ptr<ThreadPool<Task>> tp(ThreadPool<Task>::getInstance());
    tp->start();
    
    srand((unsigned long)time(nullptr) ^ getpid() ^ pthread_self());

    while(1)
    {
        int one = rand()%50;
        int two = rand()%10;
        char oper = operators[rand()%operators.size()];
        Log() << "主线程派发计算任务: " << one << oper << two << "=?" << "\n";
        Task t(one,two,oper);
        tp->push(t);
        sleep(1);
    }

    return 0;
}