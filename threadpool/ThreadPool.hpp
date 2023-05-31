#pragma once

#include<iostream>
#include<cassert>
#include<queue>
#include<cstdlib>
#include<unistd.h>
#include<pthread.h>
#include<memory.h>
#include<sys/prctl.h>
#include"Log.hpp"
#include"Task.hpp"
#include"Lock.hpp"

using namespace std;

int gThtreadNum = 5;

template<class T>
class ThreadPool{
    //单例模式
private:
    ThreadPool(int threadNum = gThtreadNum):threadNum_(threadNum),isStart_(false)
    {
        assert(threadNum > 0);
        pthread_mutex_init(&mutex_,nullptr);
        pthread_cond_init(&cond_,nullptr);
    }
    ThreadPool(const ThreadPool<T> &) = delete;
    void operator=(const ThreadPool<T>&) = delete;

public:
    //获取线程池实例
    static ThreadPool<T>* getInstance()
    {
        static Mutex mutex;
        if(instance == nullptr)
        {
            LockGuard lockguard(&mutex);
            if(instance == nullptr)
            {
                instance = new ThreadPool<T>();
            }
        }
        return instance;
    }

    

    static void* threadRoutine(void* args)
    {
        pthread_detach(pthread_self());
        ThreadPool* tp = static_cast<ThreadPool<T> *>(args);
        prctl(PR_SET_NAME,"follower");
        while(1)
        {
            tp->lockQueue();
            while(!tp->haveTask())
            {
                tp->waitForTask();
            }
            T t = tp->pop();
            tp->unlockQueue();

            int one,two;
            char oper;
            t.get(&one,&two,&oper);
            Log() << "新线程完成计算任务" << one << oper << two <<"=" << t.run() << endl;
        }
    }

    

    //线程池开始运行，创建线程
    void start()
    {
        assert(!isStart_);
        for(int i=0;i<threadNum_;i++)
        {
            pthread_t temp;
            pthread_create(&temp,nullptr,threadRoutine,this);
        }

        isStart_ = true;
    }

    //将线程插入任务队列
    void push(const T& in)
    {
        lockQueue();
        taskQueue_.push(in);
        choiceThreadForHandler();
        unlockQueue();
    }

    ~ThreadPool()
    {
        pthread_mutex_destroy(&mutex_);
        pthread_cond_destroy(&cond_);
    }
private:
    void lockQueue(){pthread_mutex_lock(&mutex_);}
    void unlockQueue(){pthread_mutex_unlock(&mutex_);}
    bool haveTask(){ return !taskQueue_.empty();}
    void waitForTask(){pthread_cond_wait(&cond_,&mutex_);}//线程等待
    void choiceThreadForHandler(){pthread_cond_signal(&cond_);}//线程唤醒
    T pop()
    {
        T temp = taskQueue_.front();
        taskQueue_.pop();

        return temp;
    }
private:
    bool isStart_;//是否开始
    int threadNum_;//线程数
    queue<T> taskQueue_;//任务队列
    pthread_mutex_t mutex_;//互斥量
    pthread_cond_t cond_;//条件变量

    static ThreadPool<T>* instance;
};

template<class T>
ThreadPool<T>* ThreadPool<T>::instance = nullptr;



