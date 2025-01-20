#include"threadpool.h"

threadpool::threadpool(int Size) {
    pthread_t thread;
    for(int i = 0;i<Size;i++)
    {
        pthread_create(&thread,nullptr,Woker,this);
        Threads.push_back(thread);
    }
    isStop = false;
    pthread_mutex_init(&PoolMutex,NULL);
    pthread_cond_init(&TaskCond,NULL);
    pthread_mutex_init(&TaskMutex,NULL);
    pthread_cond_init(&ShutCond,NULL);
    ThreadsActive = 0;
}

threadpool::~threadpool() {
    pthread_mutex_lock(&PoolMutex);
    while (ThreadsActive||!TaskQueue.empty()) {
        pthread_cond_wait(&ShutCond,&PoolMutex);
    }
    isStop = true;
    pthread_mutex_unlock(&PoolMutex);
    pthread_cond_broadcast(&TaskCond);
    for(pthread_t thread : Threads) {
        pthread_join(thread,NULL);
    }
}

void * threadpool::Woker(void * This) {
    threadpool * thispool = static_cast<threadpool*>(This);
    while (!thispool->isStop)
    {
        pthread_mutex_lock(&thispool->PoolMutex);
        while (thispool->TaskQueue.empty()&&!thispool->isStop) {
            pthread_cond_wait(&thispool->TaskCond,&thispool->PoolMutex);
        }
        if(thispool->isStop) {
            pthread_mutex_unlock(&thispool->PoolMutex);
            return nullptr;
        }
        thispool->ThreadsActive ++;
        function<void()> Task = thispool->TaskQueue.front();
        thispool->TaskQueue.pop();
        Task();
        thispool->ThreadsActive --;
        if(thispool->ThreadsActive == 0&&thispool->TaskQueue.empty()) {
            pthread_cond_broadcast(&thispool->ShutCond);
        }
        pthread_mutex_unlock(&thispool->PoolMutex);
    }
    return nullptr;
}

void threadpool::TaskSubmit(function<void()>Task) {
    pthread_mutex_lock(&TaskMutex);
    TaskQueue.push(Task);
    pthread_cond_signal(&TaskCond);
    pthread_mutex_unlock(&TaskMutex);
}

void threadpool::Stop() {
    pthread_mutex_lock(&PoolMutex);
    while (ThreadsActive||!TaskQueue.empty()) {
        pthread_cond_wait(&ShutCond,&PoolMutex);
    }
    isStop = true;
    pthread_mutex_unlock(&PoolMutex);
    pthread_cond_broadcast(&TaskCond);
    for(pthread_t thread : Threads) {
        pthread_join(thread,NULL);
    }
}