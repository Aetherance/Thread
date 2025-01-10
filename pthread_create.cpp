#include<iostream>
#include<unistd.h>
#include<pthread.h>
using namespace std;
void* thread_func(void *)
{
    cout<<"func()调用  线程ID -> "<<pthread_self()<<endl;
    return NULL;
}
int main()
{
    thread_func(NULL);
    pthread_t ptd;
    pthread_create(&ptd,NULL,thread_func,NULL);
    pthread_exit(0);

    return 0;
}