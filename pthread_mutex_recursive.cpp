#include<iostream>
#include<unistd.h>
#include<pthread.h>
using namespace std;

pthread_mutex_t mtx;
pthread_mutexattr_t mtxattr;
void * A(void *)
{
    pthread_mutex_lock(&mtx);
    cout<<"锁定第1次"<<endl;
    pthread_mutex_lock(&mtx);
    cout<<"锁定第2次"<<endl;
    cout<<"A"<<endl;
    pthread_mutex_unlock(&mtx);
    cout<<"解锁第1次"<<endl;
    pthread_mutex_unlock(&mtx);
    cout<<"解锁第2次"<<endl;
    return NULL;
}

void * B(void *)
{
    pthread_mutex_lock(&mtx);
    cout<<"B"<<endl;
    pthread_mutex_unlock(&mtx);
    return NULL;
}

int main()
{
    pthread_mutexattr_init(&mtxattr);
    pthread_mutexattr_settype(&mtxattr,PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mtx,&mtxattr);
    pthread_t ptd1,ptd2;    
    pthread_create(&ptd1,NULL,A,NULL);

    usleep(100);

    pthread_create(&ptd2,NULL,B,NULL);


    pthread_join(ptd1,NULL);
    pthread_join(ptd2,NULL);
    pthread_mutex_destroy(&mtx);
    return 0;
}