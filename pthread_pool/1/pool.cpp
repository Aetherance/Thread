// #include"threadpool.h"

// threadpool::threadpool(int Size)
// {
//     pthread_t ThreadCreated;
//     for(int i = 0;i<Size;i++)
//     {
//         pthread_create(&ThreadCreated,NULL,Woker,this);
//         Threads.push_back(ThreadCreated);
//     }
//     pthread_cond_init(&PoolCond,NULL);
//     pthread_mutex_init(&PoolMutex,NULL);
//     pthread_cond_init(&ShutdownCond,NULL);
//     isShutdown = false;
//     ThreadsWorking = 0;
// }

// threadpool::~threadpool()
// {

// }

// void *threadpool::Woker(void * This)
// {
//     threadpool * thispool = static_cast<threadpool*>(This);
//     while (!thispool->isShutdown)
//     {
//         pthread_mutex_lock(&(thispool->PoolMutex));
//         while (thispool->TaskQueue.empty()&&!thispool->isShutdown)
//         {
//             pthread_cond_wait(&thispool->PoolCond,&thispool->PoolMutex);
//         }
//         if(thispool->isShutdown)
//         {
//             pthread_mutex_unlock(&thispool->PoolMutex);
//             return NULL;
//         }
//         thispool->ThreadsWorking ++;
//         function<void()>Task = thispool->TaskQueue.front();
//         thispool->TaskQueue.pop();
//         pthread_mutex_unlock(&thispool->PoolMutex);
//         Task();
//         pthread_mutex_lock(&thispool->PoolMutex);
//         thispool->ThreadsWorking --;
//         if(thispool->ThreadsWorking == 0)
//         {
//             pthread_cond_signal(&thispool->ShutdownCond);
//         }
//         pthread_mutex_unlock(&thispool->PoolMutex);
//     }

//     return NULL;
// }

// void threadpool::TaskSubmit(function<void()>Task)
// {
//     pthread_mutex_lock(&PoolMutex);
//     TaskQueue.push(Task);
//     pthread_cond_signal(&PoolCond);
//     pthread_mutex_unlock(&PoolMutex);
// }

// void threadpool::Shutdown()
// {
//     pthread_mutex_lock(&PoolMutex);
//     while(ThreadsWorking)
//     {
//         pthread_cond_wait(&ShutdownCond,&PoolMutex);
//     }
//     pthread_mutex_unlock(&PoolMutex);
    
//     isShutdown = true;
//     pthread_cond_broadcast(&PoolCond);
//     for(auto thread:Threads)
//     {
//         pthread_join(thread,NULL);
//     }
//     pthread_cond_destroy(&PoolCond);
//     pthread_mutex_destroy(&PoolMutex);
//     pthread_cond_destroy(&ShutdownCond);
// }