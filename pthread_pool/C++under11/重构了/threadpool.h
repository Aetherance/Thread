#ifndef THREAD_POOL
#define THREAD_POOL

#include<iostream>
#include<pthread.h>
#include<queue>
#include<vector>
#include<functional>
#include<unistd.h>

using namespace std;

class threadpool
{
public:
    threadpool(int);
    ~threadpool();
    static void * Woker(void *);
    void Stop(void);
    void TaskSubmit(function<void()>);
private:
    bool isStop;
    size_t ThreadsActive;
    vector<pthread_t>Threads;
    pthread_mutex_t PoolMutex;
    queue<function<void()>>TaskQueue;
    pthread_cond_t TaskCond;
    pthread_mutex_t TaskMutex;
    pthread_cond_t ShutCond;
    pthread_mutex_t ShutMutex;
};

#endif