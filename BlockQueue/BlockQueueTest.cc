#include"Task.hpp"
#include"BlockQueue.hpp"

#include<ctime>

const std::string ops = "+-*/%";

void *consumer(void* args)
{
    BlockQueue<Task>* bqp = static_cast<BlockQueue<Task> *>(args);
    while(true)
    {
        Task t = bqp->pop();
        int result = t();
        int one,two;
        char op;
        t.get(&one,&two,&op);
        cout << "consumer[" << pthread_self() << "] " << (unsigned long)time(nullptr) 
        << " 消费了一个任务: " << one << op << two << "=" << result << endl;
    }
}

void *productor(void* args)
{
    BlockQueue<Task>* bqp = static_cast<BlockQueue<Task> *>(args);
    while(true)
    {
        int one = rand()%50;
        int two = rand()%20;
        char op = ops[rand()%ops.size()];
        Task t(one,two,op);
        bqp->push(t);
        cout << "producter[" << pthread_self() << "] " << (unsigned long)time(nullptr) 
        << " 生产了一个任务: " << one << op << two << "=?" << endl;
        sleep(1);
    }
}


int main()
{
    srand((unsigned long)time(nullptr));

    BlockQueue<Task> bq;

    pthread_t c,p;
    pthread_create(&p,nullptr,productor,&bq);
    pthread_create(&c,nullptr,consumer,&bq);

    pthread_join(p,nullptr);
    pthread_join(c,nullptr);

    return 0;
}