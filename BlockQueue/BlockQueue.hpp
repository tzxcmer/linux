#pragma once

#include<iostream>
#include<cstdlib>
#include<queue>
#include<unistd.h>
#include<pthread.h>

using namespace std;

const uint32_t gDefaultCap = 5;

template<class T>
class BlockQueue{
public:
    BlockQueue(uint32_t cap = gDefaultCap):cap_(cap)
    {
        pthread_mutex_init(&mutex_,nullptr);
        pthread_cond_init(&conCond_,nullptr);
        pthread_cond_init(&proCond_,nullptr);
    }
    ~BlockQueue()
    {
        pthread_mutex_destroy(&mutex_);
        pthread_cond_destroy(&conCond_);
        pthread_cond_destroy(&proCond_);
    }

public:
    //生产接口
    void push(const T& in)
    {
        // 加锁
        // 判断->是否适合生产->bq是否为满->程序员视角的条件->1. 满(不生产) 2. 不满(生产)
        // if(满) 不生产,休眠
        // else if(不满) 生产，唤醒消费者
        // 解锁

        lockQueue();
        while(isFull())
        {
            proBlockWait();
        }

        pushCore(in);
        unblockQueue();
        wakeupCon();
    }

    //消费接口
    T pop()
    {
        // 加锁
        // 判断->是否适合消费->bq是否为空->程序员视角的条件->1. 空(不消费) 2. 有(消费)
        // if(空) 不消费,休眠
        // else if(有) 消费，唤醒生产者
        // 解锁

        lockQueue();
        while(isEmpty())
        {
            conBlockWait();
        }

        T temp = popCore();
        unblockQueue();
        wakeupPro();

        return temp;
    }

private:
    void lockQueue()
    {
        pthread_mutex_lock(&mutex_);
    }

    void unblockQueue()
    {
        pthread_mutex_unlock(&mutex_);
    }
    bool isEmpty()
    {
        return bq_.empty();
    }

    bool isFull()
    {
        return bq_.size() == cap_;
    }

    void proBlockWait()
    {
        pthread_cond_wait(&proCond_, &mutex_);
    }

    void conBlockWait()
    {
        pthread_cond_wait(&conCond_,&mutex_);
    }

    void wakeupPro()
    {
        pthread_cond_signal(&proCond_);
    }

    void wakeupCon()
    {
        pthread_cond_signal(&conCond_);
    }

    void pushCore(const T& in)
    {
        bq_.push(in);
    }

    T popCore()
    {
        T temp = bq_.front();
        bq_.pop();
        return temp;
    }


private:
    uint32_t cap_;//容量
    queue<T> bq_;//阻塞队列
    pthread_mutex_t mutex_;//互斥锁
    pthread_cond_t conCond_;//消费者条件变量
    pthread_cond_t proCond_;//生产者条件变量
};