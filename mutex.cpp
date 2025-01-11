#include<iostream>
#include<pthread.h>
#include<unistd.h>
using namespace std;
int num = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
void * A(void *)
{
    pthread_mutex_lock(&mtx);
    cout<<"线程A锁住了num"<<endl;
    // sleep(10);
    num = 1;
    while (num != 2);
    pthread_mutex_unlock(&mtx);

    return NULL;
}

void * B(void *)
{
    pthread_mutex_lock(&mtx);
    cout<<"线程B锁住了num"<<endl;
    num = 2;
    pthread_mutex_unlock(&mtx);

    return NULL;
}


int main()
{
    pthread_t ptd1,ptd2;
    pthread_create(&ptd1,NULL,A,NULL);
    sleep(1);
    pthread_create(&ptd2,NULL,B,NULL);

    pthread_join(ptd1,NULL);
    pthread_join(ptd2,NULL);
    cout<<endl<<num;

    return 0;
}