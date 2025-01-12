#include<iostream>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
using namespace std;
void * A(void*)
{
    pthread_mutex_lock(&mtx);
    
    pthread_cond_wait(&cond,&mtx);
    cout<<"A using"<<endl;
    pthread_mutex_unlock(&mtx);
    return NULL;
}
void *B(void *)
{
    pthread_cond_signal(&cond);
    return NULL;
}
void *C(void *)
{
    pthread_mutex_lock(&mtx);
    cout<<"C using"<<endl;
    pthread_mutex_unlock(&mtx);
    return NULL;
}
int main()
{
    pthread_t ptd1,ptd2,ptd3;
    pthread_create(&ptd1,NULL,A,NULL);
    usleep(100);
    pthread_create(&ptd2,NULL,B,NULL);
    usleep(100);
    pthread_create(&ptd3,NULL,C,NULL);
    pthread_join(ptd1,NULL);
    pthread_join(ptd2,NULL);
    pthread_join(ptd3,NULL);
    return 0;
}