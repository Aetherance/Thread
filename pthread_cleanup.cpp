#include<iostream>
#include<pthread.h>
#include<unistd.h>
using namespace std;

void a(void *)
{
    cout<<"析构1"<<endl;
}

void b(void *)
{
    cout<<"析构2"<<endl;
}

void c(void *)
{
    cout<<"析构3"<<endl;
}

void * A(void *)
{
    pthread_cleanup_push(a,NULL);
    // pthread_cleanup_push(b,NULL);
    // pthread_cleanup_push(c,NULL);
    cout<<"A线程调用"<<endl;

    pthread_exit(NULL);
    sleep(5);
    pthread_cleanup_pop(1);   
}

int count = 0;
int main()
{

    pthread_t ptd1;
    pthread_create(&ptd1,NULL,A,NULL);

    pthread_join(ptd1,NULL);
    return 0;
}