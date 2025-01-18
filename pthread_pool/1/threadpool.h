// #ifndef THREAD_POOL
// #define THREAD_POOL

// #include<iostream>
// #include<pthread.h>
// #include<queue>
// #include<vector>
// #include<functional>
// #include<unistd.h>

// using namespace std;

// class threadpool
// {
// public:
//     threadpool(int);
//     ~threadpool();
//     static void * Woker(void *);
//     void Shutdown(void);
//     void TaskSubmit(function<void()>);
// private:
//     bool isStop;
//     vector<pthread_t>Threads;
//     queue<function<void()>>TaskQueue;
//     pthread_mutex_t PoolMutex;
//     pthread_cond_t PoolCond;
//     bool isShutdown;
//     pthread_cond_t ShutdownCond;
//     size_t ThreadsWorking;
// };


// #endif