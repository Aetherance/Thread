#include<iostream>
#include<unistd.h>
#include<pthread.h>
using namespace std;
int num;
pthread_mutex_t mtx;

int isA = 0;
int isB = 0;
void * APrintWait(void *)
{
    while(!isA)cout<<"A waiting"<<endl;
    return NULL;
}

void * BPrintWait(void *)
{
    while(!isB)
    {
        cout<<"B waiting"<<endl;
        usleep(10);
    }
    return NULL;
}

void * A(void *)
{
    pthread_t ptd0;
    pthread_create(&ptd0,NULL,APrintWait,NULL);
    if(pthread_mutex_lock(&mtx)==0)isA = 1;
    cout<<"A锁住了共享资源"<<endl;
    usleep(80);
    pthread_mutex_unlock(&mtx);
    
    return NULL;
}

void * B(void *)
{
    pthread_t ptd0;
    pthread_create(&ptd0,NULL,BPrintWait,NULL);
    if(pthread_mutex_lock(&mtx)==0)isB = 1;
    cout<<"B锁住了共享资源"<<endl;
    pthread_mutex_unlock(&mtx);
    
    return NULL;
}


int main()
{
    pthread_t ptd1,ptd2,ptd3;
    pthread_mutex_init(&mtx,NULL);
    pthread_create(&ptd1,NULL,A,NULL);
    usleep(100);
    pthread_create(&ptd2,NULL,B,NULL);


    pthread_join(ptd1,NULL);
    pthread_join(ptd2,NULL);
    pthread_mutex_destroy(&mtx);
    pthread_exit(NULL);
    return 0;
}